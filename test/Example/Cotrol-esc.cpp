
#include <Receiver.h>
#include <CarControl.h>
#include "config.h"

Receiver receiver;
ChannelConfig channels[] = {
    {16, 0, 0, false},
    {15, 0, 0, false},
    {7, 0, 0, false},
    {6, 0, 0, false},
    {5, 0, 0, true},
    {4, 0, 0, true},
};
uint8_t numChannels = sizeof(channels) / sizeof(ChannelConfig);
MotorPWM leftMotor;
MotorPWM rightMotor;
MotorPWMConfig leftConfig = {LEFT_MOTOR_PIN, LEFT_MOTOR_CHANNEL, MOTOR_PWM_DEFAULT_RES, MOTOR_PWM_DEFAULT_FREQ, MOTOR_PWM_DEFAULT_DUTY};
MotorPWMConfig rightConfig = {RIGHT_MOTOR_PIN, RIGHT_MOTOR_CHANNEL, MOTOR_PWM_DEFAULT_RES, MOTOR_PWM_DEFAULT_FREQ, MOTOR_PWM_DEFAULT_DUTY};

CarControl carControl;
CarControlConfig carControlConfig = {
    leftConfig,
    rightConfig,
    FORWARD_MIN,
    FORWARD_MAX,
    BACKWARD_MIN,
    BACKWARD_MAX,
};

void setup()
{
    Serial.begin(115200);
    delay(1000);

    receiver.init(channels, numChannels);
    carControl.init(carControlConfig);
}

void loop()
{
    int16_t throttle = receiver.getChannelValue(1);

    if (throttle > 1) // Tiến
    {
        carControl.moveForward(throttle);
    }
    else if (throttle < -1) // Lùi
    {
        carControl.moveBackward(throttle);
    }
    else
    {
        carControl.stop();
    }
}