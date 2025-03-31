#include "PIDController.h"

PIDController::PIDController(float Kp, float Ki, float Kd, float minOutput, float maxOutput)
    : Kp(Kp), Ki(Ki), Kd(Kd), minOutput(minOutput), maxOutput(maxOutput), prevError(0.0f), integral(0.0f) {}

float PIDController::compute(float setpoint, float measurement, float dt)
{
    if (dt <= 0.0f)
        return 0.0f; // Tránh lỗi chia 0

    float error = setpoint - measurement;
    integral += error * dt;
    float derivative = (error - prevError) / dt;

    float output = Kp * error + Ki * integral + Kd * derivative;
    prevError = error;

    // Giới hạn đầu ra
    if (output > maxOutput)
        output = maxOutput;
    if (output < minOutput)
        output = minOutput;

    return output;
}

void PIDController::reset()
{
    prevError = 0.0f;
    integral = 0.0f;
}
