# Lab 1: Single Task vs Multitasking Demo

## วัตถุประสงค์
เปรียบเทียบระบบ Single Task กับ Multitasking เพื่อเข้าใจความแตกต่างในการตอบสนอง

## ไฟล์ในโปรเจกต์

### 💻 Code Files
- `main/single_task.c` - โปรแกรมแบบ Single Task
- `main/multitask.c` - โปรแกรมแบบ Multitasking
- `main/CMakeLists.txt` - Configuration สำหรับเลือกไฟล์ที่จะ compile

### 📚 Documentation Files
- [`BUILD_AND_FLASH.md`](BUILD_AND_FLASH.md) - 🔨 **คำสั่ง Build และ Flash (idf.py)**
- [`WIRING_GUIDE.md`](WIRING_GUIDE.md) - 🔌 **คู่มือการต่อสายแบบละเอียด**
- [`CIRCUIT_DIAGRAM.md`](CIRCUIT_DIAGRAM.md) - 🎨 **Diagram แบบละเอียด พร้อมภาพประกอบ**
- [`WOKWI_SIMULATION.md`](WOKWI_SIMULATION.md) - 🎮 **วิธีใช้ Wokwi Online Simulator**
- `diagram.json` - 🔧 **Wokwi Circuit File (import ได้เลย)**

## ⚠️ ก่อนเริ่ม: ต่อสาย Hardware

**กรุณาอ่านคู่มือการต่อสายก่อน:** [`WIRING_GUIDE.md`](WIRING_GUIDE.md)

### การต่อสายแบบสรุป:
```
GPIO2 ──→ [220Ω Resistor] ──→ LED1 (+) ──→ LED1 (-) ──→ GND
GPIO4 ──→ [220Ω Resistor] ──→ LED2 (+) ──→ LED2 (-) ──→ GND
GPIO0 ──→ ใช้ปุ่ม BOOT บน ESP32 (ไม่ต้องต่ออะไรเพิ่ม)
```

### 🌐 ทดสอบบน Wokwi (ไม่ต้องมี Hardware!)

**ไม่มี ESP32 จริง?** ไม่เป็นไร! ทดสอบออนไลน์ได้:

1. ไปที่ https://wokwi.com
2. สร้าง ESP32 project ใหม่
3. Import ไฟล์ `diagram.json` จากโฟลเดอร์นี้
4. Copy code จาก `main/single_task.c` หรือ `main/multitask.c`
5. กด Start Simulation!

👉 **รายละเอียดเพิ่มเติม:** อ่าน [`WOKWI_SIMULATION.md`](WOKWI_SIMULATION.md)

## การใช้งาน

### การทดสอบ Single Task System
1. แก้ไขไฟล์ `main/CMakeLists.txt`:
   ```cmake
   idf_component_register(SRCS "single_task.c" INCLUDE_DIRS ".")
   ```

2. Build และ Flash:
   ```bash
   idf.py build
   idf.py flash monitor
   ```

### การทดสอบ Multitasking System
1. แก้ไขไฟล์ `main/CMakeLists.txt`:
   ```cmake
   idf_component_register(SRCS "multitask.c" INCLUDE_DIRS ".")
   ```

2. Build และ Flash:
   ```bash
   idf.py build
   idf.py flash monitor
   ```

## การทดสอบ

### Single Task System
- สังเกตการทำงานของ LED ที่เป็นลำดับ
- กดปุ่ม (GPIO0) และสังเกตเวลาตอบสนอง
- บันทึกเวลาตอบสนองเมื่อกดปุ่ม (อาจช้ามาก 2-3 วินาที)

### Multitasking System
- สังเกตการทำงานของ LED ที่ทำงานพร้อมกัน
- กดปุ่ม (GPIO0) และสังเกตเวลาตอบสนอง
- เปรียบเทียบกับระบบ Single Task (ควรตอบสนองภายใน < 100ms)

## พิน GPIO ที่ใช้
- LED1: GPIO2 (Sensor simulation)
- LED2: GPIO4 (Actuator simulation)
- Button: GPIO0 (Emergency response test)

## คำถามสำหรับวิเคราะห์

1. ความแตกต่างในการตอบสนองปุ่มระหว่างทั้งสองระบบคืออะไร?
2. ใน Single Task System งานไหนที่ทำให้การตอบสนองล่าช้า?
3. ข้อดีของ Multitasking System ที่สังเกตได้คืออะไร?
4. มีข้อเสียของ Multitasking System ที่สังเกตได้หรือไม่?
5. ทำไม Emergency Task จึงมี Priority สูงสุด (Priority 5)?

## ผลการทดลองที่คาดหวัง

| ระบบ | เวลาตอบสนองปุ่ม | การทำงาน LED | CPU Utilization |
|------|-------------------|---------------|-----------------|
| Single Task | 2-3 วินาที | ทำงานเป็นลำดับ | 100% (blocking) |
| Multitasking | < 100ms | ทำงานพร้อมกัน | แบ่งกันใช้ |

## สิ่งที่ได้เรียนรู้
- ปัญหาของระบบ Single Task ในการตอบสนองเหตุการณ์
- ประโยชน์ของ Multitasking ในการปรับปรุงการตอบสนอง
- การใช้ Priority ใน FreeRTOS เพื่อจัดการงานที่มีความสำคัญต่างกัน
- การใช้ vTaskDelay() เพื่อให้ task อื่นได้รันด้วย

## เวลาที่ใช้
45 นาที

