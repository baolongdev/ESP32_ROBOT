#include "MotorPWM.h"
#include "config.h"

MotorPWM leftMotor;
MotorPWM rightMotor;

void motorSetDuty(float duty)
{
    leftMotor.setDuty(duty);
    rightMotor.setDuty(duty);
    Serial.print("Set Duty Cycle: ");
    Serial.println(duty);
}

void changePWMFrequency(float frequency)
{
    leftMotor.setFrequency(frequency);
    rightMotor.setFrequency(frequency);
    Serial.print("Set PWM Frequency: ");
    Serial.println(frequency);
}

void readSerialCommand()
{
    if (Serial.available())
    {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.startsWith("A ")) // Cập nhật Duty Cycle (%)
        {
            float dutyValue = input.substring(2).toFloat();
            motorSetDuty(dutyValue);
        }
        else if (input.startsWith("B ")) // Cập nhật Frequency (Hz)
        {
            float freqValue = input.substring(2).toFloat();
            changePWMFrequency(freqValue);
        }
    }
}

void setup()
{
    Serial.begin(115200);

    MotorPWMConfig leftConfig = {LEFT_MOTOR_PIN, LEFT_MOTOR_CHANNEL, MOTOR_PWM_DEFAULT_RES, MOTOR_PWM_DEFAULT_FREQ, MOTOR_PWM_DEFAULT_DUTY};
    MotorPWMConfig rightConfig = {RIGHT_MOTOR_PIN, RIGHT_MOTOR_CHANNEL, MOTOR_PWM_DEFAULT_RES, MOTOR_PWM_DEFAULT_FREQ, MOTOR_PWM_DEFAULT_DUTY};

    leftMotor.init(leftConfig);
    rightMotor.init(rightConfig);

    Serial.println("Motor PWM Initialized");
}

void loop()
{
    readSerialCommand();
}
