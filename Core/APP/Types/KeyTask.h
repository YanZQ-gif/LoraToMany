//
// Created by YanZQ-PC on 2026/2/7.
//
#include "main.h"

#ifndef LORATOMANY_KEY_H
#define LORATOMANY_KEY_H

typedef enum {
    KEY_NONE = 0,			/* 0 表示按键事件 */

    KEY_1_DOWN,				/* 1键按下 */  //关灯
    KEY_1_UP,				/* 1键弹起 */
    KEY_1_LONG,				/* 1键长按 */

    KEY_2_DOWN,				/* 2键按下 */   //调亮度
    KEY_2_UP,				/* 2键弹起 */
    KEY_2_LONG,				/* 2键长按 */

    KEY_3_DOWN,				/* 3键按下 */  //开灯
    KEY_3_UP,				/* 3键弹起 */
    KEY_3_LONG,				/* 3键长按 */
}KEY_ENUM;

uint8_t DetectKey(void);

#endif //LORATOMANY_KEY_H