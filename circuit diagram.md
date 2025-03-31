Dưới đây là phần bổ sung cho README.md về sơ đồ mạch của dự án **ESP32_ROBOT**:

---

## Sơ đồ mạch

### **Tổng quan**
Dưới đây là sơ đồ mạch kết nối giữa ESP32 và các thành phần phần cứng như động cơ, cảm biến và bộ thu tín hiệu. Mạch bao gồm các mô-đun chính:

1. **ESP32-S3-WROOM-1**: Vi điều khiển chính, điều khiển các thiết bị ngoại vi.
2. **Receiver (Bộ thu tín hiệu)**: Nhận lệnh điều khiển từ xa, kết nối với ESP32 qua các chân tín hiệu.
3. **Servo**: Điều khiển các cơ cấu chấp hành, kết nối với ESP32 qua PWM.
4. **Stepper Motor (Động cơ bước)**: Sử dụng driver A4988 để điều khiển động cơ bước.
5. **GY-87 (Cảm biến IMU)**: Gồm các cảm biến MPU6050 (gia tốc, con quay hồi chuyển), HMC5883L (từ trường), BMP180 (áp suất).
6. **ESC (Bộ điều tốc điện tử)**: Điều khiển động cơ không chổi than (BLDC).

### **Hình ảnh sơ đồ mạch**
![Sơ đồ mạch ESP32_ROBOT](./doc/main.pdf)

### **Kết nối phần cứng**

#### **1. ESP32-S3-WROOM-1**
- Chân nguồn:
  - **3V3**: Cấp nguồn 3.3V cho các thiết bị ngoại vi.
  - **GND**: Mass chung cho toàn hệ thống.
- Chân giao tiếp:
  - **GPIO 35, 36**: Điều khiển Servo.
  - **GPIO 45, 48, 47**: Điều khiển Stepper thông qua driver A4988.
  - **GY1, GY2**: Giao tiếp với cảm biến GY-87.
  - **ESC1, ESC2**: Điều khiển bộ điều tốc ESC.
  - **Re1 - Re6**: Nhận tín hiệu từ bộ thu Receiver.

#### **2. Stepper Motor với Driver A4988**
- **Nguồn cấp**:
  - **+12V**: Cấp nguồn cho động cơ bước.
  - **3.3V**: Cấp nguồn tín hiệu điều khiển từ ESP32.
- **Tín hiệu điều khiển**:
  - **Step, Dir**: Điều khiển hướng quay và số bước di chuyển.
  - **MS1, MS2, MS3**: Cấu hình chế độ vi bước.

#### **3. Servo**
- **Nguồn cấp**: 3.3V hoặc 5V tùy loại servo.
- **Tín hiệu điều khiển**: GPIO 35, 36.

#### **4. Cảm biến GY-87**
- **Nguồn cấp**: 3.3V.
- **Giao tiếp**: I2C (SDA, SCL).

#### **5. ESC (Điều khiển BLDC)**
- **Nguồn cấp**: 3.3V (tín hiệu), 12V (nguồn chính cho động cơ).
- **Tín hiệu điều khiển**: ESC1, ESC2.

---

Phần này giúp tài liệu README.md của bạn rõ ràng hơn về sơ đồ mạch và cách kết nối phần cứng. Nếu bạn muốn bổ sung chi tiết nào khác, hãy cho mình biết nhé! 🚀