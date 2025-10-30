# สำหรับการทดสอบ Single Task ให้ใช้:
# idf_component_register(SRCS "single_task.c" INCLUDE_DIRS ".")

# สำหรับการทดสอบ Multitasking ให้ใช้:
idf_component_register(SRCS "multitask.c" INCLUDE_DIRS ".")

# สลับ comment เพื่อเปลี่ยนระหว่าง single_task.c และ multitask.c

