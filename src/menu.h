#ifndef MENU_H
#define MENU_H

#include <windows.h>

/* ============================================================
   ชั้น "scene" - หน้าเมนูหลัก
   รู้ว่าจะวาดอะไร และตอบสนองการคลิกยังไง (ไม่ยุ่ง Win32 ตรงๆ)
   ============================================================ */

/* ผลลัพธ์เมื่อผู้เล่นคลิกเมนู - บอกชั้น platform ว่าให้ทำอะไรต่อ */
typedef enum {
    MENU_ACTION_NONE = 0,   /* ไม่ได้คลิกโดนปุ่มไหน */
    MENU_ACTION_NEW_GAME,   /* ปุ่ม New Game */
    MENU_ACTION_LOAD,       /* ปุ่ม Load Game Save */
    MENU_ACTION_QUIT        /* ปุ่ม Quick -> ออกจากโปรแกรม (ตอนนี้) */
} MenuAction;

/* วาดหน้าเมนูทั้งหมด (หัวเรื่อง + ปุ่ม) ลงบน hdc */
void menu_render(HWND hwnd, HDC hdc);

/* เช็คว่าคลิกที่ (x, y) โดนปุ่มไหน แล้วคืน action ที่ต้องทำ */
MenuAction menu_on_click(HWND hwnd, int x, int y);

/* อัปเดตปุ่มที่เมาส์กำลังชี้อยู่ (เรียกตอนเมาส์ขยับ) เพื่อทำไฮไลต์ */
void menu_on_mouse_move(HWND hwnd, int x, int y);

#endif /* MENU_H */
