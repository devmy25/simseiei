// window.c (ชั้น platform) - เพิ่มการรับคลิกเมาส์ ส่งให้ menu แล้วทำตาม action (step 5)
#include "window.h"
#include "menu.h"

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
            menu_render(hwnd, hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_LBUTTONDOWN:
        {
            /* ถามโมดูล menu ว่าคลิกตรงนี้แล้วต้องทำอะไร */
            MenuAction action = menu_on_click(hwnd, LOWORD(lParam), HIWORD(lParam));

            if (action == MENU_ACTION_QUIT)
                DestroyWindow(hwnd);       /* ปุ่ม Quick -> ปิดหน้าต่าง = ออกจากโปรแกรม */

            return 0;
        }

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
