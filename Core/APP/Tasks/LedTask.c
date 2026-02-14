//
// Created by YanZQ-PC on 2026/2/7.
//
#include "cmsis_os2.h"
#include "LedTask.h"
#include "KeyTask.h"

static LED_DEV ledDev;

static void LedBlink(void)
{
    uint32_t currentTime = osKernelGetTickCount();
    if ((currentTime - ledDev.lastBlinkTime) >= ledDev.shanTime) {
        if (ledDev.blinkState == 0) {
            LED1(1);
            LED2(0);
            BEEP(1);
            ledDev.blinkState = 1;
        } else {
            LED1(0);
            LED2(1);
            BEEP(0);
            ledDev.blinkState = 0;
        }
        ledDev.lastBlinkTime = currentTime;
    }
}

static void LedProcessCommand(uint32_t cmd)
{
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
            BEEP(0);
            break;

        case KEY_TIAOLIANGDU:
        //先不做
            break;

        default: break;
    }
}


void StartLedTask(void *argument)
{
    /* USER CODE BEGIN StartKeyTask */
    ledDev.state = LED_LUNSHAN_OFF;
    ledDev.shanTime = 400;
    ledDev.enabled = 0;
    ledDev.blinkState = 0;
    ledDev.lastBlinkTime = 0;

    /* Infinite loop */
    for(;;)
    {
        //uint32_t cmd;
        KEY_ENUM cmd;
        osStatus_t status = osMessageQueueGet(LedMsgQueueHandle,&cmd,0,10);
        
        if (status == osOK) {
            LedProcessCommand(cmd);
        }

        if (ledDev.enabled) {
            LedBlink();
        }
    }
    /* USER CODE END StartKeyTask */
}
