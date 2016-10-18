#include "kompobmen.h"
#include "crc.h"
#include "usart.h"
#include "flash.h"
#include "workfunction.h"

extern uint8_t txDataUsart2[255];
extern uint8_t rxDataUsart2[255];

char versionSoftvare[] = {"2.0"};   //версия ПО
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
    
    getCrc16 = crc16(txDataUsart2, 4);
    
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
    getCrc16 = crc16(txDataUsart2, 16);
    txDataUsart2[16] = getCrc16 >> 8;
    txDataUsart2[17] = getCrc16;
    
    ChipSelectUsart2(GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_UART_Transmit_IT(&huart2, txDataUsart2, 18);
    HAL_Delay(10);
    ChipSelectUsart2(GPIO_PIN_RESET);
}
/*########################################*/
void CmdGetVersionSoft(void)    //отправляет версию ПО
{
    txDataUsart2[0] = addrMaster;
    txDataUsart2[1] = addrSlave;
    txDataUsart2[2] = GET_VERSION_SOFT;
    txDataUsart2[3] = 0x09;
    txDataUsart2[4] = versionSoftvare[0];
    txDataUsart2[5] = versionSoftvare[1];
    txDataUsart2[6] = versionSoftvare[2];
    getCrc16 = crc16(txDataUsart2, 7);
    txDataUsart2[7] = getCrc16 >> 8;
    txDataUsart2[8] = getCrc16;
    
    ChipSelectUsart2(GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_UART_Transmit_IT(&huart2, txDataUsart2, 9);
    HAL_Delay(10);
    ChipSelectUsart2(GPIO_PIN_RESET);
}
/*########################################*/
void TestMehanizm(void) //включение и выключение исполнительных механизмов
{
    switch(rxDataUsart2[4])
    {
        case 0x01: //клапан воздух
            if(rxDataUsart2[5] == 0)
            {
                ValveAir(GPIO_PIN_RESET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x01;
                txDataUsart2[5] = 0x00;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            else
            {
                ValveAir(GPIO_PIN_SET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x01;
                txDataUsart2[5] = 0x01;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            break;
        case 0x02: //клапан насекомые
            if(rxDataUsart2[5] == 0)
            {
                ValveNasekom(GPIO_PIN_RESET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x02;
                txDataUsart2[5] = 0x00;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            else
            {
                ValveNasekom(GPIO_PIN_SET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x02;
                txDataUsart2[5] = 0x01;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            break;
        case 0x03: //клапан горячая вода
            if(rxDataUsart2[5] == 0)
            {
                ValveHotWater(GPIO_PIN_RESET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x03;
                txDataUsart2[5] = 0x00;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            else
            {
                ValveHotWater(GPIO_PIN_SET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x03;
                txDataUsart2[5] = 0x01;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            break;
        case 0x04: //клапан холодная вода
            if(rxDataUsart2[5] == 0)
            {
                ValveCoolWater(GPIO_PIN_RESET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x04;
                txDataUsart2[5] = 0x00;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            else
            {
                ValveCoolWater(GPIO_PIN_SET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x04;
                txDataUsart2[5] = 0x01;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            break;
        case 0x05: //клапан осмос
            if(rxDataUsart2[5] == 0)
            {
                ValveOsmos(GPIO_PIN_RESET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x05;
                txDataUsart2[5] = 0x00;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            else
            {
                ValveOsmos(GPIO_PIN_SET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x05;
                txDataUsart2[5] = 0x01;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            break;
        case 0x06: //клапан пена
            if(rxDataUsart2[5] == 0)
            {
                ValvePena(GPIO_PIN_RESET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x06;
                txDataUsart2[5] = 0x00;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            else
            {
                ValvePena(GPIO_PIN_SET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x06;
                txDataUsart2[5] = 0x01;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            break;
        case 0x07: //клапан сброс
            if(rxDataUsart2[5] == 0)
            {
                ValveSbros(GPIO_PIN_RESET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x07;
                txDataUsart2[5] = 0x00;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            else
            {
                ValveSbros(GPIO_PIN_SET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x07;
                txDataUsart2[5] = 0x01;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            break;
        case 0x08: //дозатор воск
            if(rxDataUsart2[5] == 0)
            {
                DozatorVosk(GPIO_PIN_RESET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x08;
                txDataUsart2[5] = 0x00;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            else
            {
                DozatorVosk(GPIO_PIN_SET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x08;
                txDataUsart2[5] = 0x01;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            break;
        case 0x09: //дозатор пена
            if(rxDataUsart2[5] == 0)
            {
                DozatorPena(GPIO_PIN_RESET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x09;
                txDataUsart2[5] = 0x00;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            else
            {
                DozatorPena(GPIO_PIN_SET);
                
                txDataUsart2[0] = addrMaster;
                txDataUsart2[1] = addrSlave;
                txDataUsart2[2] = TEST_MEHANIZM;
                txDataUsart2[3] = 0x06;
                txDataUsart2[4] = 0x09;
                txDataUsart2[5] = 0x01;
                getCrc16 = crc16(txDataUsart2, 6);
                txDataUsart2[6] = getCrc16 >> 8;
                txDataUsart2[7] = getCrc16;
            }
            break;
    }
    
    ChipSelectUsart2(GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_UART_Transmit_IT(&huart2, txDataUsart2, 8);
    HAL_Delay(10);
    ChipSelectUsart2(GPIO_PIN_RESET);
}
/*########################################*/
/*########################################*/
/*########################################*/
/*########################################*/
