// window.c (ชั้น platform) - สร้างหน้าต่าง + วงวนหลัก (step 1)
#include "window.h"

#define WIN_TITLE  "Sim Seiei"
#define WIN_WIDTH  800
#define WIN_HEIGHT 600

/* WndProc = ฝ่ายรับข่าวของหน้าต่าง (เก็บเป็น static ใช้เฉพาะในไฟล์นี้) */
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
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
