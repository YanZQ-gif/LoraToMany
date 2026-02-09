//
// Created by YanZQ-PC on 2026/2/7.
//
#include "cmsis_os2.h"
#include "LedTask.h"
#include "KeyTask.h"

static LED_DEV ledDev;


void StartLedTask(void *argument)
{
    /* USER CODE BEGIN StartKeyTask */
    ledDev.state = LED_LUNSHAN_OFF;
    ledDev.shanTime = 100;
    ledDev.enabled = 0;
    ledDev.blinkState = 0;
    ledDev.lastBlinkTime = 0;

    /* Infinite loop */
    for(;;)
    {
        uint32_t cmd;
        osStatus_t status = osMessageQueueGet(LedMsgQueueHandle,&cmd,0,10);
        
        if (status == osOK) {
            switch(cmd) {
                case KEY_KAIDENG:
                    if (!ledDev.enabled) {
                        ledDev.enabled = 1;
                        ledDev.blinkState = 0;
                        ledDev.lastBlinkTime = osKernelGetTickCount();
                    }
                break;

                case KEY_GUANDENG:
                    ledDev.enabled = 0;
                    LED1(0);
                    LED2(0);
                break;

                case KEY_TIAOLIANGDU:
                //先不做
                break;

                default: break;
            }
        }

        if (ledDev.enabled) {
            uint32_t currentTime = osKernelGetTickCount();
            if ((currentTime - ledDev.lastBlinkTime) >= ledDev.shanTime) {
                if (ledDev.blinkState == 0) {
                    LED1(1);
                    LED2(0);
                    ledDev.blinkState = 1;
                } else {
                    LED1(0);
                    LED2(1);
                    ledDev.blinkState = 0;
                }
                ledDev.lastBlinkTime = currentTime;
            }
        }
    }
    /* USER CODE END StartKeyTask */
}
