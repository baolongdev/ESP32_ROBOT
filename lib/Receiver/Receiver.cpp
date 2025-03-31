#include "Receiver.h"

volatile uint32_t Receiver::lastRiseTime[8] = {0};
volatile uint16_t Receiver::channelValue[8] = {DEFAULT_CHANNEL_VALUE}; // Mặc định là giữa (1500µs)
uint8_t Receiver::numChannels = 0;
ChannelConfig Receiver::channelConfigs[8] = {};

Receiver::Receiver() {}

void Receiver::init(ChannelConfig *configs, uint8_t channels)
{
    numChannels = channels;

    for (uint8_t i = 0; i < numChannels; i++)
    {
        channelConfigs[i] = configs[i];
        pinMode(channelConfigs[i].pin, INPUT);

        void (*interruptHandlers[8])() = {
            []()
            { handleInterrupt(0); }, []()
            { handleInterrupt(1); },
            []()
            { handleInterrupt(2); }, []()
            { handleInterrupt(3); },
            []()
            { handleInterrupt(4); }, []()
            { handleInterrupt(5); },
            []()
            { handleInterrupt(6); }, []()
            { handleInterrupt(7); }};

        if (i < 8)
        {
            attachInterrupt(digitalPinToInterrupt(channelConfigs[i].pin), interruptHandlers[i], CHANGE);
        }
    }

    printReceiverInfo();
}

int16_t Receiver::getChannelValue(uint8_t channel)
{
    if (channel >= numChannels)
        return 0;

    uint16_t rawValue = channelValue[channel];
    autoUpdateChannelRange(channel, rawValue);

    uint16_t minVal = channelConfigs[channel].minVal;
    uint16_t maxVal = channelConfigs[channel].maxVal;

    // Nếu min/max chưa cập nhật xong, trả về 0
    if (minVal == maxVal)
        return 0;

    uint16_t midVal = (minVal + maxVal) / 2;
    // Nếu là công tắc, trả về -1, 0, 1
    if (channelConfigs[channel].isSwitch)
    {
        if (rawValue < SWITCH_LOW_THRESHOLD)
            return 0;
        if (rawValue > SWITCH_HIGH_THRESHOLD)
            return 2;
        return 1;
    }

    // Nếu là thanh trượt, chuyển đổi về khoảng đối xứng [-100, 100]
    int16_t mappedValue = ((int32_t)(rawValue - midVal) * 200) / (maxVal - minVal);
#ifdef DEBUG_RECEIVER
    return rawValue;
#endif
    return mappedValue - 50;
}

void Receiver::autoUpdateChannelRange(uint8_t channel, uint16_t value)
{
    if (channel >= numChannels)
        return;

    if (value < channelConfigs[channel].minVal)
    {
        channelConfigs[channel].minVal = value;
    }
    if (value > channelConfigs[channel].maxVal)
    {
        channelConfigs[channel].maxVal = value;
    }
}

// 📌 Định nghĩa các hàm ngắt riêng biệt cho từng kênh
void IRAM_ATTR Receiver::handleInterrupt0(uint8_t channel) { Receiver::handleInterrupt(channel); }
void IRAM_ATTR Receiver::handleInterrupt1(uint8_t channel) { Receiver::handleInterrupt(channel); }
void IRAM_ATTR Receiver::handleInterrupt2(uint8_t channel) { Receiver::handleInterrupt(channel); }
void IRAM_ATTR Receiver::handleInterrupt3(uint8_t channel) { Receiver::handleInterrupt(channel); }
void IRAM_ATTR Receiver::handleInterrupt4(uint8_t channel) { Receiver::handleInterrupt(channel); }
void IRAM_ATTR Receiver::handleInterrupt5(uint8_t channel) { Receiver::handleInterrupt(channel); }
void IRAM_ATTR Receiver::handleInterrupt6(uint8_t channel) { Receiver::handleInterrupt(channel); }
void IRAM_ATTR Receiver::handleInterrupt7(uint8_t channel) { Receiver::handleInterrupt(channel); }

// 📌 Định nghĩa đúng hàm handleInterrupt()
void IRAM_ATTR Receiver::handleInterrupt(uint8_t channel)
{
    uint32_t now = micros();
    if (digitalRead(channelConfigs[channel].pin))
    {
        lastRiseTime[channel] = now;
    }
    else
    {
        channelValue[channel] = now - lastRiseTime[channel];
    }
}

void Receiver::printReceiverInfo()
{
    Serial.println("✅ Thông tin Receiver:");
    Serial.print("📌 Số kênh: ");
    Serial.println(numChannels);

    for (uint8_t i = 0; i < numChannels; i++)
    {
        Serial.print("🔹 Kênh ");
        Serial.print(i);
        Serial.print(" - Chân: ");
        Serial.print(channelConfigs[i].pin);
        Serial.print(" | Min: ");
        Serial.print(channelConfigs[i].minVal);
        Serial.print(" | Max: ");
        Serial.print(channelConfigs[i].maxVal);
        Serial.print(" | Loại: ");
        Serial.println(channelConfigs[i].isSwitch ? "Công tắc" : "Trượt");
    }
}
