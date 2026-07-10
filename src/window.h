#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

/* ============================================================
   ชั้น "platform" - จัดการเรื่องหน้าต่างของ Windows โดยเฉพาะ
   (ส่วนเนื้อหาที่จะวาด/คลิก อยู่ในโมดูล menu แทน)
   ============================================================ */

/* สร้างหน้าต่างเกม
   คืน handle ของหน้าต่าง หรือ NULL ถ้าไม่สำเร็จ */
HWND window_create(HINSTANCE hInstance, int nCmdShow);

/* เข้าวงวนหลัก (message loop) วนจนกว่าจะปิดหน้าต่าง
   คืนค่า exit code ของโปรแกรม */
int window_run(void);

#endif /* WINDOW_H */
