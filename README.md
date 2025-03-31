# ESP32_ROBOT

## Giới thiệu
ESP32_ROBOT là một dự án sử dụng vi điều khiển ESP32 để điều khiển robot. Dự án hỗ trợ các tính năng như điều khiển động cơ, đọc cảm biến, và giao tiếp qua giao thức I2C. Các thư viện custom được thiết kế để tối ưu hóa hiệu suất và dễ dàng tích hợp.

---

## Yêu cầu hệ thống

### Phần cứng
- **Vi điều khiển**: ESP32 DevKit
- **Động cơ**: Động cơ DC hoặc Servo
- **Cảm biến**: 
  - MPU6050 (Gia tốc kế và con quay hồi chuyển)
  - HMC5883L (Cảm biến từ trường)
  - BMP180 (Cảm biến áp suất)
- **Nguồn điện**: Pin hoặc nguồn điện phù hợp
- **Các linh kiện khác**: Dây nối, module điều khiển ESC, v.v.

### Phần mềm
- **Arduino IDE**: Phiên bản mới nhất ([Tải tại đây](https://www.arduino.cc/en/software))
- **Thư viện ESP32**: Cài đặt qua Board Manager
- **Thư viện bổ sung**:
  - Adafruit BMP085
  - Adafruit MPU6050
  - Adafruit HMC5883_U
  - Kalman Filter (tích hợp trong dự án)

---

## Thông tin các thư viện sử dụng

### Thư viện bên thứ ba
- **Adafruit BMP085**: Đọc dữ liệu áp suất từ cảm biến BMP180.
- **Adafruit MPU6050**: Đọc dữ liệu gia tốc và con quay hồi chuyển.
- **Adafruit HMC5883_U**: Đọc dữ liệu từ cảm biến từ trường HMC5883L.

### Thư viện custom
1. **CarControl**:
   - Điều khiển chuyển động của robot (tiến, lùi, rẽ trái, rẽ phải).
   - Hỗ trợ dừng mượt mà và cấu hình động cơ.
2. **MotorPWM**:
   - Điều khiển động cơ bằng PWM.
   - Hỗ trợ thay đổi tần số và duty cycle.
3. **SensorManager**:
   - Quản lý và đọc dữ liệu từ các cảm biến (MPU6050, HMC5883L, BMP180).
   - Tính toán góc nghiêng và định hướng.
4. **I2c_interface**:
   - Giao tiếp I2C với các thiết bị ngoại vi.
5. **ProcessData**:
   - Xử lý dữ liệu từ cảm biến và bộ thu tín hiệu.
6. **Receiver**:
   - Quản lý tín hiệu từ bộ thu điều khiển từ xa.

---

## Hướng dẫn sử dụng các thư viện custom

### 1. **CarControl**
- **Khởi tạo**:
  ```cpp
    CarControl carControl;
    carControl.init(carControlConfig);
  ```
- **Chức năng chính**:
- `moveForward(speed)`: Di chuyển tiến với tốc độ `speed`.
- `moveBackward(speed)`: Di chuyển lùi với tốc độ `speed`.
- `turnLeft(speed)`: Rẽ trái với tốc độ `speed`.
- `turnRight(speed)`: Rẽ phải với tốc độ `speed`.
- `stop()`: Dừng robot ngay lập tức.


### 2. **MotorPWM**
- **Khởi tạo**:
  ```cpp
    MotorPWM motor;
    motor.init(motorConfig);
  ```
- **Chức năng chính**:
- `setDuty(duty)`: Cài đặt hệ số nhiệm vụ (duty cycle) của PWM (%), giá trị từ 0 đến 100.
- `setFrequency(frequency)`: Thay đổi tần số xung PWM (Hz) để điều chỉnh tốc độ động cơ.
- `getDuty()`: Lấy giá trị duty cycle hiện tại.
- `getFrequency()`: Lấy tần số PWM hiện tại.
- `printMotorInfo()`: Xuất thông tin cấu hình động cơ ra Serial Monitor.


### 3. **SensorManager**
- **Khởi tạo**:
  ```cpp
    SensorManager sensorManager;
    sensorManager.begin(true, true, true); // Bật các cảm biến
  ```
- **Chức năng chính**:
- `readMPU6050(data)`: Đọc dữ liệu từ MPU6050.
- `readHMC5883L(data)`: Đọc dữ liệu từ HMC5883L.
- `readBMP180(data)`: Đọc dữ liệu từ BMP180.
- `calculateAngles(data)`: Tính toán góc nghiêng. 

### 4. **I2c_interface**
- **Khởi tạo**:
  ```cpp
    I2cInterface i2c;
    i2c.init();
  ```
- **Chức năng chính**:
- `readRegister()`: Đọc dữ liệu từ thanh ghi.
- `writeRegister(addr, reg, data)`: Ghi dữ liệu vào thanh ghi `reg` của thiết bị có địa chỉ `addr`.


### **Tác Giả**  
Code được phát triển bởi [Lê Bảo Long (baolongdev)](https://github.com/baolongdev).  
Mọi ý kiến đóng góp xin gửi về: [24520998@gm.uit.edu.vn](mailto:24520998@gm.uit.edu.vn).
