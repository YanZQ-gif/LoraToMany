//
// Created by YanZQ-PC on 2026/2/7.
//
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "KeyTask.h"
#include "main.h"
#include "LoraTask.h"


void StartLedTask(void *argument)
{
    /* USER CODE BEGIN StartLedTask */
    /* Infinite loop */
    for(;;)
    {
        for (;;) {
            KEY_ENUM key = DetectKey(); //貌似不用消息队列，直接解析到键值发送lora就可以
            if (key != KEY_NONE) {
                //osMessageQueuePut(KeyMsgQueueHandle,&key,0,osWaitForever);
                Lora_SendFrame(key,LORA_CMD_FRAME_ID,LORA_DEV_ID);
            }
            osDelay(50);
        }
    }
    /* USER CODE END StartLedTask */
}

uint8_t DetectKey(void) {
    //3个按键按下为低电平
    if (HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == GPIO_PIN_RESET) {
        TickType_t conunt1 = xTaskGetTickCount();
        osDelay(5);
        if (HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == GPIO_PIN_RESET) {
            while (HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)== GPIO_PIN_RESET) {
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
    else if (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET) {
        TickType_t conunt1 = xTaskGetTickCount();
        osDelay(5);
        if (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET) {
            while (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET) {
                osDelay(1);//可以观察高优先级任务占用CPU的情况
            }
            TickType_t conunt2 = xTaskGetTickCount();
            if (conunt2-conunt1 > 500) {
                return KEY_3_LONG;
            }
            else {
                return KEY_2_DOWN;
            }
        }
    }
    else if (HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == GPIO_PIN_RESET) {
        TickType_t conunt1 = xTaskGetTickCount();
        osDelay(5);
        if (HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == GPIO_PIN_RESET) {
            while (HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == GPIO_PIN_RESET) {
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
