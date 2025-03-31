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
    // Serial.println("🛑 Dừng lại!");
    leftMotor.setDuty(MOTOR_PWM_DEFAULT_DUTY);
    rightMotor.setDuty(MOTOR_PWM_DEFAULT_DUTY);
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
    if (speed < 1)
    {
        // Serial.println("⚠ Giá trị speed không hợp lệ! Nhập từ 1 đến 50.");
        stop();
        return;
    }
    float mappedSpeed = config.forwardMin +
                        ((speed - 1) * (config.forwardMax - config.forwardMin)) / (50 - 1);

    mappedSpeed = constrain(mappedSpeed, config.forwardMin, config.forwardMax);

    leftMotor.setDuty(mappedSpeed);
    rightMotor.setDuty(mappedSpeed);
    currentDirection = FORWARD;
}

void CarControl::moveBackward(float speed)
{
    if (speed > -1)
    {
        // Serial.println("⚠ Giá trị speed không hợp lệ! Nhập từ -1 đến -50.");
        stop();
        return;
    }

    float mappedSpeed = config.backwardMax -
                        ((abs(speed) - 1) * (config.backwardMax - config.backwardMin)) / (50 - 1);

    mappedSpeed = constrain(mappedSpeed, config.backwardMin, config.backwardMax);

    // Serial.print("🚗 Lùi lại với duty cycle: ");
    // Serial.println(mappedSpeed);

    leftMotor.setDuty(mappedSpeed);
    rightMotor.setDuty(mappedSpeed);
    currentDirection = BACKWARD;
}

void CarControl::turnLeft(float speed)
{
    // Serial.println("🔄 Rẽ trái...");
    leftMotor.setDuty(speed * 0.5);
    rightMotor.setDuty(speed);
}

void CarControl::turnRight(float speed)
{
    // Serial.println("🔄 Rẽ phải...");
    leftMotor.setDuty(speed);
    rightMotor.setDuty(speed * 0.5);
}

void CarControl::printCarInfo()
{
    // Serial.println("✅ Thông tin xe:");
    // Serial.print("📌 Hướng hiện tại: ");
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

    // Serial.println("🔹 Động cơ trái:");
    leftMotor.printMotorInfo();
    // Serial.println("🔹 Động cơ phải:");
    rightMotor.printMotorInfo();
}
