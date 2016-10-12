#include "crc.h"

#define POLYNOMIAL 0x08408

uint16_t crc16(uint8_t *pcBlock, uint16_t len)//магическая функция считающяя 
{
 uint16_t crc=0xFFFF;
 uint8_t i;
 while (len--)
 {
  crc ^= *pcBlock++ << 8;
  for (i = 0; i < 8; i++)
    crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
 } 
 return crc;
}
/*###########################################*/
uint32_t GetCRC16(uint8_t* bufData, uint32_t sizeData)
{
    uint16_t crc = 0;
  int i;
  if (sizeData) do {
    crc ^= *bufData++;
    for (i=0; i<8; i++) {
      if (crc & 1) crc = (crc >> 1) ^ 0x8408;
      else crc >>= 1;
    }
  } while (--sizeData);
  
  crc=(crc<<8)+(crc>>8);
  return crc;
}
