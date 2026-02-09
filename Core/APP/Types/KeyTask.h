//
// Created by YanZQ-PC on 2026/2/7.
//
#include "main.h"

#ifndef LORATOMANY_KEY_H
#define LORATOMANY_KEY_H

#define KEY1_DIN()  HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEY2_DIN()  HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
#define KEY3_DIN()  HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)

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

#define KEY_GUANDENG    KEY_1_DOWN  // 关灯对应1键按下
#define KEY_TIAOLIANGDU KEY_2_DOWN  // 调亮度对应2键按下
#define KEY_KAIDENG     KEY_3_DOWN  // 开灯对应3键按下

uint8_t DetectKey(void);

#endif //LORATOMANY_KEY_H