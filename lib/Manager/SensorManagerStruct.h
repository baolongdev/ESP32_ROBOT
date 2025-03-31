#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

struct MPUData
{
    float accX, accY, accZ;
    float gyroX, gyroY, gyroZ;
    float roll, pitch, yaw;
};

struct MAGData
{
    float magX, magY, magZ;
};

struct BMPData
{
    float temperature;
    float pressure;
    float altitude;
};

struct SensorData
{
    MPUData mpu;
    MAGData mag;
    BMPData bmp;
    float roll, pitch, yaw;
};

#endif // SENSOR_DATA_H
