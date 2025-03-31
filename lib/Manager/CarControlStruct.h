#ifndef CAR_CONTROL_STRUCTS_H
#define CAR_CONTROL_STRUCTS_H

#include "Arduino.h"
#include "config.h"
// Enum xác định hướng di chuyển của xe
enum Direction
{
    STOP,
    FORWARD,
    BACKWARD
};
// Cấu trúc cấu hình PWM cho động cơ
struct MotorPWMConfig
{
    uint8_t pin = 0;                             // Chân GPIO
    uint8_t channel = 0;                         // Kênh PWM
    uint8_t resolution = MOTOR_PWM_DEFAULT_RES;  // Độ phân giải PWM
    uint32_t frequency = MOTOR_PWM_DEFAULT_FREQ; // Tần số PWM
    float dutyCycle = MOTOR_PWM_DEFAULT_DUTY;    // Hệ số nhiệm vụ (Duty Cycle)

    MotorPWMConfig() = default;
    MotorPWMConfig(uint8_t p, uint8_t ch, uint8_t res, uint32_t freq, float duty)
        : pin(p), channel(ch), resolution(res), frequency(freq), dutyCycle(duty) {}
};

struct CarControlConfig
{
    MotorPWMConfig leftMotorConfig;
    MotorPWMConfig rightMotorConfig;
    float forwardMin = 0.0f, forwardMax = 0.0f;
    float backwardMin = 0.0f, backwardMax = 0.0f;

    CarControlConfig() = default;
    CarControlConfig(const MotorPWMConfig &left, const MotorPWMConfig &right,
                     float fMin, float fMax, float bMin, float bMax)
        : leftMotorConfig(left), rightMotorConfig(right),
          forwardMin(fMin), forwardMax(fMax),
          backwardMin(bMin), backwardMax(bMax) {}
};

#endif // CAR_CONTROL_STRUCTS_H