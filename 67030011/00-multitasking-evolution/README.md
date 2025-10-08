# 00. วิวัฒนาการของ Multitasking ในไมโครคอนโทรลเลอร์

**รหัสนักศึกษา:** 67030011

## 📋 ภาพรวม

โฟลเดอร์นี้ประกอบด้วย 3 labs ที่จะพาคุณเรียนรู้เกี่ยวกับวิวัฒนาการของ Multitasking:

1. **Lab 1** - Single Task vs Multitasking Demo
2. **Lab 2** - Time-Sharing Implementation  
3. **Lab 3** - Cooperative vs Preemptive Comparison

## 🗂️ โครงสร้างโฟลเดอร์

```
67030011/00-multitasking-evolution/
├── README.md                          ← ไฟล์นี้
├── REPORT.md                          ← รายงานการทดลองรวม (กรอกหลังทำ lab เสร็จ)
│
├── lab1-single-vs-multi/              ← Lab 1: Single Task vs Multitasking
│   ├── README.md                      - คู่มือการใช้งาน Lab 1
│   ├── WIRING_GUIDE.md               - 🔌 คู่มือการต่อสายแบบละเอียด
│   ├── CIRCUIT_DIAGRAM.md            - 🎨 Diagram พร้อมภาพประกอบ
│   ├── WOKWI_SIMULATION.md           - 🎮 วิธีใช้ Online Simulator
│   ├── diagram.json                   - 🔧 Wokwi circuit file
│   ├── CMakeLists.txt                 - ESP-IDF project config
│   └── main/
│       ├── CMakeLists.txt             - Component config
│       ├── single_task.c              - โปรแกรม Single Task
│       └── multitask.c                - โปรแกรม Multitasking
│
├── lab2-time-sharing/                 ← Lab 2: Time-Sharing
│   ├── README.md                      - คู่มือการใช้งาน Lab 2
│   ├── CMakeLists.txt                 - ESP-IDF project config
│   └── main/
│       ├── CMakeLists.txt             - Component config
│       └── time_sharing.c             - โปรแกรม Time-Sharing
│
└── lab3-coop-vs-preemptive/          ← Lab 3: Cooperative vs Preemptive
    ├── README.md                      - คู่มือการใช้งาน Lab 3
    ├── CMakeLists.txt                 - ESP-IDF project config
    └── main/
        ├── CMakeLists.txt             - Component config
        └── multitask_comparison.c     - โปรแกรมเปรียบเทียบ
```

## 🚀 Quick Start Guide

### เริ่มต้นใช้งาน

1. **อ่านทฤษฎีก่อน** (แนะนำ)
   - ไปที่ `/00-multitasking-evolution/theory.md` ในโฟลเดอร์หลัก
   - เข้าใจพื้นฐานก่อนเริ่มทำ lab

2. **เลือก Lab ที่ต้องการ**
   - เริ่มจาก Lab 1 ตามลำดับ
   - แต่ละ lab มี README.md เป็นของตัวเอง

3. **ต่อสาย Hardware** (Lab 1 และ 3)
   - อ่าน WIRING_GUIDE.md ในแต่ละ lab
   - หรือทดสอบบน Wokwi ก่อน (ไม่ต้องมี hardware)

4. **Build และ Flash**
   ```bash
   cd lab1-single-vs-multi
   idf.py build
   idf.py flash monitor
   ```

5. **บันทึกผล**
   - กรอกข้อมูลใน `REPORT.md`
   - ถ่ายรูปการทดลอง (ถ้ามี)

## 📚 รายละเอียดแต่ละ Lab

### Lab 1: Single Task vs Multitasking Demo
⏱️ **เวลา:** 45 นาที

**สิ่งที่จะได้เรียนรู้:**
- ปัญหาของระบบ Single Task
- ประโยชน์ของ Multitasking
- การใช้ Priority ใน FreeRTOS

**Hardware ที่ต้องใช้:**
- ESP32 Board
- LED 2 ดวง
- Resistor 220Ω × 2
- Push Button (หรือใช้ BOOT button บนบอร์ด)

**ไฟล์สำคัญ:**
- 🔰 `WIRING_GUIDE.md` - คู่มือต่อสายแบบละเอียด
- 🎨 `CIRCUIT_DIAGRAM.md` - Diagram พร้อมภาพประกอบ
- 🎮 `WOKWI_SIMULATION.md` - ทดสอบแบบออนไลน์

### Lab 2: Time-Sharing Implementation
⏱️ **เวลา:** 45 นาที

**สิ่งที่จะได้เรียนรู้:**
- Time-Sharing และ Context Switching
- CPU Utilization และ Overhead
- ปัญหาของ Fixed Time Slice

**Hardware ที่ต้องใช้:**
- ESP32 Board
- LED 4 ดวง
- Resistor 220Ω × 4

### Lab 3: Cooperative vs Preemptive
⏱️ **เวลา:** 30 นาที

**สิ่งที่จะได้เรียนรู้:**
- Cooperative Multitasking
- Preemptive Multitasking
- ข้อดี-ข้อเสียของแต่ละแบบ
- Response Time Comparison

**Hardware ที่ต้องใช้:**
- ESP32 Board
- LED 3 ดวง
- Resistor 220Ω × 3
- Push Button (หรือใช้ BOOT button)

## 🎯 Learning Objectives

เมื่อทำ labs ทั้งหมดเสร็จ คุณจะสามารถ:

- ✅ อธิบายวิวัฒนาการของ Multitasking ได้
- ✅ เข้าใจปัญหาของระบบ Single Task
- ✅ เข้าใจ Time-Sharing และ Context Switching
- ✅ เปรียบเทียบ Cooperative vs Preemptive ได้
- ✅ เลือกเทคนิคที่เหมาะสมสำหรับแต่ละงานได้
- ✅ ใช้ FreeRTOS เบื้องต้นได้

## 🛠️ เครื่องมือที่ใช้

### Software
- **ESP-IDF** - Framework สำหรับ ESP32
- **FreeRTOS** - Real-Time Operating System
- **VS Code** - Text Editor (แนะนำ)
- **Wokwi** - Online Simulator (ไม่บังคับ)

### Hardware
- **ESP32 Development Board** - ตัวหลัก
- **LEDs** - สำหรับแสดงผล
- **Resistors 220Ω** - จำกัดกระแส LED
- **Breadboard** - สำหรับต่อวงจร
- **Jumper Wires** - สายต่อ
- **USB Cable** - ต่อกับคอมพิวเตอร์

## 📊 ตารางเปรียบเทียบ

| เทคนิค | Response Time | Resource Usage | Complexity | Real-time |
|--------|---------------|----------------|------------|-----------|
| **Single Task** | Poor | Low | Low | ❌ Poor |
| **Time-Sharing** | Medium | Medium | Medium | ⚠️ Medium |
| **Cooperative** | Variable | Low | Medium | ⚠️ Medium |
| **Preemptive** | Excellent | High | High | ✅ Excellent |

## 🌐 ทดสอบออนไลน์ (ไม่มี Hardware)

ไม่มี ESP32? ไม่เป็นไร! ทดสอบได้บน **Wokwi Online Simulator**

### วิธีใช้:
1. ไปที่ https://wokwi.com
2. สร้าง ESP32 project
3. Import `diagram.json` จาก lab1
4. Copy code และ run!

👉 ดูคู่มือเพิ่มเติม: `lab1-single-vs-multi/WOKWI_SIMULATION.md`

## 📝 รายงานการทดลอง

หลังทำ labs เสร็จแล้ว อย่าลืม:

1. **กรอก REPORT.md**
   - บันทึกผลการทดลอง
   - ตอบคำถาม
   - วิเคราะห์ผล

2. **ถ่ายรูป** (ถ้าทำจริง)
   - วงจรที่ต่อ
   - LED กระพริบ
   - Serial Monitor

3. **สรุปสิ่งที่ได้เรียนรู้**

## 🐛 Troubleshooting

### ปัญหาทั่วไป

**Q: Build error - ESP-IDF not found**
```bash
# ตรวจสอบว่าติดตั้ง ESP-IDF แล้ว
idf.py --version

# ถ้ายังไม่มี ติดตั้งก่อน
# https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/
```

**Q: LED ไม่ติด**
- ✅ ตรวจสอบขั้ว LED (ขายาว = +)
- ✅ ตรวจสอบว่ามี Resistor
- ✅ ตรวจสอบ GPIO pins ถูกต้อง

**Q: Serial Monitor ไม่แสดงผล**
```bash
# ลองใหม่ด้วย
idf.py monitor -p /dev/ttyUSB0  # Linux
idf.py monitor -p COM3           # Windows
```

**Q: ปุ่มไม่ทำงาน**
- ✅ ใช้ปุ่ม BOOT บนบอร์ด (แนะนำ)
- ✅ ตรวจสอบว่า GPIO0 ถูกต้อง

## 📖 เอกสารอ้างอิง

- [FreeRTOS Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Wokwi ESP32 Simulator](https://docs.wokwi.com/guides/esp32)

## 💡 Tips

1. **อ่านทฤษฎีก่อน** - จะเข้าใจ lab มากขึ้น
2. **ทำตามลำดับ** - Lab 1 → Lab 2 → Lab 3
3. **ทดสอบบน Wokwi ก่อน** - ถ้าไม่มั่นใจ
4. **บันทึกผลการทดลอง** - จะได้ไม่ลืม
5. **ถ่ายรูป/วีดีโอ** - แสดงการทำงาน

## ⏱️ เวลารวม

- Lab 1: 45 นาที
- Lab 2: 45 นาที
- Lab 3: 30 นาที
- **รวม: 2 ชั่วโมง**

## ✅ Checklist

ก่อนเริ่ม:
- [ ] อ่าน theory.md แล้ว
- [ ] ติดตั้ง ESP-IDF แล้ว
- [ ] มี ESP32 และอุปกรณ์ครบ (หรือใช้ Wokwi)

ระหว่างทำ:
- [ ] ทำ Lab 1 เสร็จ
- [ ] ทำ Lab 2 เสร็จ
- [ ] ทำ Lab 3 เสร็จ
- [ ] บันทึกผลการทดลอง

หลังเสร็จ:
- [ ] กรอก REPORT.md
- [ ] ตอบคำถามทุกข้อ
- [ ] สรุปสิ่งที่ได้เรียนรู้

## 🎓 สรุป

การเรียนรู้ในหัวข้อนี้จะช่วยให้คุณเข้าใจ:
- **ทำไม** เราต้องมี RTOS
- **อย่างไร** Multitasking ทำงาน
- **เมื่อไหร่** ควรใช้เทคนิคแบบไหน

เตรียมพร้อมแล้ว? เริ่มจาก Lab 1 กันเลย! 🚀

---

**หมายเหตุ:** หากมีปัญหาหรือข้อสงสัย สามารถดูคู่มือในแต่ละ lab หรือถามอาจารย์ผู้สอนได้ครับ

