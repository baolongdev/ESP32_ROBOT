#ifndef MOTOR_PWM_H
#define MOTOR_PWM_H

#include "Arduino.h"
#include "driver/ledc.h"
#include "CarControlStruct.h"

class MotorPWM
{
private:
    MotorPWMConfig config;
    uint16_t motorDuty;

public:
    void init(const MotorPWMConfig &motorConfig);
    void setDuty(float duty);
    void setFrequency(float frequency);

    float getDuty();
    uint32_t getFrequency();

    void printMotorInfo();
};

#endif
