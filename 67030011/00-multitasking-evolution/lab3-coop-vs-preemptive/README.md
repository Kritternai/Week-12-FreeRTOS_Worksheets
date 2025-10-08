# Lab 3: Cooperative vs Preemptive Comparison

## วัตถุประสงค์
เปรียบเทียบ Cooperative Multitasking กับ Preemptive Multitasking และเข้าใจข้อดี-ข้อเสีย

## ไฟล์ในโปรเจกต์
- `main/multitask_comparison.c` - โปรแกรมเปรียบเทียบทั้งสองแบบ

## การใช้งาน

### เปลี่ยนโหมดการทดสอบ

แก้ไขไฟล์ `main/multitask_comparison.c` บรรทัดที่ 16-17:

#### ทดสอบ Cooperative Multitasking:
```c
#define TEST_MODE TEST_MODE_COOPERATIVE
```

#### ทดสอบ Preemptive Multitasking:
```c
#define TEST_MODE TEST_MODE_PREEMPTIVE
```

### Build และ Flash
```bash
cd /Users/kbbk/Week-12-FreeRTOS_Worksheets/67030011/00-multitasking-evolution/lab3-coop-vs-preemptive
idf.py build
idf.py flash monitor
```

## พิน GPIO ที่ใช้
- LED1: GPIO2 (Task 1 indicator)
- LED2: GPIO4 (Task 2 indicator)
- LED3: GPIO5 (Emergency response indicator)
- Button: GPIO0 (Emergency trigger)

## การทดสอบ

### ทดสอบ Cooperative System

1. **ตั้งค่าโหมด:**
   - แก้ไข `TEST_MODE` เป็น `TEST_MODE_COOPERATIVE`
   - Build และ flash

2. **สังเกตการทำงาน:**
   - Task1 และ Task2 จะทำงานสลับกัน
   - แต่ละ task จะ yield (สละ CPU) โดยสมัครใจ
   - สังเกต log ว่า task จะ yield เมื่อเจอ emergency

3. **ทดสอบ Emergency Response:**
   - กดปุ่ม GPIO0 หลายครั้ง
   - บันทึกเวลาตอบสนอง (Response time)
   - สังเกตว่า response time แตกต่างกันไปแต่ละครั้ง
   - Max response time อาจสูงถึง 500-1000ms

4. **วิเคราะห์:**
   - ทำไม response time ไม่คงที่?
   - ทำไมบางครั้งตอบสนองช้ามาก?

### ทดสอบ Preemptive System

1. **ตั้งค่าโหมด:**
   - แก้ไข `TEST_MODE` เป็น `TEST_MODE_PREEMPTIVE`
   - Build และ flash

2. **สังเกตการทำงาน:**
   - Task1 และ Task2 ไม่มี voluntary yield
   - RTOS จะบังคับสลับ task โดยอัตโนมัติ
   - Task ที่มี priority สูงจะแย่ง CPU ได้ทันที

3. **ทดสอบ Emergency Response:**
   - กดปุ่ม GPIO0 หลายครั้ง
   - บันทึกเวลาตอบสนอง (Response time)
   - สังเกตว่า response time คงที่และรวดเร็ว
   - Max response time ควรต่ำกว่า 50ms

4. **วิเคราะห์:**
   - ทำไม response time สม่ำเสมอ?
   - Priority มีผลอย่างไรกับการทำงาน?

## คำถามสำหรับวิเคราะห์

1. **ระบบไหนมีเวลาตอบสนองดีกว่า? เพราะอะไร?**
   - คำตอบ: Preemptive ดีกว่า เพราะ task ที่มี priority สูงจะได้รันทันทีโดยไม่ต้องรอ task อื่น yield

2. **ข้อดีของ Cooperative Multitasking คืออะไร?**
   - ใช้ทรัพยากรน้อย (context switch overhead ต่ำ)
   - เข้าใจและ debug ง่ายกว่า
   - ไม่มี race condition ถ้าเขียนโค้ดดี

3. **ข้อเสียของ Cooperative Multitasking คืออะไร?**
   - Response time ไม่แน่นอน
   - Task หนึ่งอาจครอบครอง CPU ถ้าไม่ yield
   - ไม่เหมาะสำหรับ real-time systems

4. **ในสถานการณ์ใดที่ Cooperative จะดีกว่า Preemptive?**
   - งานที่ไม่ต้องการ real-time strict
   - ระบบที่มีทรัพยากรจำกัดมาก
   - งานที่ทราบลำดับการทำงานแน่ชัด

5. **เหตุใด Preemptive จึงเหมาะสำหรับ Real-time systems?**
   - รับประกันเวลาตอบสนอง (deterministic)
   - Priority-based scheduling
   - Task สำคัญไม่ถูกบล็อกโดย task ที่สำคัญน้อยกว่า

## ผลการทดลองที่คาดหวัง

| ระบบ | เวลาตอบสนองเฉลี่ย | เวลาตอบสนองสูงสุด | ความซับซ้อน | Resource Usage |
|------|-------------------|------------------|-------------|----------------|
| Cooperative | 50-200ms | 500-1000ms | ต่ำ | น้อย |
| Preemptive | 5-20ms | 50ms | สูง | มาก |

## ตารางเปรียบเทียบ

| ลักษณะ | Cooperative | Preemptive |
|--------|-------------|------------|
| **ความซับซ้อน** | ต่ำ | สูง |
| **Response Time** | ไม่แน่นอน | แน่นอน |
| **Resource Usage** | น้อย | มาก |
| **Determinism** | ไม่มี | มี |
| **Development** | ง่าย | ยาก |
| **Debugging** | ง่าย | ยาก |
| **Real-time Suitability** | ไม่เหมาะ | เหมาะมาก |
| **Priority Support** | ไม่มี | มี |
| **Context Switch Control** | Manual (voluntary) | Automatic (forced) |
| **CPU Utilization** | สูง (overhead ต่ำ) | กลาง (overhead สูงกว่า) |

## สถานการณ์จำลอง

### Cooperative System
```
Task1 กำลังทำงาน...
Emergency เกิดขึ้น!
Task1: "เดี๋ยวนะ รอให้ฉันทำงานเสร็จก่อน"
Task1 ทำงานต่อ...
Task1: "เสร็จแล้ว ยกสิทธิ์ให้"
Emergency: "ตอบสนองแล้ว (ช้ามาก!)"
```

### Preemptive System
```
Task1 กำลังทำงาน...
Emergency เกิดขึ้น!
RTOS: "หยุด Task1 ทันที! Emergency มี priority สูงกว่า"
Emergency: "ตอบสนองแล้ว (เร็วมาก!)"
Task1: "กลับมาทำงานต่อ"
```

## สิ่งที่ได้เรียนรู้

1. **Cooperative Multitasking**
   - พึ่งพาความร่วมมือของ tasks
   - เหมาะสำหรับระบบง่ายๆ
   - ไม่เหมาะสำหรับงาน real-time

2. **Preemptive Multitasking**
   - RTOS จัดการทุกอย่าง
   - รับประกันการตอบสนอง
   - เหมาะสำหรับระบบที่ซับซ้อน

3. **การเลือกใช้**
   - ขึ้นอยู่กับข้อกำหนดของระบบ
   - ความสมดุลระหว่าง performance กับ complexity
   - Real-time requirements เป็นปัจจัยสำคัญ

## การประยุกต์ใช้จริง

### ใช้ Cooperative:
- Simple IoT devices
- Battery-powered sensors
- Single-purpose embedded systems
- งานที่มี workload คาดการณ์ได้

### ใช้ Preemptive:
- Industrial control systems
- Automotive systems
- Medical devices
- Robotics
- Real-time data processing

## เวลาที่ใช้
30 นาที

## หมายเหตุ
- เปลี่ยนโหมดได้ง่ายๆ โดยแก้ไขแค่ #define TEST_MODE
- โปรแกรมจะ compile เฉพาะโค้ดส่วนที่เลือกเท่านั้น
- สังเกต log messages เพื่อเข้าใจการทำงาน
- ใช้ logic analyzer หรือ oscilloscope จะเห็นความแตกต่างชัดเจนยิ่งขึ้น

