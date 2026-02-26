//
// Created by YanZQ-PC on 2026/2/7.
//
#include "cmsis_os2.h"
#include "LedTask.h"
#include "KeyTask.h"

static LED_DEV ledDev;

static const uint16_t brightnessTable[] = {
    1000,  // 100% (ARR=1000)
    750,   // 75%
    500,   // 50%
    250,   // 25%
    0     // 0%
};

static void LedSetBrightness(uint8_t level)
{
    if (level >= 5) level = 4;
    ledDev.brightness = level;
    //LED1_PWM(brightnessTable[level]);
    LED2_PWM(brightnessTable[level]);
}

static void LedBlink(void)
{
    uint32_t currentTime = osKernelGetTickCount();
    if ((currentTime - ledDev.lastBlinkTime) >= ledDev.shanTime) {
        if (ledDev.blinkState == 0) {
            LED1_PWM(brightnessTable[BRIGHTNESS_100]);
            LED2_PWM(brightnessTable[BRIGHTNESS_0]);
            ledDev.blinkState = 1;
            BEEP(1);
        } else {
            LED1_PWM(brightnessTable[BRIGHTNESS_0]);
            LED2_PWM(brightnessTable[BRIGHTNESS_100]);
            ledDev.blinkState = 0;
            BEEP(0);
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
                ledDev.pwmMode = 0;
            }
            break;

        case KEY_GUANDENG:
            ledDev.enabled = 0;
            LED1_PWM(brightnessTable[BRIGHTNESS_0]);
            LED2_PWM(brightnessTable[BRIGHTNESS_0]);
            ledDev.brightness = 0;
            BEEP(0);
            break;

        case KEY_TIAOLIANGDU:
            if (!ledDev.enabled) {
                ledDev.brightness++;
                if (ledDev.brightness >= 5) {
                    ledDev.brightness = 0;
                }
                LedSetBrightness(ledDev.brightness);
            }
            break;

        default: break;
    }
}


void StartLedTask(void *argument)
{
    /* USER CODE BEGIN StartKeyTask */
    ledDev.state = LED_LUNSHAN_OFF;
    ledDev.shanTime = 300;
    ledDev.enabled = 0;
    ledDev.blinkState = 0;
    ledDev.lastBlinkTime = 0;
    ledDev.brightness = 0;
    ledDev.pwmMode = 0;
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);

    /* Infinite loop */
    for(;;)
    {
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
