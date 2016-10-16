#include "kompobmen.h"
#include "crc.h"
#include "usart.h"
#include "flash.h"

extern uint8_t txDataUsart2[255];

uint8_t addrMaster = 0xFE; //адрес мастера
uint8_t addrSlave = 0x01; //адрес ведомого
uint16_t getCrc16 = 0; //принимает контрольную сумму массива
uint32_t UID_devisePart1 = 0;
uint32_t UID_devisePart2 = 0;
uint32_t UID_devisePart3 = 0;

void CmdTest(void)  //отправляет тестовый пакет
{
    txDataUsart2[0] = addrMaster;
    txDataUsart2[1] = addrSlave;
    txDataUsart2[2] = TEST;
    txDataUsart2[3] = 0x06;
    
    getCrc16 = crc16(txDataUsart2, txDataUsart2[3]);
    
    txDataUsart2[4] = getCrc16 >> 8;
    txDataUsart2[5] = getCrc16;
    
    ChipSelectUsart2(GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_UART_Transmit_IT(&huart2, txDataUsart2, 6);
    //HAL_UART_Transmit(&huart2, txDataUsart2, 6, 100);
    HAL_Delay(10);
    ChipSelectUsart2(GPIO_PIN_RESET);
}
/*########################################*/
void CmdGetUidDevice(void)  //отправляет UID устройства
{
    UID_devisePart1 = ReadAdresFlash(0x1FFF7A10);
    UID_devisePart2 = ReadAdresFlash(0x1FFF7A14);
    UID_devisePart3 = ReadAdresFlash(0x1FFF7A18);
    
    txDataUsart2[0] = addrMaster;
    txDataUsart2[1] = addrSlave;
    txDataUsart2[2] = GET_ID_DEVICE;
    txDataUsart2[3] = 0x12;
    txDataUsart2[4] = UID_devisePart1 >> 24;
    txDataUsart2[5] = UID_devisePart1 >> 16;
    txDataUsart2[6] = UID_devisePart1 >> 8;
    txDataUsart2[7] = UID_devisePart1;
    txDataUsart2[8] = UID_devisePart2 >> 24;
    txDataUsart2[9] = UID_devisePart2 >> 16;
    txDataUsart2[10] = UID_devisePart2 >> 8;
    txDataUsart2[11] = UID_devisePart2;
    txDataUsart2[12] = UID_devisePart3 >> 24;
    txDataUsart2[13] = UID_devisePart3 >> 16;
    txDataUsart2[14] = UID_devisePart3 >> 8;
    txDataUsart2[15] = UID_devisePart3;
    getCrc16 = crc16(txDataUsart2, txDataUsart2[3]);
    txDataUsart2[16] = getCrc16 >> 8;
    txDataUsart2[17] = getCrc16;
    
    ChipSelectUsart2(GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_UART_Transmit_IT(&huart2, txDataUsart2, 18);
    HAL_Delay(10);
    ChipSelectUsart2(GPIO_PIN_RESET);
}
/*########################################*/
/*########################################*/
/*########################################*/
/*########################################*/
/*########################################*/
/*########################################*/
