//! GY-87 (MPU6050 + HMC5883L + BMP180)
#define GY87_SCL 1
#define GY87_SDA 2

//? Kích hoạt từng cảm biến trong module GY-87
#define ENABLE_MPU // MPU6050 (Gia tốc + con quay hồi chuyển)
#define ENABLE_MAG // HMC5883L (Cảm biến từ trường)
#define ENABLE_BMP // BMP180 (Cảm biến áp suất)

//? Địa chỉ I2C của MPU6050 và HMC5883L
#define MPU6050_ADDR 0x68
#define HMC5883L_ADDR 0x1E

//? Thanh ghi MPU6050
#define MPU6050_INT_PIN_CFG 0x37 // Cấu hình ngõ ra ngắt và I2C Bypass
#define MPU6050_USER_CTRL 0x6A   // Điều khiển các tính năng MPU6050
#define I2C_BYPASS_ENABLE 0x02   // Bật chế độ I2C Bypass Mode
#define I2C_MASTER_DISABLE 0x00  // Tắt chế độ I2C Master

//! Receiver
#define MAX_CHANNELS 8
#define DEFAULT_CHANNEL_VALUE 1500
// 📌 Ngưỡng tín hiệu cho công tắc 3 trạng thái (Switch)
#define SWITCH_LOW_THRESHOLD 1200
#define SWITCH_HIGH_THRESHOLD 1600
// #define DEBUG_RECEIVER
//! ESC
// Định nghĩa thông số mặc định cho PWM động cơ
#define MOTOR_PWM_DEFAULT_RES 12    // Độ phân giải mặc định (10-bit: 0-1023)
#define MOTOR_PWM_DEFAULT_FREQ 72   // Tần số PWM mặc định (Hz)
#define MOTOR_PWM_DEFAULT_DUTY 10.8 // Duty Cycle mặc định (%)
                                    //! Phiên bản cũ
                                    // #define MOTOR_PWM_DEFAULT_DUTY 11.14 // Duty Cycle mặc định (%) Phiên bản cũ

#define FORWARD_MIN 11.1
#define FORWARD_MAX 17.8
#define BACKWARD_MIN 5.38
#define BACKWARD_MAX 10.4
//? ESP cũ
// #define FORWARD_MIN 11.34
// #define FORWARD_MAX 17.2
// #define BACKWARD_MIN 4.6
// #define BACKWARD_MAX 10.8

// Định nghĩa chân điều khiển động cơ
#define LEFT_MOTOR_PIN 41
#define RIGHT_MOTOR_PIN 42

// Định nghĩa kênh PWM
#define LEFT_MOTOR_CHANNEL 0
#define RIGHT_MOTOR_CHANNEL 1

//! Stepper

//! Servo