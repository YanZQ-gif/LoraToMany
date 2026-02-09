//
// Created by YanZQ-PC on 2026/2/7.
//
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "LoraTask.h"
#include "Sx1276-1278.h"
#include "crc.h"
#include "radio.h"
#include "KeyTask.h"


uint8_t   RXBuffer[RF_BUFFER_SIZE];  //RX buffer
uint8_t   TXBuffer[RF_BUFFER_SIZE];  //TX buffer
tRadioDriver *Radio = 0;

void StartLoraTask(void *argument)
{
    /* USER CODE BEGIN StartLoraTask */

	Radio = RadioDriverInit();
	Radio->Init();
	Radio->StartRx();
    /* Infinite loop */
    for(;;)
    {
    	//osMessageQueuePut(KeyMsgQueueHandle,&key,0,osWaitForever);
    	uint32_t key;
    	osMessageQueueGet(LoraMsgQueueHandle,&key,0,0);
    	Lora_SendFrame(key,LORA_CMD_FRAME_ID,LORA_DEV_ID);
    	LoraProcess(); //查询接收
    }
    /* USER CODE END StartLoraTask */
}

void LoraProcess( void )
{
	uint16_t num_rx=0;
	uint16_t crc_value;
	switch(Radio->Process())
	{
		case RF_RX_DONE:
			Radio->GetRxPacket(RXBuffer,(uint16_t* )&num_rx );
			if(num_rx >0)
			{
				crc_value=RXBuffer[num_rx-2];
				crc_value<<=8;
				crc_value|=RXBuffer[num_rx-1];
				uint16_t crctemp=RadioComputeCRC(RXBuffer,num_rx-2,CRC_TYPE_IBM);
				if(crc_value==crctemp)//CRC check
				{
					//收到空中LORA消息，发led消息动作led
					osMessageQueuePut(LedMsgQueueHandle,&RXBuffer[4],0,10);
				}
			}
			break;

        case RF_TX_DONE:
			Radio->StartRx( );
			break;

        case RF_RX_TIMEOUT:
			break;

		default:break;
    }
}
//f_id:帧id 命令帧/回应帧
//回应帧先考虑不做，或者只有执行失败回应？1对多，空中设备同时响应，频点打架
//d_id:设备id 宏定义好
void  Lora_SendFrame(uint8_t data, uint8_t f_id ,uint8_t d_id)
{
	uint8_t Buff[10]={0};
	uint16_t check_sum;

	Buff[0]=0xEB;
	Buff[1]=0x90;
	Buff[2]=f_id;
	Buff[3]=d_id;
	Buff[4]=data;
	check_sum = RadioComputeCRC(Buff,5,CRC_TYPE_IBM);
	Buff[5] = (uint8_t)(check_sum >> 8);
	Buff[6] = (uint8_t)(check_sum & 0xFF);

	Radio->SetTxPacket(Buff,7);
}
