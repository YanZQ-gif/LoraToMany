/*
 * THE FOLLOWING FIRMWARE IS PROVIDED: (1) "AS IS" WITH NO WARRANTY; AND 
 * (2)TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, SEMTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * 
 * Copyright (C) SEMTECH S.A.
 */
/*! 
 * \file       sx1276-Hal.c
 * \brief      SX1276 Hardware Abstraction Layer
 *
 * \version    2.0.B2 
 * \date       Nov 21 2012
 * \author     Miguel Luis
 *
 * Last modified by Miguel Luis on Jun 19 2013
 */
#include <stdint.h>
#include <stdbool.h> 
#include "stm32f1xx.h"
#include "main.h"
#include "platform.h"
#include "spi.h"

#if defined( USE_SX1276_RADIO )
#include "sx1276-Hal.h"


void SpiWriteData(uint8_t byteCount,uint8_t* pData)
{
 uint8_t i;
 
 for(i=0;i<byteCount;i++)
 {
   SpiInputOutput_Data(pData[i]);
 }
}

void SpiReadData(uint8_t byteCount,uint8_t* pData)
{
 uint8_t i;
 
 for(i=0;i<byteCount;i++)
 {
   *pData=SpiInputOutput_Data(0xff);
   pData++;
 }
}


void SX1276SetReset( uint8_t state )
{
    if( state == RADIO_RESET_ON )
    {
      // Set RESET pin to 0
      HAL_GPIO_WritePin( RF_RST_GPIO_Port, RF_RST_Pin, GPIO_PIN_RESET);
    }
    else
    {
      HAL_GPIO_WritePin( RF_RST_GPIO_Port, RF_RST_Pin, GPIO_PIN_SET);
    }
}

void SX1276Write( uint8_t addr, uint8_t data )
{
    SX1276WriteBuffer( addr, &data, 1 );
}

void SX1276Read( uint8_t addr, uint8_t *data )
{
    SX1276ReadBuffer( addr, data, 1 );
}

void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
  addr=addr|0x80;
  HAL_GPIO_WritePin( SPI1_NSS_GPIO_Port, SPI1_NSS_Pin,GPIO_PIN_RESET);//NSS = 0;
  SpiInputOutput_Data(addr);
  SpiWriteData(size,buffer);
  HAL_GPIO_WritePin( SPI1_NSS_GPIO_Port, SPI1_NSS_Pin,GPIO_PIN_SET);//NSS = 1;
}

void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )
{
   addr=addr&0x7F;
   HAL_GPIO_WritePin( SPI1_NSS_GPIO_Port, SPI1_NSS_Pin,GPIO_PIN_RESET);//NSS = 0;
   SpiInputOutput_Data(addr);
   SpiReadData(size,buffer);
   HAL_GPIO_WritePin( SPI1_NSS_GPIO_Port, SPI1_NSS_Pin,GPIO_PIN_SET);//NSS = 1;
}

void SX1276WriteFifo( uint8_t *buffer, uint8_t size )
{
    SX1276WriteBuffer( 0, buffer, size );
}

void SX1276ReadFifo( uint8_t *buffer, uint8_t size )
{
    SX1276ReadBuffer( 0, buffer, size );
}

inline uint8_t SX1276ReadDio0( void )
{
   return HAL_GPIO_ReadPin( RF_IO0_GPIO_Port, RF_IO0_Pin );
}

inline uint8_t SX1276ReadDio1( void )
{
   return HAL_GPIO_ReadPin( RF_IO1_GPIO_Port, RF_IO1_Pin );
}

inline uint8_t SX1276ReadDio2( void )
{
    //return HAL_GPIO_ReadPin( RF_DIO2_PORT, RF_DIO2_IO );
  return 0;
}

inline uint8_t SX1276ReadDio3( void )
{
   //return HAL_GPIO_ReadPin( RF_DIO3_PORT, RF_DIO3_IO );
}

inline uint8_t SX1276ReadDio4( void )
{
  return 0;
}

inline uint8_t SX1276ReadDio5( void )
{
  // return GPIO_ReadInputDataBit( RF_DIO5_PORT, RF_DIO5_IO );
  return 0;
}

inline void SX1276WriteRxTx( uint8_t txEnable )
{
    if( txEnable != 0 )
    {
       // IoePinOn( FEM_CTX_PIN );
       // IoePinOff( FEM_CPS_PIN );
    }
    else
    {
       // IoePinOff( FEM_CTX_PIN );
       // IoePinOn( FEM_CPS_PIN );
    }
}

#endif // USE_SX1276_RADIO
