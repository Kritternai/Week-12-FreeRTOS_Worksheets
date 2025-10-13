# วิธีการ Build และ Flash โปรเจกต์

## ขั้นตอนการ Build

### 1. เปิด Terminal และเข้าสู่โฟลเดอร์โปรเจกต์

```bash
cd /Users/kbbk/Week-12-FreeRTOS_Worksheets/67030011/01-freertos-overview/lab1-setup-first-project
```

### 2. Set up ESP-IDF Environment

```bash
# สำหรับ macOS/Linux
. $HOME/esp/esp-idf/export.sh

# หรือถ้าติดตั้งที่อื่น
. /path/to/esp-idf/export.sh
```

### 3. Set Target (ครั้งแรกเท่านั้น)

```bash
idf.py set-target esp32
```

คำสั่งนี้จะสร้างไฟล์ `sdkconfig` และกำหนด target เป็น ESP32

### 4. Build โปรเจกต์

```bash
idf.py build
```

**ระยะเวลาที่ใช้:**
- Build ครั้งแรก: 2-5 นาที
- Build ครั้งต่อไป: 10-30 วินาที (compile เฉพาะไฟล์ที่เปลี่ยน)

**Output ที่ได้:**
```
build/
├── bootloader/
│   └── bootloader.bin
├── partition_table/
│   └── partition-table.bin
├── hello_esp32.bin         # ไฟล์สำหรับ flash
├── hello_esp32.elf         # ไฟล์พร้อม debug symbols
└── hello_esp32.map         # Memory map
```

## ขั้นตอนการ Flash

### 1. เชื่อมต่อ ESP32 กับคอมพิวเตอร์

- เชื่อมต่อ ESP32 ด้วย USB cable
- ตรวจสอบว่าเชื่อมต่อสำเร็จ

### 2. ตรวจสอบ Port

```bash
# macOS
ls /dev/cu.*

# Linux
ls /dev/ttyUSB*

# Windows
# ตรวจสอบใน Device Manager
```

**Port ที่พบบ่อย:**
- macOS: `/dev/cu.usbserial-XXXX` หรือ `/dev/cu.SLAB_USBtoUART`
- Linux: `/dev/ttyUSB0`
- Windows: `COM3`, `COM4`, etc.

### 3. Flash โปรแกรม

```bash
# Flash โดยอัตโนมัติหา port
idf.py flash

# หรือระบุ port เอง
idf.py -p /dev/cu.usbserial-XXXX flash
```

**ระยะเวลาที่ใช้:** 10-20 วินาที

### 4. Monitor Serial Output

```bash
# เปิด Serial Monitor
idf.py monitor

# หรือ flash และ monitor พร้อมกัน
idf.py flash monitor
```

**การออกจาก Monitor:**
- กด `Ctrl + ]`

## คำสั่งรวม (แนะนำ)

```bash
# Build, Flash และ Monitor ในคำสั่งเดียว
idf.py build flash monitor
```

## คำสั่งที่มีประโยชน์

### Clean Build

```bash
# Clean build files
idf.py clean

# Full clean (รวม config)
idf.py fullclean
```

### ตรวจสอบขนาดไฟล์

```bash
idf.py size

# แสดงรายละเอียดแต่ละ component
idf.py size-components
```

### Configuration

```bash
# เปิด menuconfig
idf.py menuconfig
```

## ตัวอย่าง Output

### Build Success:

```
Project build complete. To flash, run:
 idf.py flash
or
 idf.py -p PORT flash
```

### Flash Success:

```
Leaving...
Hard resetting via RTS pin...
Done
```

### Serial Monitor Output:

```
=== My First ESP32 Project ===
ESP-IDF Version: v5.x.x
Free heap: 294420 bytes
Running for 0 seconds
Running for 1 seconds
Running for 2 seconds
...
```

## การแก้ไขปัญหา

### ปัญหา: Permission denied (macOS/Linux)

```bash
sudo chmod 666 /dev/cu.usbserial-*
# หรือ
sudo chmod 666 /dev/ttyUSB0
```

### ปัญหา: Cannot find ESP-IDF

```bash
# ตรวจสอบว่า export แล้ว
echo $IDF_PATH

# ถ้ายังไม่ได้ export
. $HOME/esp/esp-idf/export.sh
```

### ปัญหา: Build failed

```bash
# Clean และ build ใหม่
idf.py fullclean
idf.py set-target esp32
idf.py build
```

### ปัญหา: Flash failed

1. ตรวจสอบ USB cable (ใช้ cable ที่รองรับ data)
2. กด BOOT button ค้างไว้ขณะ flash
3. ลอง reset board ก่อน flash
4. ตรวจสอบ driver (CP210x หรือ CH340)

## Tips

1. **ใช้ `flash monitor` แทน `flash` และ `monitor` แยกกัน**
   ```bash
   idf.py flash monitor
   ```

2. **เปิด monitor หลัง flash เสร็จ**
   - Monitor จะ reset board อัตโนมัติ

3. **ใช้ verbose mode เพื่อ debug**
   ```bash
   idf.py -v build
   idf.py -v flash
   ```

4. **Monitor ด้วย baud rate ที่ถูกต้อง**
   ```bash
   idf.py monitor -b 115200
   ```

## สรุป

**Workflow ปกติ:**
```bash
# ครั้งแรก
idf.py set-target esp32
idf.py build

# ทุกครั้งหลังแก้ไขโค้ด
idf.py build flash monitor
```

**Shortcut:**
```bash
# One-liner สำหรับทุกครั้ง
idf.py build flash monitor
```
