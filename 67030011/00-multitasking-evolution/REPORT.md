# รายงานการทดลอง: วิวัฒนาการของ Multitasking ในไมโครคอนโทรลเลอร์

## ข้อมูลทั่วไป
- **รหัสนักศึกษา:** 67030011
- **วันที่ทำการทดลอง:** 1 ตุลาคม 2568
- **หัวข้อ:** 00-multitasking-evolution
- **เวลาที่ใช้รวม:** 2 ชั่วโมง 30 นาที

---

## Lab 1: Single Task vs Multitasking Demo

### วัตถุประสงค์
เปรียบเทียบระบบ Single Task กับ Multitasking เพื่อเข้าใจความแตกต่างในการตอบสนอง

### อุปกรณ์ที่ใช้
- ESP32 Development Board
- LED 2 ดวง (GPIO2, GPIO4)
- Push Button (GPIO0 - ใช้ปุ่ม BOOT บนบอร์ด)
- Resistor 220Ω × 2
- สาย USB
- คอมพิวเตอร์พร้อม ESP-IDF

### วิธีการทดลอง

#### Part 1: Single Task System
1. เปิดโปรเจกต์ lab1-single-vs-multi
2. แก้ไขไฟล์ `main/CMakeLists.txt` ให้ compile `single_task.c`
3. Build และ Flash โปรแกรมด้วยคำสั่ง `idf.py flash monitor`
4. สังเกตการทำงานของ LED ที่กระพริบเป็นลำดับ
5. ทดสอบกดปุ่ม BOOT และบันทึกเวลาตอบสนอง 5 ครั้ง

#### Part 2: Multitasking System
1. แก้ไขไฟล์ `main/CMakeLists.txt` ให้ compile `multitask.c`
2. Build และ Flash โปรแกรมด้วยคำสั่ง `idf.py fullclean && idf.py flash monitor`
3. สังเกตการทำงานของ LED ที่กระพริบพร้อมกัน
4. ทดสอบกดปุ่ม BOOT และบันทึกเวลาตอบสนอง 5 ครั้ง

### ผลการทดลอง

#### Single Task System
| ครั้งที่ | เวลาตอบสนอง (วินาที) | หมายเหตุ |
|---------|---------------------|----------|
| 1 | 2.1 | ช้ามาก ต้องรอจนครบรอบ |
| 2 | 2.8 | กดขณะ processing |
| 3 | 1.9 | กดช่วงเริ่มรอบใหม่ |
| 4 | 2.5 | ช้าไม่สม่ำเสมอ |
| 5 | 2.3 | ยังคงช้า |
| **เฉลี่ย** | **2.32** | **ช้าและไม่คงที่** |

**สิ่งที่สังเกตได้:**
- LED1 กระพริบ 500ms แล้วหยุด
- มีการ delay จาก processing (loop 1,000,000 รอบ) 
- LED2 กระพริบ 300ms หลังจาก LED1 เสร็จ
- ทำงานเป็นลำดับไม่พร้อมกัน
- การตอบสนองปุ่มล่าช้ามาก ต้องรอให้งานอื่นเสร็จก่อน
- เวลาตอบสนองไม่คงที่ ขึ้นอยู่กับว่ากดช่วงงานไหน

#### Multitasking System
| ครั้งที่ | เวลาตอบสนอง (มิลลิวินาที) | หมายเหตุ |
|---------|--------------------------|----------|
| 1 | 15 | ตอบสนองทันที |
| 2 | 12 | เร็วมาก |
| 3 | 18 | สม่ำเสมอ |
| 4 | 14 | Priority 5 ทำงานทันที |
| 5 | 16 | ยอดเยี่ยม |
| **เฉลี่ย** | **15** | **เร็วและคงที่** |

**สิ่งที่สังเกตได้:**
- LED1 และ LED2 กระพริบพร้อมกัน แต่ละอันมีจังหวะของตัวเอง
- LED1: กระพริบ 100ms ทุกๆ 1 วินาที
- LED2: กระพริบ 200ms แบบสม่ำเสมอ
- Processing task ทำงานเบื้องหลังโดยไม่กระทบงานอื่น
- Emergency task (Priority 5) ตอบสนองทันทีภายใน 10-20ms
- เวลาตอบสนองคงที่และรวดเร็ว

### การวิเคราะห์ผล

#### คำถามและคำตอบ

**1. ความแตกต่างในการตอบสนองปุ่มระหว่างทั้งสองระบบคืออะไร?**

คำตอบ: Single Task System มีเวลาตอบสนองเฉลี่ย 2.32 วินาที และไม่สม่ำเสมอ ในขณะที่ Multitasking System ตอบสนองเฉลี่ย 15 มิลลิวินาที ซึ่งเร็วกว่าประมาณ 150 เท่า ความแตกต่างนี้เกิดจาก Single Task ต้องรอให้งานอื่นทำเสร็จก่อน (sensor reading, processing, actuator control) จึงจะมาตรวจสอบปุ่ม แต่ Multitasking สามารถให้ Emergency task (Priority 5) ทำงานทันทีโดย preempt task อื่นๆ ได้

**2. ใน Single Task System งานไหนที่ทำให้การตอบสนองล่าช้า?**

คำตอบ: งานที่ทำให้การตอบสนองล่าช้าที่สุดคือ Processing task ที่มี loop 1,000,000 รอบ (คำนวณ i*i) ซึ่งใช้เวลาประมาณ 1-1.5 วินาที ตามด้วย Sensor reading (delay 500ms × 2) และ Actuator control (delay 300ms × 2) รวมเวลาทั้งหมดประมาณ 2-3 วินาทีต่อรอบ ทำให้การตรวจสอบปุ่มที่อยู่ท้ายสุดของลูปตอบสนองช้ามาก

**3. ข้อดีของ Multitasking System ที่สังเกตได้คืออะไร?**

คำตอบ: ข้อดีที่สังเกตได้ชัดเจนคือ (1) การตอบสนองเหตุการณ์ฉุกเฉินรวดเร็วมาก (< 20ms) เหมาะสำหรับ real-time systems (2) งานหลายอย่างทำงานพร้อมกันได้ โดย LED ทั้งสองกระพริบไม่รบกวนกัน (3) Priority scheduling ทำให้งานสำคัญได้รับการจัดการก่อน (4) ไม่มีงานใดครอบครอง CPU ตลอดเวลา ทำให้ระบบมี responsiveness สูง (5) ง่ายต่อการขยายเพิ่ม task ใหม่โดยไม่กระทบโครงสร้างเดิม

**4. มีข้อเสียของ Multitasking System ที่สังเกตได้หรือไม่?**

คำตอบ: ข้อเสียที่สังเกตได้คือ (1) ความซับซ้อนของโค้ดเพิ่มขึ้น ต้องคำนึงถึง task priorities และ synchronization (2) ใช้ memory มากขึ้น เนื่องจากแต่ละ task ต้องมี stack ของตัวเอง (lab นี้ใช้ 2048 bytes/task) (3) มี context switching overhead แม้จะไม่มากแต่ก็มีการสูญเสีย CPU cycles ในการสลับ task (4) อาจเกิด race condition หรือ deadlock ได้ถ้าไม่ระวังในการแชร์ resources (5) การ debug ยากขึ้นเพราะต้องติดตาม multiple tasks พร้อมกัน

### สรุปผล Lab 1

Lab 1 แสดงให้เห็นชัดเจนถึงข้อจำกัดของ Single Task System ที่ไม่เหมาะสำหรับงานที่ต้องการ responsive เนื่องจากต้องรอให้ทุกงานในลูปทำเสร็จก่อนจึงจะไปยังงานถัดไป ในขณะที่ Multitasking System ด้วย FreeRTOS สามารถแก้ปัญหานี้ได้โดยใช้ priority-based preemptive scheduling ทำให้งานที่มีความสำคัญสูง (Emergency task) สามารถตอบสนองได้ทันทีภายในเวลาไม่เกิน 20ms ซึ่งเร็วกว่า 150 เท่า

การทดลองนี้ยังแสดงให้เห็นว่า FreeRTOS จัดการ multitasking ได้อย่างมีประสิทธิภาพ โดยใช้ vTaskDelay() เพื่อให้ task สละ CPU และ priority scheduling เพื่อให้งานสำคัญทำก่อน ทำให้เหมาะสำหรับ embedded systems ที่ต้องการทั้ง real-time response และการทำงานหลายอย่างพร้อมกัน

---

## Lab 2: Time-Sharing Implementation

### วัตถุประสงค์
ทำความเข้าใจ Time-Sharing และสังเกตปัญหาที่เกิดขึ้นจากการแบ่งเวลาแบบ manual

### อุปกรณ์ที่ใช้
- ESP32 Development Board
- LED 4 ดวง (GPIO2, GPIO4, GPIO5, GPIO18)
- Resistor 220Ω × 4
- คอมพิวเตอร์

### วิธีการทดลอง
1. เปิดโปรเจกต์ lab2-time-sharing
2. Build และ Flash โปรแกรมด้วย `idf.py flash monitor`
3. สังเกต LED patterns และ log messages
4. บันทึกสถิติที่แสดงบน Serial Monitor ทุก 20 context switches
5. สังเกต Variable Time Slice Experiment ที่ทดสอบ time slices: 10ms, 25ms, 50ms, 100ms, 200ms

### ผลการทดลอง

#### ส่วนที่ 1: Time-Sharing ปกติ (Time Slice = 50ms)

| Round | Context Switches | CPU Utilization | Overhead | Avg Time/Task |
|-------|------------------|-----------------|----------|---------------|
| 1 | 20 | 87.3% | 12.7% | 2,180 us |
| 2 | 40 | 88.1% | 11.9% | 2,202 us |
| 3 | 60 | 87.8% | 12.2% | 2,195 us |
| 4 | 80 | 88.5% | 11.5% | 2,213 us |
| 5 | 100 | 88.0% | 12.0% | 2,200 us |

**เฉลี่ย: CPU Utilization = 87.9%, Overhead = 12.1%**

#### ส่วนที่ 2: Variable Time Slice Experiment

| Time Slice | Context Switches | Efficiency | สังเกต |
|------------|------------------|------------|--------|
| 10ms | 50 | 72.5% | Overhead สูง LED กระพริบถี่มาก |
| 25ms | 50 | 82.8% | ดีขึ้น แต่ยังมี overhead พอสมควร |
| 50ms | 50 | 88.2% | สมดุลดี response time พอใช้ |
| 100ms | 50 | 92.7% | Efficiency สูง แต่ response ช้า |
| 200ms | 50 | 95.1% | Overhead ต่ำสุด แต่ response แย่มาก |

**Time Slice ที่เหมาะสมที่สุด:** 50ms

**เหตุผล:** Time slice 50ms ให้ความสมดุลที่ดีระหว่าง CPU efficiency (88%) และ response time ที่ยอมรับได้ Time slice 100-200ms แม้จะมี efficiency สูงแต่ task ต้องรอนานเกินไปก่อนได้รัน ในขณะที่ 10-25ms มี context switching overhead สูงเกินไป (สูญเสีย CPU 15-27%) Time slice 50ms จึงเป็นจุดหวานที่เหมาะสมสำหรับระบบ embedded ส่วนใหญ่

### การวิเคราะห์ผล

#### คำถามและคำตอบ

**1. Time slice ขนาดไหนให้ประสิทธิภาพดีที่สุด? เพราะอะไร?**

คำตอบ: Time slice 50-100ms ให้ประสิทธิภาพดีที่สุด เพราะมีความสมดุลระหว่าง CPU efficiency และ response time จากการทดลอง time slice 50ms ให้ efficiency 88.2% ซึ่งดีพอ และ response time ยังอยู่ในระดับที่ยอมรับได้ (< 200ms) ในขณะที่ 100ms แม้จะมี efficiency สูงถึง 92.7% แต่ response time อาจช้าเกินไปสำหรับบางงาน ส่วน time slice ที่เล็กกว่า 25ms มี overhead จาก context switching สูงเกินไป (> 15%) ไม่คุ้มค่า

**2. ปัญหาอะไรที่เกิดขึ้นเมื่อ time slice สั้นเกินไป?**

คำตอบ: เมื่อ time slice สั้นเกินไป (10ms) จะเกิดปัญหา (1) Context switching overhead สูงมาก - CPU ใช้เวลาไปกับการสลับ task ถึง 27% แทนที่จะทำงานจริง (2) Cache miss เพิ่มขึ้น - การสลับ task บ่อยทำให้ data/instruction cache ถูกแทนที่บ่อย (3) System responsiveness ลดลง - แม้จะสลับบ่อยแต่ overhead กินเวลามากจนประสิทธิภาพโดยรวมแย่ลง (4) Power consumption เพิ่ม - การสลับ task ใช้พลังงานมากกว่าการทำงานต่อเนื่อง

**3. ปัญหาอะไรที่เกิดขึ้นเมื่อ time slice ยาวเกินไป?**

คำตอบ: เมื่อ time slice ยาวเกินไป (200ms) จะเกิดปัญหา (1) Response time ช้ามาก - task ต้องรอนานถึง 200ms × (จำนวน task - 1) กว่าจะได้รันอีกครั้ง ในกรณีที่มี 4 tasks คือรอถึง 600ms (2) Unfairness - task ที่มี workload น้อยต้องถือ CPU นานโดยไม่จำเป็น ทำให้ task อื่นหิว (3) ไม่เหมาะสำหรับ interactive tasks - งานที่ต้องการ quick response จะรู้สึกช้า lag (4) Missed deadlines - สำหรับ real-time tasks อาจพลาด deadline

**4. Context switching overhead คิดเป็นกี่เปอร์เซ็นต์ของเวลาทั้งหมด?**

คำตอบ: จากการทดลอง context switching overhead อยู่ที่ประมาณ 10-15% สำหรับ time slice ที่เหมาะสม (50-100ms) และสูงถึง 20-30% สำหรับ time slice สั้น (10ms) overhead นี้ประกอบด้วยเวลาในการ save/restore registers, update task states, select next task และ memory operations ค่า overhead จริงขึ้นอยู่กับ (1) จำนวน registers ที่ต้อง save (2) complexity ของ scheduler (3) memory access speed (4) cache behavior

**5. งานไหนที่ได้รับผลกระทบมากที่สุดจากการ time-sharing?**

คำตอบ: งานที่ได้รับผลกระทบมากที่สุดคือ (1) Processing task (heavy computation) - มี workload มากแต่ถูกจำกัดด้วย time slice ทำให้ต้องถูกขัดจังหวะบ่อย ประสิทธิภาพลดลงจากการสูญเสีย cache และ pipeline stalls (2) Display task (quick work) - แม้ทำงานเสร็จเร็ว แต่ต้องรอ time slice เต็มก่อนสละ CPU เป็นการ waste time (3) งานที่ต้องการ real-time guarantee - ไม่มี priority ทำให้ไม่สามารถรับประกัน response time ได้

### ปัญหาที่พบจาก Time-Sharing

1. **No Priority Support:** ทุก task ได้เวลา CPU เท่ากัน ไม่ว่าจะสำคัญหรือไม่ งาน critical อาจถูก delay โดยงานที่ไม่สำคัญ ไม่เหมาะสำหรับ real-time systems ที่ต้องการ guaranteed response time

2. **Fixed Time Slice Problems:** งานสั้นต้องรอ time slice เต็ม (waste) ในขณะที่งานยาวถูกขัดจังหวะ (inefficient) ไม่มีความยืดหยุ่น ต้องเลือก time slice ที่เป็น compromise ระหว่างทุก task types

3. **Context Switching Overhead:** สูญเสีย CPU 10-30% ไปกับการสลับ task โดยเฉพาะเมื่อ time slice สั้น overhead รวมถึง save/restore context, cache flush, TLB flush และ scheduler decision making

4. **No Inter-task Communication:** ไม่มีกลไกในการแชร์ข้อมูลอย่างปลอดภัย อาจเกิด race condition หรือ data corruption ต้องใช้ global variables ซึ่งไม่ thread-safe ไม่มี synchronization primitives เช่น mutex, semaphore

### สรุปผล Lab 2

Lab 2 แสดงให้เห็นถึงข้อจำกัดของ Time-Sharing แบบ manual ที่แม้จะดีกว่า Single Task แต่ยังไม่เพียงพอสำหรับระบบที่ซับซ้อน ปัญหาหลักคือ Fixed time slice ไม่เหมาะกับทุก task, Context switching overhead สูงถึง 10-30%, และไม่มี priority mechanism ทำให้ไม่เหมาะสำหรับ real-time systems

การทดลองแสดงให้เห็นว่า time slice 50ms ให้ผลลัพธ์ที่สมดุลดีที่สุด (efficiency 88%, overhead 12%) แต่ก็ยังมีข้อจำกัดในการรับประกัน response time และการจัดการ priority ซึ่งเป็นเหตุผลว่าทำไมจึงต้องมี RTOS ที่มี dynamic priority scheduling, efficient context switching และ inter-task communication mechanisms

---

## Lab 3: Cooperative vs Preemptive Comparison

### วัตถุประสงค์
เปรียบเทียบ Cooperative Multitasking กับ Preemptive Multitasking และเข้าใจข้อดี-ข้อเสีย

### อุปกรณ์ที่ใช้
- ESP32 Development Board
- LED 3 ดวง (GPIO2, GPIO4, GPIO5)
- Push Button (GPIO0 - ใช้ปุ่ม BOOT)
- Resistor 220Ω × 3
- คอมพิวเตอร์

### วิธีการทดลอง

#### Part 1: Cooperative Multitasking
1. เปิดโปรเจกต์ lab3-coop-vs-preemptive
2. ตั้งค่า `TEST_MODE` เป็น `TEST_MODE_COOPERATIVE` ในไฟล์ `main/multitask_comparison.c`
3. Build และ Flash: `idf.py fullclean && idf.py flash monitor`
4. กดปุ่ม GPIO0 หลายครั้งและบันทึกเวลาตอบสนอง 10 ครั้ง

#### Part 2: Preemptive Multitasking
1. ตั้งค่า `TEST_MODE` เป็น `TEST_MODE_PREEMPTIVE`
2. Build และ Flash: `idf.py fullclean && idf.py flash monitor`
3. กดปุ่ม GPIO0 หลายครั้งและบันทึกเวลาตอบสนอง 10 ครั้ง

### ผลการทดลอง

#### Cooperative Multitasking

| ครั้งที่ | Response Time (ms) | หมายเหตุ |
|---------|-------------------|----------|
| 1 | 85 | กด Task1 พึ่ง yield |
| 2 | 245 | กดขณะ Task2 ทำงาน |
| 3 | 120 | Task1 ทำงานครึ่งทาง |
| 4 | 380 | Worst case - Task2 ยังไม่ yield |
| 5 | 95 | Lucky - พอดี emergency |
| 6 | 210 | Task2 ต้องเสร็จก่อน |
| 7 | 155 | ปกติ |
| 8 | 290 | Task2 workload หนัก |
| 9 | 175 | รอ Task1 yield |
| 10 | 225 | เฉลี่ย |
| **เฉลี่ย** | **198** | **ไม่สม่ำเสมอ** |
| **สูงสุด** | **380** | **แย่มาก** |
| **ต่ำสุด** | **85** | **ดี** |

**สิ่งที่สังเกตได้:**
- Tasks จะ yield (สละ CPU) โดยสมัครใจเท่านั้น
- Response time แตกต่างกันมากขึ้นอยู่กับว่ากดช่วงงานไหน
- Worst case สูงถึง 380ms เมื่อ task ยังไม่ yield
- Task1 และ Task2 มี yield points หลายจุด ทำให้บางครั้งตอบสนองเร็ว
- ถ้า task มี bug ไม่ yield ทั้งระบบจะค้าง
- Response time ไม่สามารถ predict ได้

#### Preemptive Multitasking

| ครั้งที่ | Response Time (ms) | หมายเหตุ |
|---------|-------------------|----------|
| 1 | 8 | ทันที Priority 5 |
| 2 | 6 | Preempt ทันที |
| 3 | 9 | สม่ำเสมอมาก |
| 4 | 7 | RTOS switch เร็ว |
| 5 | 8 | คงที่ |
| 6 | 7 | ยอดเยี่ยม |
| 7 | 9 | < 10ms เสมอ |
| 8 | 6 | Priority ชัดเจน |
| 9 | 8 | Deterministic |
| 10 | 7 | Reliable |
| **เฉลี่ย** | **7.5** | **เร็วและคงที่** |
| **สูงสุด** | **9** | **ยอดเยี่ยม** |
| **ต่ำสุด** | **6** | **เร็วมาก** |

**สิ่งที่สังเกตได้:**
- RTOS บังคับสลับ task อัตโนมัติ ไม่ต้องรอ yield
- Response time สม่ำเสมอและ predictable (6-9ms)
- Emergency task (Priority 5) preempt task อื่นได้ทันที
- แม้ Task1 และ Task2 จะไม่มี voluntary yield ก็ไม่กระทบ response
- Priority มีผลชัดเจน - task สำคัญได้รันก่อนเสมอ
- เหมาะสำหรับ real-time systems ที่ต้องรับประกัน response time

### การวิเคราะห์ผล

#### ตารางเปรียบเทียบ

| ลักษณะ | Cooperative | Preemptive |
|--------|-------------|------------|
| Response Time เฉลี่ย | 198 ms | 7.5 ms |
| Response Time สูงสุด | 380 ms | 9 ms |
| ความคงที่ของ Response | ❌ ไม่คงที่ (85-380ms) | ✅ คงที่ (6-9ms) |
| ความซับซ้อน | ต่ำ - เข้าใจง่าย | สูง - ต้องเข้าใจ RTOS |
| Resource Usage | น้อย - overhead ต่ำ | มาก - context switch |
| Determinism | ❌ ไม่มี | ✅ มี - guaranteed |
| Real-time Suitability | ⚠️ Soft real-time | ✅ Hard real-time |

#### คำถามและคำตอบ

**1. ระบบไหนมีเวลาตอบสนองดีกว่า? เพราะอะไร?**

คำตอบ: Preemptive Multitasking มีเวลาตอบสนองดีกว่าอย่างชัดเจน โดยมีค่าเฉลี่ย 7.5ms เร็วกว่า Cooperative ถึง 26 เท่า และที่สำคัญคือมีความสม่ำเสมอ (worst case เพียง 9ms) ขณะที่ Cooperative มี worst case ถึง 380ms เหตุผลหลักคือ Preemptive ใช้ RTOS ที่สามารถบังคับให้ task หยุดทำงานทันที (preempt) เมื่อมี task priority สูงกว่าพร้อม โดยไม่ต้องรอให้ task ปัจจุบัน yield ด้วยความสมัครใจ ทำให้รับประกัน response time ได้ในระดับ microseconds

**2. ข้อดีของ Cooperative Multitasking คืออะไร?**

คำตอบ: ข้อดีของ Cooperative คือ (1) ความซับซ้อนต่ำ - เข้าใจและเขียนโค้ดง่ายกว่า ไม่ต้องกังวลเรื่อง race condition มากนัก (2) Context switch overhead ต่ำ - task yield เฉพาะเมื่อพร้อม จึงไม่ต้อง save/restore context บ่อย (3) ใช้ memory น้อย - ไม่ต้องมี complex scheduler และ stack management (4) Debugging ง่าย - execution flow linear กว่า ตามได้ง่าย (5) เหมาะกับ resource-constrained systems - เช่น MCU ขนาดเล็กที่ไม่มี RTOS

**3. ข้อเสียของ Cooperative Multitasking คืออะไร?**

คำตอบ: ข้อเสียของ Cooperative คือ (1) Response time ไม่แน่นอน - ขึ้นอยู่กับว่า task อื่นจะ yield เมื่อไหร่ ในกรณีเลวร้ายอาจช้าถึง 380ms (2) Starvation problem - task หนึ่งอาจครอบครอง CPU ถ้าลืม yield หรือมี infinite loop (3) ไม่มี priority - task ทุกตัวมีสิทธิเท่ากัน ไม่สามารถบังคับให้ task สำคัญทำก่อนได้ (4) Bug อันตราย - task หนึ่งมีปัญหาอาจทำให้ทั้งระบบค้าง (5) ไม่เหมาะสำหรับ hard real-time - ไม่สามารถรับประกัน deadline

**4. ในสถานการณ์ใดที่ Cooperative จะดีกว่า Preemptive?**

คำตอบ: Cooperative จะดีกว่าในสถานการณ์ (1) Resource-constrained systems - เช่น 8-bit MCU ที่มี RAM/Flash น้อย ไม่พอสำหรับ RTOS (2) งานง่ายๆ ที่รู้ workload ชัดเจน - เช่น sensor polling ที่ทราบเวลาแน่นอน (3) System ที่ไม่ต้องการ real-time guarantee - เช่น data logging ที่ delay เล็กน้อยไม่เป็นปัญหา (4) Trusted code environment - เมื่อแน่ใจว่าทุก task เขียนดีและ yield ถูกต้อง (5) Power-sensitive applications - context switch น้อยทำให้ประหยัดพลังงาน

**5. เหตุใด Preemptive จึงเหมาะสำหรับ Real-time systems?**

คำตอบ: Preemptive เหมาะสำหรับ Real-time systems เพราะ (1) Deterministic response - รับประกันเวลาตอบสนองได้แน่นอน (worst case 9ms จากการทดลอง) (2) Priority-based scheduling - task สำคัญได้รันก่อนเสมอ ไม่ถูกบล็อกโดย task priority ต่ำ (3) Preemption capability - สามารถขัดจังหวะ task ใดๆ ทันทีเมื่อมี task สำคัญกว่า (4) Guaranteed fairness - RTOS จัดการ CPU time อย่างเป็นธรรม ไม่มี task ใดครอบครอง CPU ได้ (5) Built-in synchronization - มี mutex, semaphore เพื่อป้องกัน race condition

### สรุปผล Lab 3

Lab 3 แสดงให้เห็นความแตกต่างชัดเจนระหว่าง Cooperative และ Preemptive Multitasking โดย Cooperative มี response time เฉลี่ย 198ms (worst case 380ms) ไม่สม่ำเสมอและ unpredictable ในขณะที่ Preemptive มี response time เพียง 7.5ms (worst case 9ms) ซึ่งเร็วกว่า 26 เท่าและ deterministic

Cooperative เหมาะสำหรับระบบง่ายๆ ที่มี resource จำกัด ไม่ต้องการ real-time guarantee และ developers มีความเชี่ยวชาญในการเขียน well-behaved tasks ที่ yield อย่างเหมาะสม ข้อดีคือความซับซ้อนต่ำ overhead น้อย และ debug ง่าย

Preemptive เหมาะสำหรับระบบที่ซับซ้อน ต้องการ deterministic response time มี multiple priority levels และต้องรับประกัน real-time deadlines RTOS จัดการทุกอย่างอัตโนมัติ ไม่ต้องพึ่งพา voluntary yielding ทำให้เหมาะกับ mission-critical applications เช่น automotive, medical devices และ industrial control systems

การเลือกใช้ขึ้นอยู่กับ trade-off ระหว่าง simplicity (Cooperative) กับ determinism (Preemptive) สำหรับ modern embedded systems ที่มี resource เพียงพอ Preemptive มักเป็นตัวเลือกที่ดีกว่าเนื่องจากให้ความน่าเชื่อถือและ maintainability ที่สูงกว่า

---

## สรุปรวมการทดลองทั้งหมด

### ความรู้ที่ได้รับ

1. **Single Task vs Multitasking**
   - Single Task System มีข้อจำกัดร้ายแรงในการตอบสนอง (2-3 วินาที) เนื่องจากทุกงานต้องรอกันเป็นคิว
   - Multitasking ด้วย FreeRTOS แก้ปัญหาได้โดยใช้ priority-based scheduling ทำให้ตอบสนองเร็วขึ้น 150 เท่า (< 20ms)
   - Priority mechanism เป็นสิ่งสำคัญในการรับประกันว่างานสำคัญจะได้รับการประมวลผลทันที

2. **Time-Sharing**
   - Manual time-sharing มี context switching overhead 10-30% ขึ้นอยู่กับขนาด time slice
   - Time slice 50ms ให้ผลลัพธ์สมดุลที่สุดระหว่าง efficiency (88%) และ response time
   - Fixed time slice ไม่เหมาะกับทุก task type - งานสั้นเสียเวลารอ งานยาวถูกขัดจังหวะ
   - ไม่มี priority support ทำให้ไม่เหมาะสำหรับ real-time systems

3. **Cooperative vs Preemptive**
   - Cooperative ง่ายและใช้ resource น้อยแต่ response time ไม่แน่นอน (85-380ms)
   - Preemptive ซับซ้อนกว่าแต่ให้ deterministic response (6-9ms) เหมาะสำหรับ real-time
   - การเลือกใช้ขึ้นอยู่กับความต้องการ: simplicity vs determinism

### การประยุกต์ใช้

**Single Task เหมาะสำหรับ:**
- งาน sequential ที่ไม่ต้องการ concurrent operations
- อุปกรณ์ขนาดเล็กมาก (< 8KB RAM) ที่ไม่รองรับ RTOS
- Proof-of-concept หรือ prototype ที่ต้องการความเรียบง่าย
- งานที่ไม่มี time-critical requirements

**Time-Sharing เหมาะสำหรับ:**
- ระบบที่ต้องการความยุติธรรมในการใช้ CPU (fair scheduling)
- Learning purposes เพื่อเข้าใจ scheduling concepts
- Legacy systems ที่ไม่สามารถ migrate ไป RTOS ได้
- งานที่มี workload ใกล้เคียงกันและไม่ต้องการ priority

**Cooperative เหมาะสำหรับ:**
- Microcontrollers ขนาดเล็ก (8-bit, 16-bit) ที่มี resource จำกัด
- งาน soft real-time ที่ delay เล็กน้อยยอมรับได้
- Event-driven systems ที่มี natural yield points
- งานที่ควบคุม execution flow ได้ดีและ trusted code

**Preemptive RTOS เหมาะสำหรับ:**
- Hard real-time systems (automotive, medical, aerospace)
- ระบบที่ต้องการ guaranteed response time < 10ms
- Complex multi-threaded applications
- Safety-critical systems ที่ต้องการ reliability สูง
- Modern 32-bit MCUs ที่มี resource เพียงพอ (>32KB RAM)

### ปัญหาที่พบและแนวทางแก้ไข

**ปัญหา:** Serial Monitor บางครั้งแสดงผลผิดเพี้ยนเมื่อ context switch เร็วมาก

**แนวทางแก้ไข:** ใช้ `vTaskDelay()` หรือ mutex protect การเข้าถึง UART เพื่อป้องกัน race condition ในการ print log หลายๆ task พร้อมกัน อีกวิธีคือใช้ `CONFIG_LOG_DEFAULT_LEVEL` ใน menuconfig เพื่อลด logging overhead

**ปัญหา:** LED บาง GPIO ไม่ทำงาน (GPIO6-11)

**แนวทางแก้ไข:** GPIO6-11 ถูกใช้โดย flash chip ไม่ควรใช้งาน ควรเลือก GPIO ที่ปลอดภัย เช่น GPIO2, GPIO4, GPIO5, GPIO18-19, GPIO21-23 เป็นต้น

**ปัญหา:** Stack overflow ใน task ทำให้ระบบ reset

**แนวทางแก้ไข:** เพิ่มขนาด stack ใน `xTaskCreate()` จาก 2048 เป็น 4096 หรือใช้ `uxTaskGetStackHighWaterMark()` เพื่อตรวจสอบ stack usage จริง

### ข้อเสนอแนะ

1. **สำหรับผู้เริ่มต้น:** เริ่มจาก Single Task เพื่อเข้าใจปัญหา จากนั้นเรียนรู้ FreeRTOS basics ก่อนไปยัง advanced features

2. **การออกแบบระบบ:** ควรวิเคราะห์ real-time requirements ก่อนเลือก architecture ไม่ใช่ใช้ RTOS ทุกโปรเจกต์

3. **Performance tuning:** ใช้ tools เช่น `uxTaskGetSystemState()` และ FreeRTOS trace เพื่อ profile และ optimize performance

4. **Best practices:** 
   - ใช้ `vTaskDelay()` แทน busy-wait loops
   - Set priority อย่างเหมาะสม (ไม่สูงหรือต่ำเกินไป)
   - ใช้ queue/semaphore สำหรับ inter-task communication
   - Monitor stack usage ป้องกัน overflow

5. **การพัฒนาต่อ:** ควรศึกษา advanced topics เช่น Direct-to-Task Notifications, Stream Buffers, Co-routines และ Tickless Idle เพื่อ optimize power consumption

### ข้อสังเกตเพิ่มเติม

จากการทดลองทั้ง 3 labs พบว่าวิวัฒนาการของ multitasking สะท้อนถึงความต้องการที่เพิ่มขึ้นของ embedded systems ที่ซับซ้อนมากขึ้น การเลือกใช้เทคนิคที่เหมาะสมต้องพิจารณา trade-offs ระหว่าง:
- **Simplicity vs Capability**
- **Resource usage vs Performance**  
- **Development time vs System reliability**

RTOS สมัยใหม่เช่น FreeRTOS ได้รวมเอาข้อดีของหลายเทคนิคมาไว้ด้วยกัน ให้ developer เลือกใช้ตามความเหมาะสม เช่น สามารถใช้ cooperative style ใน idle task เพื่อลด overhead หรือใช้ preemptive สำหรับ critical tasks ความยืดหยุ่นนี้ทำให้ FreeRTOS เป็นหนึ่งใน RTOS ที่ได้รับความนิยมสูงสุดใน embedded systems

---

## บันทึกภาพ

### Lab 1
- [x] ภาพ Single Task System - LED กระพริบเป็นลำดับ
- [x] ภาพ Multitasking System - LED กระพริบพร้อมกัน
- [x] Screenshot Serial Monitor - แสดง response time

### Lab 2
- [x] ภาพการทำงาน 4 LEDs - แต่ละ LED มี pattern ต่างกัน
- [x] Screenshot สถิติ - CPU utilization และ overhead
- [x] กราฟเปรียบเทียบ Time Slices - efficiency vs time slice size

### Lab 3
- [x] Screenshot Cooperative Response Time - แสดงความไม่สม่ำเสมอ
- [x] Screenshot Preemptive Response Time - แสดงความคงที่
- [x] กราฟเปรียบเทียบ - Cooperative vs Preemptive response time distribution

---

## ลายเซ็น

**ผู้ทำการทดลอง:** _____________________  **วันที่:** 1 ตุลาคม 2568

**ผู้ตรวจ:** _____________________  **วันที่:** _______________

**คะแนน:** _______ / 100

**ความคิดเห็นของผู้สอน:**
________________________________________________________________________
________________________________________________________________________
________________________________________________________________________

---

## หมายเหตุ

รายงานนี้เป็นส่วนหนึ่งของการเรียนรู้เกี่ยวกับวิวัฒนาการของ Multitasking ในไมโครคอนโทรลเลอร์ โดยใช้ ESP32 และ FreeRTOS เป็นเครื่องมือหลักในการทดลอง การทดลองแสดงให้เห็นถึงความสำคัญของ RTOS ในการพัฒนา embedded systems สมัยใหม่ที่ต้องการทั้ง real-time performance และ multi-tasking capabilities

### ไฟล์ที่เกี่ยวข้อง
- `/67030011/00-multitasking-evolution/lab1-single-vs-multi/` - Single Task vs Multitasking
- `/67030011/00-multitasking-evolution/lab2-time-sharing/` - Time-Sharing Implementation
- `/67030011/00-multitasking-evolution/lab3-coop-vs-preemptive/` - Cooperative vs Preemptive

### เอกสารอ้างอิง
1. FreeRTOS Reference Manual - Real Time Engineers Ltd.
2. ESP-IDF Programming Guide - Espressif Systems
3. "Real-Time Systems Design and Analysis" - Phillip A. Laplante
4. "MicroC/OS-III, The Real-Time Kernel" - Jean J. Labrosse
5. ESP32 Technical Reference Manual v4.8

---

**จบรายงาน**
