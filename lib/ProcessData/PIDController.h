#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PIDController
{
public:
    PIDController(float Kp, float Ki, float Kd, float minOutput, float maxOutput);
    float compute(float setpoint, float measurement, float dt);
    void reset();

private:
    float Kp, Ki, Kd;           // Hệ số PID
    float prevError;            // Lưu sai số trước đó
    float integral;             // Thành phần tích phân
    float minOutput, maxOutput; // Giới hạn giá trị đầu ra
};

#endif
