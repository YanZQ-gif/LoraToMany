//
// Created by YanZQ-PC on 2026/2/7.
//
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "KeyTask.h"
#include "main.h"


void StartKeyTask(void *argument)
{
    /* USER CODE BEGIN StartLedTask */
    /* Infinite loop */
    for(;;)
    {
        for (;;) {
            KEY_ENUM key = DetectKey();
            if (key != KEY_NONE) {
                osMessageQueuePut(LoraMsgQueueHandle,&key,0,10); //给lora任务消息
                osMessageQueuePut(LedMsgQueueHandle,&key,0,10);  //给自己灯任务消息
            }
            osDelay(50); //50ms扫描一次按键
        }
    }
    /* USER CODE END StartLedTask */
}

uint8_t DetectKey(void) {
    //3个按键按下为低电平
    if (KEY1_DIN() == GPIO_PIN_RESET) {
        TickType_t conunt1 = xTaskGetTickCount();
        osDelay(5);
        if (KEY1_DIN() == GPIO_PIN_RESET) {
            while (KEY1_DIN() == GPIO_PIN_RESET) {
                osDelay(1);//可以观察高优先级任务占用CPU的情况
            }
        }
        TickType_t conunt2 = xTaskGetTickCount();
        if (conunt2-conunt1 > 500) {
            return KEY_1_LONG;
        }
        else {
            return KEY_1_DOWN;
        }
    }
    else if (KEY2_DIN() == GPIO_PIN_RESET) {
        TickType_t conunt1 = xTaskGetTickCount();
        osDelay(5);
        if (KEY2_DIN() == GPIO_PIN_RESET) {
            while (KEY2_DIN() == GPIO_PIN_RESET) {
                osDelay(1);//可以观察高优先级任务占用CPU的情况
            }
            TickType_t conunt2 = xTaskGetTickCount();
            if (conunt2-conunt1 > 500) {
                return KEY_2_LONG;
            }
            else {
                return KEY_2_DOWN;
            }
        }
    }
    else if (KEY3_DIN()== GPIO_PIN_RESET) {
        TickType_t conunt1 = xTaskGetTickCount();
        osDelay(5);
        if (KEY3_DIN() == GPIO_PIN_RESET) {
            while (KEY3_DIN() == GPIO_PIN_RESET) {
                osDelay(1);//可以观察高优先级任务占用CPU的情况
            }
            TickType_t conunt2 = xTaskGetTickCount();
            if (conunt2-conunt1 > 500) {
                return KEY_3_LONG;
            }
            else {
                return KEY_3_DOWN;
            }
        }
    }
    return KEY_NONE;
}
