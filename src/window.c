// window.c (ชั้น platform) - เลือกวาด/ตอบสนองตาม "ฉากปัจจุบัน" (step 7.3)
#include "window.h"
#include "scene.h"
#include "menu.h"
#include "game.h"

#define WIN_TITLE  "Sim Seiei"
#define WIN_WIDTH  800
#define WIN_HEIGHT 600

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            /* เปิดสมุดจดดูว่าอยู่ฉากไหน แล้ววาดฉากนั้น */
            if (scene_get() == SCENE_MENU)
                menu_render(hwnd, hdc);
            else
                game_render(hwnd, hdc);

            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_MOUSEMOVE:
            /* ไฮไลต์ปุ่ม มีเฉพาะในฉากเมนู */
            if (scene_get() == SCENE_MENU)
                menu_on_mouse_move(hwnd, LOWORD(lParam), HIWORD(lParam));
            return 0;

        case WM_SETCURSOR:
            /* เคอร์เซอร์รูปมือ มีเฉพาะตอนชี้ปุ่มในฉากเมนู */
            if (scene_get() == SCENE_MENU && LOWORD(lParam) == HTCLIENT)
            {
                POINT pt;
                GetCursorPos(&pt);
                ScreenToClient(hwnd, &pt);
                if (menu_is_over_button(hwnd, pt.x, pt.y))
                {
                    SetCursor(LoadCursor(NULL, IDC_HAND));
                    return TRUE;
                }
            }
            return DefWindowProc(hwnd, msg, wParam, lParam);

        case WM_LBUTTONDOWN:
            /* คลิกปุ่ม มีเฉพาะในฉากเมนู */
            if (scene_get() == SCENE_MENU)
            {
                MenuAction action = menu_on_click(hwnd, LOWORD(lParam), HIWORD(lParam));

                if (action == MENU_ACTION_QUIT)
                    DestroyWindow(hwnd);       /* ปุ่ม Quick -> ออกจากโปรแกรม */
                /* New Game จะมาต่อสายใน step 7.4 */
            }
            return 0;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

HWND window_create(HINSTANCE hInstance, int nCmdShow)
{
    const char CLASS_NAME[] = "SimSeieiWindow";

    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(207, 230, 168));  /* พื้นหลังเขียวอ่อน */

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, WIN_TITLE, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT,
        NULL, NULL, hInstance, NULL);

    if (hwnd != NULL)
        ShowWindow(hwnd, nCmdShow);

    return hwnd;
}

int window_run(void)
{
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
