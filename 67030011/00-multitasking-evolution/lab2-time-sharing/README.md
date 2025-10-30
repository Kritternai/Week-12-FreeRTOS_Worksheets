# Lab 2: Time-Sharing Implementation

## วัตถุประสงค์
ทำความเข้าใจ Time-Sharing และสังเกตปัญหาที่เกิดขึ้นจากการแบ่งเวลาแบบ manual

## ไฟล์ในโปรเจกต์
- `main/time_sharing.c` - โปรแกรม Time-Sharing แบบ manual

## การใช้งาน

### Build และ Flash
```bash
cd /Users/kbbk/Week-12-FreeRTOS_Worksheets/67030011/00-multitasking-evolution/lab2-time-sharing
idf.py build
idf.py flash monitor
```

## สิ่งที่โปรแกรมจะทำ

1. **แสดงปัญหาของ Time-Sharing**
   - ไม่มีการรองรับ priority
   - Time slice คงที่มีปัญหา
   - Context switching overhead
   - ไม่มีการสื่อสารระหว่าง task

2. **รัน Time-Sharing ปกติ**
   - ใช้ time slice 50ms
   - แสดงสถิติทุก 20 context switches
   - วัด CPU utilization และ overhead

3. **ทดสอบ Time Slice ต่างๆ**
   - 10ms, 25ms, 50ms, 100ms, 200ms
   - เปรียบเทียบประสิทธิภาพแต่ละแบบ

## พิน GPIO ที่ใช้
- LED1: GPIO2 (Sensor task - งานเบา)
- LED2: GPIO4 (Processing task - งานหนัก)
- LED3: GPIO5 (Actuator task - งานปานกลาง)
- LED4: GPIO18 (Display task - งานเบา)

## การทดสอบและวัดผล

### 1. สังเกตการทำงาน
- ดูแพทเทิร์นการกระพริบของ LED แต่ละดวง
- สังเกตว่างานใดใช้เวลานาน (LED2 ควรติดนานกว่า)

### 2. วิเคราะห์สถิติ
- CPU Utilization: ควรอยู่ที่ 70-90%
- Overhead: ควรอยู่ที่ 10-30%
- Context switches: จำนวนครั้งที่เปลี่ยน task

### 3. เปรียบเทียบ Time Slice
- Time slice สั้น (10ms): Overhead สูง แต่ตอบสนองเร็ว
- Time slice ยาว (200ms): Overhead ต่ำ แต่ตอบสนองช้า
- Time slice ที่เหมาะสม: 50-100ms

## คำถามสำหรับวิเคราะห์

1. **Time slice ขนาดไหนให้ประสิทธิภาพดีที่สุด? เพราะอะไร?**
   - คำตอบที่คาดหวัง: 50-100ms เพราะสมดุลระหว่าง overhead กับการตอบสนอง

2. **ปัญหาอะไรที่เกิดขึ้นเมื่อ time slice สั้นเกินไป?**
   - Context switching overhead สูง
   - CPU ใช้เวลาไปกับการสลับ task มากเกินไป

3. **ปัญหาอะไรที่เกิดขึ้นเมื่อ time slice ยาวเกินไป?**
   - การตอบสนองช้า
   - Task ต้องรอนานก่อนได้รัน

4. **Context switching overhead คิดเป็นกี่เปอร์เซ็นต์ของเวลาทั้งหมด?**
   - ควรอยู่ที่ 10-30% ขึ้นอยู่กับ time slice

5. **งานไหนที่ได้รับผลกระทบมากที่สุดจากการ time-sharing?**
   - งานที่ต้องการการตอบสนองเร็ว (เช่น emergency handling)
   - งานที่ใช้เวลาน้อย แต่ต้องรอ time slice เต็ม

## ผลการทดลองที่คาดหวัง

| Time Slice | Context Switches/sec | CPU Utilization | Overhead | Response Time |
|------------|---------------------|-----------------|----------|---------------|
| 10ms       | 100                 | 70-75%          | 25-30%   | ดีมาก         |
| 25ms       | 40                  | 80-85%          | 15-20%   | ดี            |
| 50ms       | 20                  | 85-90%          | 10-15%   | ปานกลาง       |
| 100ms      | 10                  | 90-95%          | 5-10%    | พอใช้         |
| 200ms      | 5                   | 92-97%          | 3-8%     | แย่           |

## สิ่งที่ได้เรียนรู้

1. **Context Switching Overhead**
   - เวลาที่สูญเสียในการเปลี่ยน task
   - ยิ่ง time slice สั้น overhead ยิ่งสูง

2. **Time Slice Trade-offs**
   - ความสมดุลระหว่างการตอบสนองและประสิทธิภาพ
   - ไม่มี time slice ที่สมบูรณ์แบบสำหรับทุกสถานการณ์

3. **Fixed Schedule Limitations**
   - ไม่สามารถจัดการความสำคัญของงานได้
   - งานทุกอย่างได้เวลาเท่ากัน ไม่ว่าจะสำคัญหรือไม่

4. **Need for RTOS**
   - จำเป็นต้องมีระบบที่จัดการ priority
   - ต้องมีการจัดการ context switching ที่มีประสิทธิภาพ
   - ต้องมีกลไกการสื่อสารระหว่าง task

## เวลาที่ใช้
45 นาที

## การประยุกต์ใช้
เทคนิค Time-sharing แบบ manual นี้ยังใช้อยู่ใน:
- ระบบที่มีทรัพยากรจำกัดมาก
- โปรเซสเซอร์ที่ไม่รองรับ RTOS
- งานง่ายๆ ที่ไม่ต้องการ real-time

แต่สำหรับงานที่ซับซ้อนและต้องการ real-time ควรใช้ RTOS แทน

