#include "crc.h"

#define POLYNOMIAL 0x8408

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
uint32_t GetCRC16(uint8_t *bufData, uint32_t sizeData)
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

//uint16_t GetCrc16(uint8_t *data, uint16_t sizeData)
//{
//    uint32_t TmpCRC, crc16, i;
//    uint8_t j;
//    crc16 = 0;
//    
//    for(i=0; i < sizeData; i++)
//    {
//        TmpCRC = crc16 ^ data[i];
//        for(j=0; j < 8; j++)
//        {
//            if(TmpCRC & 0x0001)
//            {
//                TmpCRC >>= 1;
//                TmpCRC ^= POLYNOMIAL;
//            }
//            else 
//            {
//                TmpCRC >>= 1;
//            }
//        }
//    }
//    return crc16;
//}
unsigned short crc_16_rec (uint8_t *pucData, unsigned short ucLen)
{
//--------------------------------------------------------------------
	unsigned int i;
	unsigned char ucBit, ucCarry;
//--------------------------------------------------------------------
	unsigned short usPoly = 0x8408;//reversed 0x1021
	unsigned short usCRC = 0;
//--------------------------------------------------------------------
	for (i = 0; i < ucLen; i++)
	{
		usCRC ^= pucData[i];
		for (ucBit = 0; ucBit < 8; ucBit++)
		{
			ucCarry = usCRC & 1;
			usCRC >>= 1;
			if (ucCarry)
			{
				usCRC ^= usPoly;
			}
		}
	}
//--------------------------------------------------------------------
	return usCRC;
//--------------------------------------------------------------------
}
