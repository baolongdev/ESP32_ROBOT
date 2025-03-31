#include "Arduino.h"
#include "PIDController.h"

PIDController pid(1.2, 0.5, 0.01, -100.0, 100.0); // Kp, Ki, Kd, minOutput, maxOutput

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    float setpoint = 50.0;              // Giá trị mong muốn
    float measurement = analogRead(A0); // Đọc cảm biến
    float dt = 0.1;                     // Giả sử thời gian cập nhật là 100ms

    float controlSignal = pid.compute(setpoint, measurement, dt);

    Serial.print("Output: ");
    Serial.println(controlSignal);

    delay(100);
}
