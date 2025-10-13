# รายงานการทดลอง: FreeRTOS Overview

**นักศึกษา:** 67030011  
**วิชา:** FreeRTOS Workshop  
**หัวข้อ:** 01 - FreeRTOS Overview และการเริ่มต้นใช้งาน ESP-IDF  
**วันที่เริ่ม:** 8 ตุลาคม 2025

---

## 📋 สารบัญ

- [Lab 1: ESP-IDF Setup และโปรเจกต์แรก](lab1-setup-first-project/)
- [Lab 2: Hello World และ Serial Communication](lab2-hello-world/) (รอดำเนินการ)
- [Lab 3: สร้าง Task แรกด้วย FreeRTOS](lab3-first-task/) (รอดำเนินการ)

---

## 🎯 วัตถุประสงค์

การทดลองชุดนี้มีวัตถุประสงค์เพื่อ:
1. ติดตั้งและตรวจสอบการทำงานของ ESP-IDF
2. ทำความเข้าใจโครงสร้างโปรเจกต์ ESP-IDF
3. สร้างและจัดการ Task พื้นฐานด้วย FreeRTOS
4. ใช้เครื่องมือ Serial Monitor เพื่อ debug
5. เข้าใจ FreeRTOS APIs พื้นฐาน

---

## 🛠️ เครื่องมือและอุปกรณ์

### Hardware:
- ESP32 Development Board
- USB Cable (รองรับการส่งข้อมูล)
- คอมพิวเตอร์ (macOS/Linux/Windows)

### Software:
- ESP-IDF v5.x
- Python 3.7+
- Git
- Terminal/Command Prompt

---

## 📊 ความคืบหน้า

| Lab | หัวข้อ | สถานะ | เวลาที่ใช้ | หมายเหตุ |
|-----|--------|-------|-----------|----------|
| 1 | ESP-IDF Setup และโปรเจกต์แรก | ✅ เสร็จสิ้น | - นาที | - |
| 2 | Hello World และ Serial Communication | ⏳ กำลังดำเนินการ | - นาที | - |
| 3 | สร้าง Task แรกด้วย FreeRTOS | ⏸️ รอดำเนินการ | - นาที | - |

**Legend:**
- ✅ เสร็จสิ้น
- ⏳ กำลังดำเนินการ
- ⏸️ รอดำเนินการ
- ❌ พบปัญหา

---

## 📝 สรุปผลการเรียนรู้

### Lab 1: ESP-IDF Setup และโปรเจกต์แรก

**สิ่งที่ได้เรียนรู้:**
- โครงสร้างโปรเจกต์ ESP-IDF ประกอบด้วย CMakeLists.txt และโฟลเดอร์ main
- ฟังก์ชัน `app_main()` เป็นจุดเริ่มต้นของโปรแกรม
- `vTaskDelay()` ใช้หน่วงเวลาแบบไม่ block CPU
- คำสั่ง `idf.py` เป็นเครื่องมือหลักในการ build และ flash

**ปัญหาที่พบ:**
- [บันทึกปัญหาที่พบ]

**วิธีแก้ไข:**
- [บันทึกวิธีแก้ไข]

---

### Lab 2: Hello World และ Serial Communication

**สิ่งที่ได้เรียนรู้:**
- [รอบันทึก]

**ปัญหาที่พบ:**
- [รอบันทึก]

---

### Lab 3: สร้าง Task แรกด้วย FreeRTOS

**สิ่งที่ได้เรียนรู้:**
- [รอบันทึก]

**ปัญหาที่พบ:**
- [รอบันทึก]

---

## 🔍 แนวคิดสำคัญ

### 1. FreeRTOS Basics
- **Task:** หน่วยของการทำงานที่สามารถทำงานแบบ concurrent
- **Scheduler:** ตัวจัดการที่กำหนดว่า Task ไหนควรทำงานเมื่อไหร่
- **Delay:** การหน่วงเวลาที่ไม่ block CPU

### 2. ESP-IDF Project Structure
```
project/
├── CMakeLists.txt       # Root build configuration
├── main/
│   ├── CMakeLists.txt  # Component configuration
│   └── main.c          # Main source code
├── sdkconfig           # Project settings (generated)
└── build/              # Build output (generated)
```

### 3. Key Functions
- `app_main()`: Entry point
- `vTaskDelay()`: Non-blocking delay
- `esp_get_idf_version()`: Get ESP-IDF version
- `esp_get_free_heap_size()`: Get available memory

---

## ❓ คำถามและคำตอบ

### Q1: ทำไมต้องใช้ `vTaskDelay()` แทน delay loop?
**A:**
```
[เขียนคำตอบ]
```

### Q2: `pdMS_TO_TICKS()` คืออะไร?
**A:**
```
[เขียนคำตอบ]
```

### Q3: ความแตกต่างระหว่าง .bin และ .elf คืออะไร?
**A:**
```
[เขียนคำตอบ]
```

---

## 📈 สถิติการทำงาน

- **เวลารวมที่ใช้:** - ชั่วโมง - นาที
- **จำนวนครั้งที่ build:** - ครั้ง
- **จำนวนครั้งที่ flash:** - ครั้ง
- **ปัญหาที่พบ:** - ปัญหา
- **ปัญหาที่แก้ไขได้:** - ปัญหา

---

## 💡 บทเรียนที่ได้

1. **การวางแผน:**
   - [บันทึกบทเรียน]

2. **การ Debug:**
   - [บันทึกบทเรียน]

3. **Best Practices:**
   - [บันทึกบทเรียน]

---

## 🎓 ทักษะที่ได้รับ

- [ ] การติดตั้งและใช้งาน ESP-IDF
- [ ] การสร้างและ build โปรเจกต์
- [ ] การ flash และ monitor โปรแกรม
- [ ] การใช้ Serial Communication
- [ ] การสร้างและจัดการ Task
- [ ] การใช้ FreeRTOS APIs

---

## 📚 อ้างอิง

1. [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/)
2. [FreeRTOS Kernel Book](https://www.freertos.org/Documentation/RTOS_book.html)
3. [ESP32 Technical Reference Manual](https://www.espressif.com/en/support/documents/technical-documents)

---

## 📌 หมายเหตุ

- โปรเจกต์ทั้งหมดใช้ ESP-IDF v5.x
- Target chip: ESP32 (xtensa architecture)
- บันทึกนี้จะอัพเดทตามความคืบหน้าของการทำแลป

---

**สถานะรายงาน:** 🟡 กำลังดำเนินการ  
**อัพเดทล่าสุด:** 8 ตุลาคม 2025
