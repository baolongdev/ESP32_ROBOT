#ifndef CAR_CONTROL_H
#define CAR_CONTROL_H

#include "MotorPWM.h"
#include "CarControlStruct.h"

class CarControl
{
private:
    MotorPWM leftMotor;
    MotorPWM rightMotor;
    Direction currentDirection;
    uint32_t lastStopTime;
    CarControlConfig config;

    bool isStopDelayOver(uint32_t delayTime);

public:
    CarControl();
    void init(const CarControlConfig &config);
    void moveForward(float speed);
    void moveBackward(float speed);
    void turnLeft(float speed);
    void turnRight(float speed);
    void stop();
    void smoothStop(uint32_t waitTime);

    void printCarInfo();
};

#endif
