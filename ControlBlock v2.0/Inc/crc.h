#ifndef CRC_H
#define CRC_H

#include "stm32f4xx_hal.h"

uint32_t GetCRC16(uint8_t* bufData, uint32_t sizeData);
uint16_t crc16(uint8_t *pcBlock, uint16_t len);//магическая функция считающяя 
//uint16_t GetCrc16(uint8_t *data, uint16_t sizeData);
unsigned short crc_16_rec (uint8_t *pucData, unsigned short ucLen);

#endif
