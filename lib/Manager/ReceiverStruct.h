#ifndef RECEIVER_STRUCTS_H
#define RECEIVER_STRUCTS_H

struct ChannelConfig
{
    uint8_t pin;     // Chân tín hiệu
    uint16_t minVal; // Giá trị tối thiểu
    uint16_t maxVal; // Giá trị tối đa
    bool isSwitch;   // true: công tắc, false: trượt
};

#endif // RECEIVER_STRUCTS_H
