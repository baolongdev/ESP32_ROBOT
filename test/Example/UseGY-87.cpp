#include "config.h"
#include "SensorManager.h"

SensorManager sensorManager;
SensorData data;
void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("Start GY-87 Test");
    sensorManager.begin(true, true, false);
}
void loop()
{
    sensorManager.calculateAngles(data);
    Serial.print((int)data.roll);
    Serial.print(",");
    Serial.print((int)data.pitch);
    Serial.print(",");
    Serial.println((int)data.yaw);

    delay(10);
}