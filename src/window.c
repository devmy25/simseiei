// window.c (ชั้น platform) - ต่อสายสลับฉาก: New Game -> เกม, Esc -> เมนู (step 7.4)
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

            /* วาดตามฉากปัจจุบัน */
            if (scene_get() == SCENE_MENU)
                menu_render(hwnd, hdc);
            else
                game_render(hwnd, hdc);

            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_MOUSEMOVE:
            if (scene_get() == SCENE_MENU)
                menu_on_mouse_move(hwnd, LOWORD(lParam), HIWORD(lParam));
            return 0;

        case WM_SETCURSOR:
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
            if (scene_get() == SCENE_MENU)
            {
                MenuAction action = menu_on_click(hwnd, LOWORD(lParam), HIWORD(lParam));

                if (action == MENU_ACTION_NEW_GAME)
                {
                    scene_set(SCENE_GAME);              /* พลิกสมุดไปฉากเกม */
                    InvalidateRect(hwnd, NULL, TRUE);   /* ขอวาดจอใหม่ */
                }
                else if (action == MENU_ACTION_QUIT)
                {
                    DestroyWindow(hwnd);                /* ปุ่ม Quick -> ออกจากโปรแกรม */
                }
                /* MENU_ACTION_LOAD ยังไม่ทำ ไว้ step ต่อไป */
            }
            return 0;

        case WM_KEYDOWN:
            /* กด Esc ตอนอยู่ในเกม -> กลับหน้าเมนู */
            if (wParam == VK_ESCAPE && scene_get() == SCENE_GAME)
            {
                scene_set(SCENE_MENU);
                InvalidateRect(hwnd, NULL, TRUE);
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
