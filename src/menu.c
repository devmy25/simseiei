// menu.c (ชั้น scene) - หน้าเมนู: วาดหัวเรื่อง "Hello my game" (step 3)
#include "menu.h"

void menu_render(HWND hwnd, HDC hdc)
{
    RECT rc;
    GetClientRect(hwnd, &rc);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(46, 93, 31));   /* ตัวอักษรเขียวเข้ม #2e5d1f */

    /* หัวเรื่อง "Hello my game" */
    HFONT titleFont = CreateFont(64, 0,0,0, FW_BOLD, FALSE,FALSE,FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Trebuchet MS");
    HFONT oldFont = SelectObject(hdc, titleFont);

    RECT titleRc = rc;
    titleRc.top = 80;
    DrawText(hdc, "Hello my game", -1, &titleRc, DT_CENTER | DT_TOP | DT_SINGLELINE);

    SelectObject(hdc, oldFont);
    DeleteObject(titleFont);
}

MenuAction menu_on_click(HWND hwnd, int x, int y)
{
    (void)hwnd; (void)x; (void)y;
    return MENU_ACTION_NONE;   /* ยังไม่มีปุ่มให้คลิก */
}
