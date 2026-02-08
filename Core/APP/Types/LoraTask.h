//
// Created by YanZQ-PC on 2026/2/7.
//

#ifndef LORATOMANY_LORA_H
#define LORATOMANY_LORA_H

#define LORA_DEV_ID 0 //每个设备不一样 0-255  最多255个设备
#define LORA_CMD_FRAME_ID  1  // 指令帧 ID
#define LORA_ACK_FRAME_ID  2  // 回应帧 ID
#define LORA_STA_FRAME_ID  3  // 状态帧 ID

//d_id:设备id 宏定义好
void  Lora_SendFrame(uint8_t data, uint8_t f_id ,uint8_t d_id);
void  LoraProcess( void );

#endif //LORATOMANY_LORA_H