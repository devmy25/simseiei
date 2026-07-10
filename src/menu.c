// menu.c (ชั้น scene) - ยังเป็นโครงเปล่า เดี๋ยว step 3 เป็นต้นไปค่อยเติม
#include "menu.h"

void menu_render(HWND hwnd, HDC hdc)
{
    (void)hwnd;
    (void)hdc;
    /* ยังไม่วาดอะไร */
}

MenuAction menu_on_click(HWND hwnd, int x, int y)
{
    (void)hwnd; (void)x; (void)y;
    return MENU_ACTION_NONE;   /* ยังไม่ทำอะไร */
}
