#include "MotorPWM.h"

void MotorPWM::init(const MotorPWMConfig &motorConfig)
{
    config = motorConfig;
    motorDuty = (uint16_t)((config.dutyCycle / 100.0) * ((1 << config.resolution) - 1));

    ledcSetup(config.channel, config.frequency, config.resolution);
    ledcAttachPin(config.pin, config.channel);
    ledcWrite(config.channel, motorDuty);

    printMotorInfo();
}

void MotorPWM::setDuty(float duty)
{
    if (duty < 0 || duty > 100)
    {
        Serial.println("⚠ Giá trị duty cycle không hợp lệ! Nhập từ 0% đến 100%.");
        return;
    }

    motorDuty = (uint16_t)((duty / 100.0) * ((1 << config.resolution) - 1));
    ledcWrite(config.channel, motorDuty);

    Serial.print("✅ Duty cycle mới: ");
    Serial.print(duty);
    Serial.println("%");
}

void MotorPWM::setFrequency(float frequency)
{
    if (frequency < 10 || frequency > 5000)
    {
        Serial.println("⚠ Tần số không hợp lệ! Nhập từ 10 Hz đến 5000 Hz.");
        return;
    }

    config.frequency = frequency;
    ledcSetup(config.channel, config.frequency, config.resolution);
    ledcWrite(config.channel, motorDuty);

    Serial.print("✅ Tần số PWM mới: ");
    Serial.print(config.frequency);
    Serial.println(" Hz");
}

float MotorPWM::getDuty()
{
    return ((float)motorDuty / ((1 << config.resolution) - 1)) * 100;
}

uint32_t MotorPWM::getFrequency()
{
    return config.frequency;
}

void MotorPWM::printMotorInfo()
{
    Serial.println("✅ Motor PWM đã khởi tạo!");
    Serial.print("📌 GPIO: ");
    Serial.println(config.pin);
    Serial.print("📌 Kênh: ");
    Serial.println(config.channel);
    Serial.print("📌 Độ phân giải: ");
    Serial.print(config.resolution);
    Serial.println(" bit");
    Serial.print("📌 Tần số: ");
    Serial.print(config.frequency);
    Serial.println(" Hz");
    Serial.print("📌 Duty Cycle: ");
    Serial.print(getDuty());
    Serial.println("%");
}
