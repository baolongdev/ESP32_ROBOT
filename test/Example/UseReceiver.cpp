#include <Receiver.h>
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

void setup()
{
    Serial.begin(115200);
    delay(1000);

    receiver.init(channels, numChannels);
}

void loop()
{
    for (uint8_t i = 0; i < 6; i++)
    {
        int16_t value = receiver.getChannelValue(i);
        Serial.print(value);
        Serial.print(", ");
    }
    Serial.println();
    delay(100);
}