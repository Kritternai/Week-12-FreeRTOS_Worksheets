# Lab 1: ESP-IDF Setup และโปรเจกต์แรก

**นักศึกษา:** [67030011]  
**วันที่:** 8 ตุลาคม 2025

## วัตถุประสงค์
- ติดตั้งและตรวจสอบการทำงานของ ESP-IDF
- สร้างโปรเจกต์แรกด้วย ESP-IDF
- ทำความเข้าใจโครงสร้างโปรเจกต์และการ build

## เวลาที่ใช้
45 นาที

## ขั้นตอนการทดลอง

### Part 1: ตรวจสอบการติดตั้ง ESP-IDF

```bash
# 1. ตรวจสอบ ESP-IDF environment
echo $IDF_PATH

# 2. ตรวจสอบเวอร์ชัน
idf.py --version

# 3. ตรวจสอบ toolchain
xtensa-esp32-elf-gcc --version
```

**ผลลัพธ์:**
```
[บันทึกผลลัพธ์ที่ได้ที่นี่]
```

### Part 2: Build และ Flash โปรเจกต์

```bash
# 1. เข้าไปที่โฟลเดอร์โปรเจกต์
cd /Users/kbbk/Week-12-FreeRTOS_Worksheets/67030011/01-freertos-overview/lab1-setup-first-project

# 2. กำหนด target chip
idf.py set-target esp32

# 3. Build โปรเจกต์
idf.py build

# 4. Flash และ monitor
idf.py flash monitor
```

### Part 3: ศึกษาโค้ด

**ไฟล์ `main/hello_esp32.c`:**

โค้ดนี้ทำอะไร:
- แสดงข้อความ "My First ESP32 Project"
- แสดงเวอร์ชัน ESP-IDF
- แสดง Free heap memory
- นับเวลาทุกๆ 1 วินาที

**คำอธิบายฟังก์ชันสำคัญ:**
- `app_main()`: จุดเริ่มต้นของโปรแกรม ESP-IDF
- `printf()`: แสดงข้อความ
- `esp_get_idf_version()`: ดึงข้อมูลเวอร์ชัน ESP-IDF
- `esp_get_free_heap_size()`: ดึงข้อมูล memory ว่าง
- `vTaskDelay()`: หน่วงเวลาแบบ FreeRTOS (ไม่ block CPU)

## ผลการทดลอง

### Output จาก Serial Monitor:

```
[บันทึก output ที่ได้จาก serial monitor]
```

### Screenshot (ถ้ามี):

[วางภาพหน้าจอที่นี่]

## Exercise 1: เพิ่ม Build Information

สร้างไฟล์ `main/build_info.h`:

```c
#ifndef BUILD_INFO_H
#define BUILD_INFO_H

#define PROJECT_NAME "Hello ESP32"
#define PROJECT_VERSION "1.0.0"
#define STUDENT_ID "67030011"
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__

#endif
```

แก้ไข `main/hello_esp32.c`:

```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "build_info.h"

void app_main(void)
{
    printf("=== %s v%s ===\n", PROJECT_NAME, PROJECT_VERSION);
    printf("Student ID: %s\n", STUDENT_ID);
    printf("Built on: %s %s\n", BUILD_DATE, BUILD_TIME);
    printf("ESP-IDF Version: %s\n", esp_get_idf_version());
    printf("Chip: %s\n", CONFIG_IDF_TARGET);
    printf("Free heap: %ld bytes\n", esp_get_free_heap_size());
    
    int counter = 0;
    while(1) {
        printf("System is running... [%d seconds]\n", counter++);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
```

**ผลลัพธ์หลังแก้ไข:**
```
[บันทึก output ที่ได้]
```

## Exercise 2: ทดสอบการแก้ไข delay time

ทดลองเปลี่ยน delay จาก 1000ms เป็น:
- 500ms (0.5 วินาที)
- 2000ms (2 วินาที)
- 5000ms (5 วินาที)

**สังเกตและบันทึก:**
```
[บันทึกความแตกต่างที่สังเกตได้]
```

## ปัญหาที่พบและการแก้ไข

| ปัญหา | สาเหตุ | วิธีแก้ไข |
|-------|--------|----------|
|       |        |          |

## คำถามทบทวน

### 1. ไฟล์ใดบ้างที่จำเป็นสำหรับโปรเจกต์ ESP-IDF ขั้นต่ำ?

**คำตอบ:**
```
- CMakeLists.txt (root)
- main/CMakeLists.txt
- main/[source_file].c
```

### 2. ความแตกต่างระหว่าง `.bin` และ `.elf` คืออะไร?

**คำตอบ:**
```
[เขียนคำตอบ]
```

### 3. คำสั่ง `idf.py set-target` ทำอะไร?

**คำตอบ:**
```
[เขียนคำตอบ]
```

### 4. การใช้ `vTaskDelay()` แทน `delay()` มีความสำคัญอย่างไร?

**คำตอบ:**
```
[เขียนคำตอบ]
```

### 5. `esp_get_free_heap_size()` คืออะไร และใช้ทำอะไร?

**คำตอบ:**
```
[เขียนคำตอบ]
```

## Checklist

- [ ] ตรวจสอบ ESP-IDF environment สำเร็จ
- [ ] Build โปรเจกต์สำเร็จ
- [ ] Flash และดู serial output ได้
- [ ] เข้าใจโครงสร้างโปรเจกต์
- [ ] ทำ Exercise 1 (Build Information)
- [ ] ทำ Exercise 2 (Delay Time)
- [ ] ตอบคำถามทบทวนครบ

## บันทึกเพิ่มเติม

```
[เขียนบันทึกสิ่งที่ได้เรียนรู้เพิ่มเติม]
```

## บทสรุป

ในแลปนี้ได้เรียนรู้:
- การตรวจสอบ ESP-IDF environment
- โครงสร้างโปรเจกต์ ESP-IDF
- การ build และ flash โปรแกรม
- ฟังก์ชันพื้นฐานของ ESP-IDF
- การใช้ `vTaskDelay()` แบบ FreeRTOS

**ความยากของแลป:** ⭐⭐☆☆☆  
**ความเข้าใจ:** [ ] เข้าใจดี [ ] เข้าใจบางส่วน [ ] ควรทบทวน

---
**ขั้นตอนต่อไป:** Lab 2 - Hello World และ Serial Communication
