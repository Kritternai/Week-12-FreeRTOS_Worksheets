# 🔨 คู่มือ Build และ Flash - Lab 1

## 📋 ข้อกำหนดเบื้องต้น

### ติดตั้ง ESP-IDF แล้ว
```bash
# ตรวจสอบว่าติดตั้ง ESP-IDF แล้วหรือยัง
idf.py --version

# ควรได้ผลลัพธ์คล้าย:
# ESP-IDF v5.x.x
```

ถ้ายังไม่ได้ติดตั้ง → ไปที่: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/

### เชื่อมต่อ ESP32 กับคอมพิวเตอร์
- เสียบสาย USB ระหว่าง ESP32 และคอมพิวเตอร์
- ตรวจสอบว่า driver ติดตั้งแล้ว (ไฟบอร์ดติด)

---

## 🚀 คำสั่งพื้นฐาน

### 1. เข้าไปยังโฟลเดอร์โปรเจกต์

```bash
cd /Users/kbbk/Week-12-FreeRTOS_Worksheets/67030011/00-multitasking-evolution/lab1-single-vs-multi
```

### 2. ตรวจสอบ Port

#### สำหรับ macOS/Linux:
```bash
# ดู port ที่เชื่อมต่อ
ls /dev/tty.*

# ควรเห็นอะไรประมาณ:
# /dev/tty.usbserial-xxxxx  (CP210x)
# /dev/tty.SLAB_USBtoUART    (Silicon Labs)
# /dev/tty.usbmodem14201     (CH340)
```

#### สำหรับ Windows:
```bash
# ดู COM port
mode

# ควรเห็นอะไรประมาณ:
# COM3, COM4, etc.
```

---

## 📝 วิธีการเปลี่ยนระหว่าง Single Task และ Multitask

### แก้ไขไฟล์ CMakeLists.txt

**เปิดไฟล์:**
```bash
nano main/CMakeLists.txt
# หรือใช้ VS Code:
code main/CMakeLists.txt
```

**เนื้อหาไฟล์:**
```cmake
# สำหรับการทดสอบ Single Task ให้ใช้:
# idf_component_register(SRCS "single_task.c" INCLUDE_DIRS ".")

# สำหรับการทดสอบ Multitasking ให้ใช้:
idf_component_register(SRCS "multitask.c" INCLUDE_DIRS ".")

# สลับ comment เพื่อเปลี่ยนระหว่าง single_task.c และ multitask.c
```

**เปลี่ยนเป็น Single Task:**
```cmake
idf_component_register(SRCS "single_task.c" INCLUDE_DIRS ".")
# idf_component_register(SRCS "multitask.c" INCLUDE_DIRS ".")
```

**เปลี่ยนเป็น Multitask:**
```cmake
# idf_component_register(SRCS "single_task.c" INCLUDE_DIRS ".")
idf_component_register(SRCS "multitask.c" INCLUDE_DIRS ".")
```

---

## 🔨 คำสั่ง Build และ Flash

### ทดสอบ Single Task Mode

```bash
# 1. เข้าไปยังโฟลเดอร์
cd /Users/kbbk/Week-12-FreeRTOS_Worksheets/67030011/00-multitasking-evolution/lab1-single-vs-multi

# 2. แก้ไข CMakeLists.txt ให้ใช้ single_task.c
# (แก้ไขตามด้านบน)

# 3. Clean โปรเจกต์ (ถ้าเคย build มาก่อน)
idf.py fullclean

# 4. Build โปรเจกต์
idf.py build

# 5. Flash ลงบอร์ด
idf.py -p /dev/tty.usbserial-xxxxx flash
# แทนที่ /dev/tty.usbserial-xxxxx ด้วย port ของคุณ

# 6. เปิด Serial Monitor เพื่อดูผล
idf.py -p /dev/tty.usbserial-xxxxx monitor

# หรือทำทั้งหมดพร้อมกัน:
idf.py -p /dev/tty.usbserial-xxxxx flash monitor
```

### ทดสอบ Multitask Mode

```bash
# 1. อยู่ในโฟลเดอร์เดิม
cd /Users/kbbk/Week-12-FreeRTOS_Worksheets/67030011/00-multitasking-evolution/lab1-single-vs-multi

# 2. แก้ไข CMakeLists.txt ให้ใช้ multitask.c
# (แก้ไขตามด้านบน)

# 3. Clean โปรเจกต์
idf.py fullclean

# 4. Build, Flash และ Monitor
idf.py -p /dev/tty.usbserial-xxxxx flash monitor
```

---

## ⚡ คำสั่งแบบรวด (All-in-One)

### คำสั่งเดียวสำหรับ Build + Flash + Monitor

```bash
# สำหรับ macOS/Linux
idf.py -p /dev/tty.usbserial-xxxxx flash monitor

# สำหรับ Windows
idf.py -p COM3 flash monitor
```

### ตั้งค่า Port เป็น Default (ไม่ต้องพิมพ์ -p ทุกครั้ง)

```bash
# ตั้งค่า environment variable
export ESPPORT=/dev/tty.usbserial-xxxxx  # macOS/Linux
set ESPPORT=COM3                          # Windows

# จากนั้นใช้คำสั่งง่ายๆ
idf.py flash monitor
```

---

## 🎯 Workflow สำหรับทำ Lab 1

### Step-by-Step

```bash
# ===== PART 1: Single Task Mode =====

# 1. ไปยังโฟลเดอร์โปรเจกต์
cd /Users/kbbk/Week-12-FreeRTOS_Worksheets/67030011/00-multitasking-evolution/lab1-single-vs-multi

# 2. แก้ไข main/CMakeLists.txt ให้ใช้ single_task.c
code main/CMakeLists.txt
# เปลี่ยนเป็น: idf_component_register(SRCS "single_task.c" INCLUDE_DIRS ".")

# 3. Build และ Flash
idf.py fullclean
idf.py -p /dev/tty.usbserial-xxxxx flash monitor

# 4. ทดสอบ
#    - สังเกต LED กระพริบเป็นลำดับ
#    - กดปุ่ม BOOT → สังเกตว่าตอบสนองช้า (2-3 วินาที)
#    - บันทึกเวลาตอบสนอง

# 5. ออกจาก Monitor (Ctrl + ])


# ===== PART 2: Multitask Mode =====

# 6. แก้ไข main/CMakeLists.txt ให้ใช้ multitask.c
code main/CMakeLists.txt
# เปลี่ยนเป็น: idf_component_register(SRCS "multitask.c" INCLUDE_DIRS ".")

# 7. Build และ Flash
idf.py fullclean
idf.py -p /dev/tty.usbserial-xxxxx flash monitor

# 8. ทดสอบ
#    - สังเกต LED กระพริบพร้อมกัน
#    - กดปุ่ม BOOT → สังเกตว่าตอบสนองเร็ว (< 100ms)
#    - บันทึกเวลาตอบสนอง

# 9. ออกจาก Monitor (Ctrl + ])


# ===== PART 3: บันทึกผล =====

# 10. กรอกข้อมูลใน REPORT.md
code ../REPORT.md
```

---

## 📺 Serial Monitor

### คำสั่ง Monitor

```bash
# เปิด Monitor อย่างเดียว (ถ้า flash ไปแล้ว)
idf.py -p /dev/tty.usbserial-xxxxx monitor

# ตั้งค่า Baud rate (ถ้าจำเป็น)
idf.py -p /dev/tty.usbserial-xxxxx -b 115200 monitor
```

### Keyboard Shortcuts ใน Monitor

| คีย์ | ฟังก์ชัน |
|------|----------|
| `Ctrl + ]` | ออกจาก monitor |
| `Ctrl + T` → `Ctrl + H` | แสดง help menu |
| `Ctrl + T` → `Ctrl + R` | Reset ESP32 |
| `Ctrl + T` → `Ctrl + X` | Exit monitor |

### ตัวอย่าง Output

#### Single Task Mode:
```
Single Task System Started
LED1 (GPIO2): Sensor simulation
LED2 (GPIO4): Actuator simulation
Button (GPIO0): Emergency test
Reading sensor...
Processing data...
Controlling actuator...
Reading sensor...
Processing data...
Button pressed! (Delayed response)    ← ตอบสนองช้า!
```

#### Multitask Mode:
```
Multitasking System Started
LED1 (GPIO2): Sensor task
LED2 (GPIO4): Actuator task
Button (GPIO0): Emergency task (Priority 5)
Reading sensor...
Processing data...
Controlling actuator...
EMERGENCY! Button pressed - Immediate response!  ← ตอบสนองทันที!
Reading sensor...
```

---

## 🔧 คำสั่งเพิ่มเติม

### Clean โปรเจกต์

```bash
# Clean build files (แนะนำเมื่อเปลี่ยน source file)
idf.py fullclean

# หรือ clean ธรรมดา
idf.py clean
```

### Configuration Menu

```bash
# เข้า menuconfig (ตั้งค่าต่างๆ)
idf.py menuconfig

# ตั้งค่า serial port
idf.py menuconfig
# เลือก: Serial flasher config → Default serial port
```

### ดูข้อมูลโปรเจกต์

```bash
# ดูข้อมูลการ build
idf.py size

# ดูข้อมูล memory usage
idf.py size-components

# ดูข้อมูล flash
idf.py partition-table
```

### Erase Flash

```bash
# ลบข้อมูลใน flash ทั้งหมด
idf.py -p /dev/tty.usbserial-xxxxx erase-flash
```

---

## 🐛 Troubleshooting

### ปัญหา: Cannot find port

**macOS/Linux:**
```bash
# ดู port ทั้งหมด
ls /dev/tty.*

# ถ้าไม่เจอ ตรวจสอบ:
# 1. เสียบ USB ใหม่
# 2. ติดตั้ง driver (CP210x, CH340, หรือ Silicon Labs)
# 3. ลอง USB port อื่น
```

**Windows:**
```bash
# ดู COM port
mode

# ถ้าไม่เจอ:
# 1. เปิด Device Manager
# 2. มองหา "Ports (COM & LPT)"
# 3. ติดตั้ง driver ถ้าเห็น yellow triangle
```

### ปัญหา: Permission denied (macOS/Linux)

```bash
# เพิ่ม permission
sudo chmod 666 /dev/tty.usbserial-xxxxx

# หรือเพิ่ม user เข้า dialout group (Linux)
sudo usermod -a -G dialout $USER
# ต้อง logout/login ใหม่
```

### ปัญหา: Build error

```bash
# Clean แล้ว build ใหม่
idf.py fullclean
idf.py build

# ถ้ายังไม่ได้ ตรวจสอบ:
# 1. ESP-IDF version ถูกต้อง
# 2. ไฟล์ CMakeLists.txt ถูกต้อง
# 3. ไฟล์ .c อยู่ในโฟลเดอร์ main/
```

### ปัญหา: Flash failed

```bash
# ลองใหม่ด้วย baud rate ต่ำกว่า
idf.py -p /dev/tty.usbserial-xxxxx -b 115200 flash

# หรือกด BOOT button ขณะ flash
# 1. กด BOOT button ค้าง
# 2. รันคำสั่ง flash
# 3. เมื่อเห็น "Connecting..." ปล่อย BOOT button
```

### ปัญหา: Monitor แสดงผลผิดเพี้ยน

```bash
# Reset ESP32
# กด EN button บนบอร์ด

# หรือ reset ผ่านคำสั่ง
idf.py -p /dev/tty.usbserial-xxxxx monitor
# จากนั้นกด Ctrl+T แล้วกด Ctrl+R
```

---

## 📋 Checklist การทำ Lab

### ก่อน Build

- [ ] ติดตั้ง ESP-IDF แล้ว
- [ ] เชื่อมต่อ ESP32 กับคอมพิวเตอร์
- [ ] รู้ port ของ ESP32
- [ ] ต่อ LED และ resistor ถูกต้อง
- [ ] แก้ไข `main/CMakeLists.txt` เลือก source file

### ระหว่าง Build

- [ ] Clean โปรเจกต์ (`idf.py fullclean`)
- [ ] Build สำเร็จ (`idf.py build`)
- [ ] Flash สำเร็จ (`idf.py flash`)
- [ ] เปิด Monitor (`idf.py monitor`)

### การทดสอบ

- [ ] เห็น log ใน Serial Monitor
- [ ] LED กระพริบตามที่คาดหวัง
- [ ] กดปุ่ม BOOT ทดสอบ emergency response
- [ ] บันทึกเวลาตอบสนอง
- [ ] ทำทั้ง Single Task และ Multitask Mode

### หลังทำเสร็จ

- [ ] เปรียบเทียบผลระหว่าง 2 โหมด
- [ ] กรอกข้อมูลใน REPORT.md
- [ ] ถ่ายรูปวงจร (ถ้าทำจริง)
- [ ] Screenshot Serial Monitor

---

## 💡 Tips

1. **ใช้ `fullclean`** ทุกครั้งที่เปลี่ยน source file
2. **ตั้งค่า ESPPORT** เพื่อไม่ต้องพิมพ์ -p ทุกครั้ง
3. **เปิด 2 terminal** - terminal 1 สำหรับ build, terminal 2 สำหรับ monitor
4. **บันทึก log** - Screenshot หรือ copy text จาก monitor
5. **ทดสอบทีละส่วน** - Single Task ก่อน แล้วค่อย Multitask

---

## 📝 สรุปคำสั่งที่ใช้บ่อย

```bash
# เข้าโฟลเดอร์
cd /Users/kbbk/Week-12-FreeRTOS_Worksheets/67030011/00-multitasking-evolution/lab1-single-vs-multi

# ตั้งค่า port (ครั้งเดียว)
export ESPPORT=/dev/tty.usbserial-xxxxx

# Clean, Build, Flash, Monitor (แบบเดียวจบ)
idf.py fullclean && idf.py flash monitor

# หรือแยกเป็นขั้นตอน
idf.py fullclean
idf.py build
idf.py flash
idf.py monitor
```

---

**พร้อมเริ่มต้น Build และ Flash แล้ว! 🚀**

หากมีปัญหาระหว่างทำ สามารถดูในส่วน Troubleshooting หรือถามได้เลยครับ!

