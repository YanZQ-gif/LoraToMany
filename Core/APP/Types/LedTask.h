//
// Created by YanZQ-PC on 2026/2/7.
//

#ifndef LORATOMANY_LED_H
#define LORATOMANY_LED_H
#include <stdint.h>


typedef enum {
    LED_LUNSHAN_OFF=0,
    LED_LUNSHAN_ON=1, //交替闪烁
}LEDState;

typedef struct {
    LEDState state;
    uint16_t shanTime;
}LEDMessage;

#endif //LORATOMANY_LED_H