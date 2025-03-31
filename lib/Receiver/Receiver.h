#ifndef RECEIVER_H
#define RECEIVER_H

#include "Arduino.h"
#include "config.h"
#include "ReceiverStruct.h"

class Receiver
{
private:
    static volatile uint32_t lastRiseTime[MAX_CHANNELS]; // Lưu thời gian trước đó
    static volatile uint16_t channelValue[MAX_CHANNELS]; // Lưu giá trị kênh PWM
    static uint8_t numChannels;                          // Số kênh nhận tín hiệu
    static ChannelConfig channelConfigs[MAX_CHANNELS];   // Cấu hình từng kênh

    static void IRAM_ATTR handleInterrupt(uint8_t channel);

// Định nghĩa từng hàm xử lý ngắt riêng biệt
#if MAX_CHANNELS >= 1
    static void IRAM_ATTR handleInterrupt0(uint8_t channel);
#endif
#if MAX_CHANNELS >= 2
    static void IRAM_ATTR handleInterrupt1(uint8_t channel);
#endif
#if MAX_CHANNELS >= 3
    static void IRAM_ATTR handleInterrupt2(uint8_t channel);
#endif
#if MAX_CHANNELS >= 4
    static void IRAM_ATTR handleInterrupt3(uint8_t channel);
#endif
#if MAX_CHANNELS >= 5
    static void IRAM_ATTR handleInterrupt4(uint8_t channel);
#endif
#if MAX_CHANNELS >= 6
    static void IRAM_ATTR handleInterrupt5(uint8_t channel);
#endif
#if MAX_CHANNELS >= 7
    static void IRAM_ATTR handleInterrupt6(uint8_t channel);
#endif
#if MAX_CHANNELS >= 8
    static void IRAM_ATTR handleInterrupt7(uint8_t channel);
#endif

    void autoUpdateChannelRange(uint8_t channel, uint16_t value);

public:
    Receiver();
    void init(ChannelConfig *configs, uint8_t channels);
    void printReceiverInfo();
    int16_t getChannelValue(uint8_t channel);
};

#endif // RECEIVER_H
