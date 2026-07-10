// scene.c - สมุดจดว่าตอนนี้อยู่ฉากไหน (เก็บไว้ที่เดียว ใครๆ ก็มาอ่าน/แก้ได้)
#include "scene.h"

/* ตัวแปรจำฉากปัจจุบัน  เริ่มต้นที่หน้าเมนูเสมอ
   (static = ใช้ได้เฉพาะในไฟล์นี้ ข้างนอกต้องเรียกผ่าน scene_get/scene_set) */
static SceneId g_current = SCENE_MENU;

SceneId scene_get(void)
{
    return g_current;
}

void scene_set(SceneId id)
{
    g_current = id;
}
