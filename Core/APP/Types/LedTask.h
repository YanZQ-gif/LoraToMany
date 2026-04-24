//
// Created by YanZQ-PC on 2026/2/7.
//

#ifndef LORATOMANY_LED_H
#define LORATOMANY_LED_H
#include <stdint.h>
#include "main.h"
#include "tim.h"

#define  LED1(n) (n?HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET))
#define  LED2(n) (n?HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET))
#define  BEEP(n) (n?HAL_GPIO_WritePin(BUZ_GPIO_Port,BUZ_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(BUZ_GPIO_Port,BUZ_Pin,GPIO_PIN_RESET))

#define  LED1_Toggle (HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin))
#define  LED2_Toggle (HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin))

#define  LED1_PWM(duty) __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, duty)
#define  LED2_PWM(duty) __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, duty)
#define  LED3_PWM(duty) __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, duty)

typedef enum {
    LED_LUNSHAN=0,   //正常闪烁
    LED_BAOSHAN=1,   //快速闪烁
    LED_3_ALL_ON=2,  //3灯全亮
}LEDState;

typedef enum {
    BRIGHTNESS_100 = 0,  // 100%
    BRIGHTNESS_75 = 1,   // 75%
    BRIGHTNESS_50 = 2,   // 50%
    BRIGHTNESS_25 = 3,   // 25%
    BRIGHTNESS_0 = 4,    // 0% (关闭)
}BrightnessLevel;

typedef struct {
    LEDState state;
    uint16_t shanTime;
    uint16_t baoshanTime;
    uint8_t  ledshan_enabled;
    uint8_t  beep_enabled;
    uint8_t  blinkState;
    uint32_t lastBlinkTime;
    uint8_t  brightness;
    uint8_t  pwmMode;
}LED_DEV;

#endif //LORATOMANY_LED_H