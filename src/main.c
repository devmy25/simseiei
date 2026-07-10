// Sim Seiei - จุดเริ่มต้นของโปรแกรม
// หน้าที่: เปิดหน้าต่างเกม แล้วเข้าวงวนหลัก
// (รายละเอียดจริงแยกไปอยู่ตามโมดูล window / menu)

#include <windows.h>
#include "window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    (void)hPrevInstance;   /* พารามิเตอร์ที่ไม่ได้ใช้ (กัน warning) */
    (void)lpCmdLine;

    /* สร้างหน้าต่างเกม */
    HWND hwnd = window_create(hInstance, nCmdShow);
    if (hwnd == NULL)
        return 1;          /* สร้างไม่สำเร็จ -> ออกด้วย error code */

    /* เข้าวงวนหลัก วนจนกว่าจะปิดหน้าต่าง */
    return window_run();
}
