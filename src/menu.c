// menu.c (ชั้น scene) - หน้าเมนู: เพิ่ม hit-testing เวลาคลิกปุ่ม (step 5)
#include "menu.h"

#define NUM_BUTTONS 3
#define BTN_W   320
#define BTN_H   60
#define BTN_GAP 18
#define BTN_TOP 220

static const char *g_labels[NUM_BUTTONS] = { "New Game", "Load Game Save", "Quick" };

/* กรอบสี่เหลี่ยมของปุ่มหมายเลข i - ใช้ทั้งตอนวาดและตอนเช็คคลิก จะได้ตรงกันเป๊ะ */
static RECT menu_button_rect(HWND hwnd, int i)
{
    RECT rc;
    GetClientRect(hwnd, &rc);

    int x   = (rc.right - BTN_W) / 2;
    int top = BTN_TOP + i * (BTN_H + BTN_GAP);

    RECT br = { x, top, x + BTN_W, top + BTN_H };
    return br;
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

    HPEN   pen      = CreatePen(PS_SOLID, 3, RGB(110, 168, 61));
    HBRUSH brush    = CreateSolidBrush(RGB(255, 255, 255));
    HPEN   oldPen   = SelectObject(hdc, pen);
    HBRUSH oldBrush = SelectObject(hdc, brush);

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        RECT br = menu_button_rect(hwnd, i);
        RoundRect(hdc, br.left, br.top, br.right, br.bottom, 20, 20);
        DrawText(hdc, g_labels[i], -1, &br, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    SelectObject(hdc, oldFont);
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(btnFont);
    DeleteObject(pen);
    DeleteObject(brush);
}

MenuAction menu_on_click(HWND hwnd, int x, int y)
{
    POINT pt = { x, y };

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        RECT br = menu_button_rect(hwnd, i);
        if (PtInRect(&br, pt))          /* คลิกโดนกรอบปุ่ม i ไหม? */
        {
            switch (i)
            {
                case 0: return MENU_ACTION_NEW_GAME;
                case 1: return MENU_ACTION_LOAD;
                case 2: return MENU_ACTION_QUIT;   /* ปุ่ม Quick -> ออกจากโปรแกรม */
            }
        }
    }
    return MENU_ACTION_NONE;   /* ไม่โดนปุ่มไหนเลย */
}
