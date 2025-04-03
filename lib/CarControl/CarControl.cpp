#include "CarControl.h"

CarControl::CarControl() : currentDirection(STOP), lastStopTime(0) {}

void CarControl::init(const CarControlConfig &config)
{
    this->config = config;
    leftMotor.init(config.leftMotorConfig);
    rightMotor.init(config.rightMotorConfig);
    currentDirection = STOP;
    lastStopTime = millis();

    printCarInfo();
}

void CarControl::stop()
{
    // Dừng cả 2 động cơ
    setMotorDuty(MOTOR_PWM_DEFAULT_DUTY, MOTOR_PWM_DEFAULT_DUTY);
    lastStopTime = micros(); // Lưu thời điểm dừng
    currentDirection = STOP;
}

bool CarControl::isStopDelayOver(uint32_t delayTime)
{
    return (micros() - lastStopTime) >= delayTime;
}

void CarControl::smoothStop(uint32_t waitTime)
{
    stop();
    uint32_t startTime = micros();
    while (micros() - startTime < waitTime)
    {
        delayMicroseconds(1000);
    }
}

void CarControl::moveForward(float speed)
{
    if (speed < 1) // Kiểm tra giá trị hợp lệ
    {
        // Serial.println("⚠ Giá trị speed không hợp lệ! Nhập từ 1 đến 50.");
        stop();
        return;
    }
    float mappedSpeed = mapSpeed(speed, config.forwardMin, config.forwardMax);
    setMotorDuty(mappedSpeed, mappedSpeed);
    currentDirection = FORWARD;
}

void CarControl::moveBackward(float speed)
{
    if (speed > -1) // Kiểm tra giá trị hợp lệ
    {
        // Serial.println("⚠ Giá trị speed không hợp lệ! Nhập từ -1 đến -50.");
        stop();
        return;
    }
    float mappedSpeed = mapSpeed(abs(speed), config.backwardMin, config.backwardMax);
    setMotorDuty(mappedSpeed, mappedSpeed);
    currentDirection = BACKWARD;
}

void CarControl::moveForwardTurn(float speed, float steering)
{
    // Kiểm tra giá trị speed hợp lệ
    if (speed < 1 || speed > 50)
    {
        stop();
        return;
    }

    // Steering ảnh hưởng đến độ lệch giữa hai bánh xe
    // Tính toán duty cho bánh trái và bánh phải dựa trên steering
    float leftDuty = mapSpeed(speed,
                              config.forwardMin * (1 - abs(steering) / 50.0), // Giảm forwardMin khi steering âm (rẽ trái)
                              config.forwardMax);                             // Giữ nguyên forwardMax

    float rightDuty = mapSpeed(speed,
                               config.forwardMin,                               // Giữ nguyên forwardMin
                               config.forwardMax * (1 - abs(steering) / 50.0)); // Giảm forwardMax khi steering dương (rẽ phải)

    // Nếu steering âm (rẽ trái), bánh trái giảm tốc độ; nếu steering dương (rẽ phải), bánh phải giảm tốc độ
    if (steering < 0)
    {
        setMotorDuty(leftDuty, rightDuty); // Rẽ trái
    }
    else
    {
        setMotorDuty(rightDuty, leftDuty); // Rẽ phải
    }

    currentDirection = FORWARD;
}

void CarControl::moveBackwardTurn(float speed, float steering)
{
    // Kiểm tra giá trị speed hợp lệ
    if (speed < -50 || speed > -1)
    {
        stop();
        return;
    }

    float leftDuty = mapSpeed(speed,
                              config.backwardMin * (1 + abs(steering) / 50.0), // Giảm forwardMin khi steering âm (rẽ trái)
                              config.backwardMax);                             // Giữ nguyên forwardMax

    float rightDuty = mapSpeed(speed,
                               config.backwardMin,                               // Giữ nguyên forwardMin
                               config.backwardMax * (1 + abs(steering) / 50.0)); // Giảm forwardMax khi steering dương (rẽ phải)

    // Nếu steering âm (rẽ trái), bánh trái giảm tốc độ; nếu steering dương (rẽ phải), bánh phải giảm tốc độ
    if (steering < 0)
    {
        setMotorDuty(leftDuty, rightDuty); // Rẽ trái khi lùi
    }
    else
    {
        setMotorDuty(rightDuty, leftDuty); // Rẽ phải khi lùi
    }

    currentDirection = BACKWARD;
}

void CarControl::printCarInfo()
{
    // In thông tin trạng thái xe và động cơ
    switch (currentDirection)
    {
    case FORWARD:
        // Serial.println("Tiến");
        break;
    case BACKWARD:
        // Serial.println("Lùi");
        break;
    case STOP:
        // Serial.println("Dừng");
        break;
    }

    leftMotor.printMotorInfo();
    rightMotor.printMotorInfo();
}

void CarControl::setMotorDuty(float leftDuty, float rightDuty)
{
    leftMotor.setDuty(leftDuty);
    rightMotor.setDuty(rightDuty);
}

float CarControl::mapSpeed(float speed, float min, float max)
{
    return constrain(min + ((speed - 1) * (max - min)) / (50 - 1), min, max);
}
