// menu.c (ชั้น scene) - เพิ่มไฮไลต์ปุ่มตอนเมาส์ชี้ (hover) (step 6)
#include "menu.h"

#define NUM_BUTTONS 3
#define BTN_W   320
#define BTN_H   60
#define BTN_GAP 18
#define BTN_TOP 220

static const char *g_labels[NUM_BUTTONS] = { "New Game", "Load Game Save", "Quick" };
static int g_hover = -1;   /* ปุ่มที่เมาส์กำลังชี้อยู่ (-1 = ไม่ได้ชี้ปุ่มไหน) */

/* กรอบสี่เหลี่ยมของปุ่มหมายเลข i - ใช้ทั้งตอนวาด / เช็คคลิก / เช็ค hover จะได้ตรงกัน */
static RECT menu_button_rect(HWND hwnd, int i)
{
    RECT rc;
    GetClientRect(hwnd, &rc);

    int x   = (rc.right - BTN_W) / 2;
    int top = BTN_TOP + i * (BTN_H + BTN_GAP);

    RECT br = { x, top, x + BTN_W, top + BTN_H };
    return br;
}

/* หาว่าจุด (x, y) อยู่บนปุ่มไหน คืน index (0..) หรือ -1 ถ้าไม่โดนปุ่มไหนเลย */
static int menu_button_at(HWND hwnd, int x, int y)
{
    POINT pt = { x, y };
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        RECT br = menu_button_rect(hwnd, i);
        if (PtInRect(&br, pt))
            return i;
    }
    return -1;
}

/* คืน 1 ถ้า (x, y) อยู่บนปุ่มใดปุ่มหนึ่ง (ไว้ให้ window เปลี่ยนเคอร์เซอร์เป็นรูปมือ) */
int menu_is_over_button(HWND hwnd, int x, int y)
{
    return menu_button_at(hwnd, x, y) >= 0;
}

void menu_render(HWND hwnd, HDC hdc)
{
    RECT rc;
    GetClientRect(hwnd, &rc);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(46, 93, 31));

    /* ---------- (1) หัวเรื่อง ---------- */
    HFONT titleFont = CreateFont(64, 0,0,0, FW_BOLD, FALSE,FALSE,FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Trebuchet MS");
    HFONT oldFont = SelectObject(hdc, titleFont);

    RECT titleRc = rc;
    titleRc.top = 80;
    DrawText(hdc, "Hello my game", -1, &titleRc, DT_CENTER | DT_TOP | DT_SINGLELINE);

    SelectObject(hdc, oldFont);
    DeleteObject(titleFont);

    /* ---------- (2) ปุ่มเมนู ---------- */
    HFONT btnFont = CreateFont(28, 0,0,0, FW_BOLD, FALSE,FALSE,FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Trebuchet MS");
    oldFont = SelectObject(hdc, btnFont);

    HPEN   pen        = CreatePen(PS_SOLID, 3, RGB(110, 168, 61));  /* ขอบเขียว */
    HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));       /* พื้นขาว (ปุ่มปกติ) */
    HBRUSH hoverBrush = CreateSolidBrush(RGB(234, 255, 207));       /* พื้นเขียวอ่อน (ปุ่มที่ชี้) #eaffcf */
    HPEN   oldPen     = SelectObject(hdc, pen);
    HBRUSH oldBrush   = SelectObject(hdc, whiteBrush);

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        RECT br = menu_button_rect(hwnd, i);

        /* ปุ่มที่เมาส์ชี้อยู่ -> พื้นเขียวอ่อน, ปุ่มอื่น -> พื้นขาว */
        SelectObject(hdc, (i == g_hover) ? hoverBrush : whiteBrush);

        RoundRect(hdc, br.left, br.top, br.right, br.bottom, 20, 20);
        DrawText(hdc, g_labels[i], -1, &br, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    SelectObject(hdc, oldFont);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);        /* คืนแปรงเดิมก่อน แล้วค่อยลบแปรงที่สร้าง */
    DeleteObject(btnFont);
    DeleteObject(pen);
    DeleteObject(whiteBrush);
    DeleteObject(hoverBrush);
}

void menu_on_mouse_move(HWND hwnd, int x, int y)
{
    int now = menu_button_at(hwnd, x, y);

    if (now != g_hover)                     /* ปุ่มที่ชี้เปลี่ยนไป -> ค่อยสั่งวาดใหม่ */
    {
        g_hover = now;
        InvalidateRect(hwnd, NULL, TRUE);   /* บอก Windows ว่าจอเปลี่ยนแล้ว ขอวาดใหม่ */
    }
}

MenuAction menu_on_click(HWND hwnd, int x, int y)
{
    int i = menu_button_at(hwnd, x, y);

    switch (i)
    {
        case 0: return MENU_ACTION_NEW_GAME;
        case 1: return MENU_ACTION_LOAD;
        case 2: return MENU_ACTION_QUIT;    /* ปุ่ม Quick -> ออกจากโปรแกรม */
    }
    return MENU_ACTION_NONE;                /* ไม่โดนปุ่มไหนเลย */
}
