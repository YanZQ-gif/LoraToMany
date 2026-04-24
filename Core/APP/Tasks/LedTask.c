//
// Created by YanZQ-PC on 2026/2/7.
//
#include "cmsis_os2.h"
#include "LedTask.h"
#include "KeyTask.h"

static LED_DEV ledDev;

static const uint16_t brightnessTable[] = {
    1000, // 100% (ARR=1000)
    750, // 75%
    500, // 50%
    250, // 25%
    0     // 0%
};

static void LedBlink(void)  //普通闪
{
    uint32_t currentTime = osKernelGetTickCount();
    if ((currentTime - ledDev.lastBlinkTime) >= ledDev.shanTime) {
        if (ledDev.blinkState == 0) {
            LED1_PWM(brightnessTable[BRIGHTNESS_100]);
            LED2_PWM(brightnessTable[BRIGHTNESS_0]);
            LED3_PWM(brightnessTable[BRIGHTNESS_0]);
            ledDev.blinkState = 1;
            if (ledDev.beep_enabled) {BEEP(1);}
        } else {
            LED1_PWM(brightnessTable[BRIGHTNESS_0]);
            LED2_PWM(brightnessTable[BRIGHTNESS_100]);
            LED3_PWM(brightnessTable[BRIGHTNESS_0]);
            ledDev.blinkState = 0;
            if (ledDev.beep_enabled) {BEEP(0);}
        }
        ledDev.lastBlinkTime = currentTime;
    }
}

static void LedProcessCommand(uint32_t cmd)
{
    switch(cmd) {
        case KEY_BAOJING:
            if (!ledDev.ledshan_enabled) {
                ledDev.ledshan_enabled = 1;
                ledDev.beep_enabled = 1; //只有报警，蜂鸣器响
                ledDev.shanTime = 300;  //快闪时间调整
                ledDev.blinkState = 0;
                ledDev.lastBlinkTime = osKernelGetTickCount();
                ledDev.pwmMode = 0;
            }
            break;

        case KEY_KAIDENG:
            if (!ledDev.ledshan_enabled) {

                if (ledDev.state == LED_LUNSHAN) {
                    ledDev.ledshan_enabled = 1;
                    ledDev.beep_enabled = 0;  //关蜂鸣器
                    ledDev.shanTime = 300;
                }//慢闪时间调整
                else if (ledDev.state == LED_BAOSHAN) {
                    ledDev.ledshan_enabled = 1;
                    ledDev.beep_enabled = 0;  //关蜂鸣器
                    ledDev.shanTime = 50;
                }//爆闪时间调整
                else if (ledDev.state == LED_3_ALL_ON) {                     //3灯全亮，禁闪烁使能
                    ledDev.ledshan_enabled = 0;
                    ledDev.beep_enabled = 0;  //关蜂鸣器
                    LED1_PWM(brightnessTable[BRIGHTNESS_100]);
                    LED2_PWM(brightnessTable[BRIGHTNESS_100]);
                    LED3_PWM(brightnessTable[BRIGHTNESS_100]);
                }
                ledDev.state++;  //每按1次 状态+1
                if (ledDev.state > LED_3_ALL_ON) { ledDev.state = LED_LUNSHAN; }  //回到0状态
                ledDev.blinkState = 0;
                ledDev.lastBlinkTime = osKernelGetTickCount();
                ledDev.pwmMode = 0;
            }
            break;

        case KEY_GUANDENG:
            ledDev.ledshan_enabled = 0;
            ledDev.beep_enabled = 0;  //关蜂鸣器
            LED1_PWM(brightnessTable[BRIGHTNESS_0]);
            LED2_PWM(brightnessTable[BRIGHTNESS_0]);
            LED3_PWM(brightnessTable[BRIGHTNESS_0]);
            ledDev.brightness = 0;
            BEEP(0);
            break;

        default: break;
    }
}


void StartLedTask(void *argument)
{
    /* USER CODE BEGIN StartKeyTask */
    ledDev.state = LED_LUNSHAN;
    ledDev.shanTime = 300;
    ledDev.ledshan_enabled = 0;
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

        if (ledDev.ledshan_enabled) {
            LedBlink();
        }
    }
    /* USER CODE END StartKeyTask */
}
