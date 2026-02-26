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

typedef enum {
    LED_LUNSHAN_OFF=0,
    LED_LUNSHAN_ON=1, //交替闪烁
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
    uint8_t  enabled;
    uint8_t  blinkState;
    uint32_t lastBlinkTime;
    uint8_t  brightness;
    uint8_t  pwmMode;
}LED_DEV;

#endif //LORATOMANY_LED_H