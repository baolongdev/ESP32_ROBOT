#include "SensorManager.h"

// Constructor
SensorManager::SensorManager() {}

void SensorManager::begin(bool enableMPU, bool enableMag, bool enableBMP)
{
    Serial.begin(115200);
    Wire.begin(GY87_SDA, GY87_SCL);
    Wire.setClock(400000);

    if (enableMPU)
        initMPU6050();
    if (enableMag)
        initHMC5883L();
    if (enableBMP)
        initBMP180();
}

// Khởi tạo MPU6050
void SensorManager::initMPU6050()
{
    if (!mpu.begin())
    {
        Serial.println("Lỗi: Không tìm thấy MPU6050!");
        while (1)
            ;
    }
    Serial.println("MPU6050 OK!");
}

// Khởi tạo HMC5883L
void SensorManager::initHMC5883L()
{
    enable_HMC5883L_via_MPU6050(); // Bật chế độ Bypass trên MPU6050
    delay(100);
    if (!mag.begin())
    {
        Serial.println("Lỗi: Không tìm thấy HMC5883L!");
        while (1)
            ;
    }
    Serial.println("HMC5883L OK!");
}

// Khởi tạo BMP180
void SensorManager::initBMP180()
{
    if (!bmp.begin())
    {
        Serial.println("Lỗi: Không tìm thấy BMP180!");
        while (1)
            ;
    }
    Serial.println("BMP180 OK!");
}

// Đọc dữ liệu từ MPU6050
void SensorManager::readMPU6050(MPUData &mpuData)
{
    sensors_event_t a, g, temp;
    mpu.getAccelerometerSensor()->getEvent(&a);
    mpu.getGyroSensor()->getEvent(&g);

    mpuData.accX = a.acceleration.x;
    mpuData.accY = a.acceleration.y;
    mpuData.accZ = a.acceleration.z;

    mpuData.gyroX = g.gyro.x;
    mpuData.gyroY = g.gyro.y;
    mpuData.gyroZ = g.gyro.z;
}

// Đọc dữ liệu từ HMC5883L
void SensorManager::readHMC5883L(MAGData &magData)
{
    sensors_event_t event;
    mag.getEvent(&event);

    magData.magX = event.magnetic.x;
    magData.magY = event.magnetic.y;
    magData.magZ = event.magnetic.z;
}

// Đọc dữ liệu từ BMP180
void SensorManager::readBMP180(BMPData &bmpData)
{
    bmpData.temperature = bmp.readTemperature();
    bmpData.pressure = bmp.readPressure();
    bmpData.altitude = bmp.readAltitude();
}

// Tính toán Roll, Pitch từ MPU6050 và Yaw từ HMC5883L
void SensorManager::calculateAngles(SensorData &data)
{
    // Lấy dữ liệu từ MPU6050
    readMPU6050(data.mpu);
    readHMC5883L(data.mag);

    // Tính Roll và Pitch từ gia tốc kế
    float rollAcc = atan2(data.mpu.accY, data.mpu.accZ) * 180.0 / M_PI;
    float pitchAcc = atan2(-data.mpu.accX, sqrt(data.mpu.accY * data.mpu.accY + data.mpu.accZ * data.mpu.accZ)) * 180.0 / M_PI;

    // Tính dt
    unsigned long currentMicros = micros();
    dt = (currentMicros - lastTime) / 1e6; // Chuyển micro giây sang giây
    lastTime = currentMicros;

    // Lọc Kalman cho Roll và Pitch
    data.roll = kalmanX.update(rollAcc, data.mpu.gyroX, dt);
    data.pitch = kalmanY.update(pitchAcc, data.mpu.gyroY, dt);

    // Bù nghiêng cho từ kế (Hiệu chỉnh Roll, Pitch trước khi tính Yaw)
    float cosPitch = cos(data.pitch * M_PI / 180.0);
    float sinPitch = sin(data.pitch * M_PI / 180.0);
    float cosRoll = cos(data.roll * M_PI / 180.0);
    float sinRoll = sin(data.roll * M_PI / 180.0);

    float magX = data.mag.magX * cosPitch + data.mag.magZ * sinPitch;
    float magY = data.mag.magX * sinRoll * sinPitch + data.mag.magY * cosRoll - data.mag.magZ * sinRoll * cosPitch;

    // Tính Yaw từ Magnetometer
    float yawMag = atan2(-magY, magX) * 180.0 / M_PI;
    // yawMag = normalizeAngle(yawMag);

    // Lọc Kalman cho Yaw
    data.yaw = kalmanZ.update(yawMag, data.mpu.gyroZ, dt);
    // data.yaw = normalizeAngle(data.yaw);
    if (data.yaw < 0)
        data.yaw += 360.0;
}

// Chuẩn hóa góc về [-180, 180] hoặc [0, 360]
float SensorManager::normalizeAngle(float angle)
{
    return fmod(angle + 180.0, 360.0) - 180.0;
}

// Kích hoạt HMC5883L thông qua MPU6050
void SensorManager::enable_HMC5883L_via_MPU6050()
{
    sensor_write_reg_single(MPU6050_ADDR, MPU6050_INT_PIN_CFG, I2C_BYPASS_ENABLE); // Bật I2C Bypass mode
    sensor_write_reg_single(MPU6050_ADDR, MPU6050_USER_CTRL, I2C_MASTER_DISABLE);  // Tắt Master I2C Mode
}
