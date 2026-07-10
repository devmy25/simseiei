// game.c (ชั้น scene) - หน้าในเกม แบบ placeholder (step 7.2)
#include "game.h"

void game_render(HWND hwnd, HDC hdc)
{
    RECT rc;
    GetClientRect(hwnd, &rc);

    /* พื้นหลังฉากเกม - สีฟ้าอ่อน (จงใจให้คนละสีกับเมนู จะได้เห็นชัดว่าเปลี่ยนฉากแล้ว) */
    HBRUSH bg = CreateSolidBrush(RGB(140, 190, 230));
    FillRect(hdc, &rc, bg);
    DeleteObject(bg);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(20, 50, 80));      /* น้ำเงินเข้ม */

    /* ข้อความใหญ่กลางจอ */
    HFONT bigFont = CreateFont(56, 0,0,0, FW_BOLD, FALSE,FALSE,FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Trebuchet MS");
    HFONT oldFont = SelectObject(hdc, bigFont);

    RECT titleRc = rc;
    titleRc.top = 200;
    DrawText(hdc, "In Game!", -1, &titleRc, DT_CENTER | DT_TOP | DT_SINGLELINE);

    SelectObject(hdc, oldFont);
    DeleteObject(bigFont);

    /* ข้อความเล็ก บอกวิธีกลับเมนู */
    HFONT smallFont = CreateFont(24, 0,0,0, FW_NORMAL, FALSE,FALSE,FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Trebuchet MS");
    oldFont = SelectObject(hdc, smallFont);

    RECT hintRc = rc;
    hintRc.top = 300;
    DrawText(hdc, "Press Esc to return to menu", -1, &hintRc, DT_CENTER | DT_TOP | DT_SINGLELINE);

    SelectObject(hdc, oldFont);
    DeleteObject(smallFont);
}
