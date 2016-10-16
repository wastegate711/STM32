#ifndef KOMPOBMEN_H
#define KOMPOBMEN_H

#include "stm32f4xx_hal.h"

//команды включения исполнительных механизмов
#define TEST                (uint8_t)0x01 //тестовый пакет, проверка связи
#define GET_ID_DEVICE       (uint8_t)0x02 //запрос UID устройства


void CmdTest(void);  //отправляет тестовый пакет
void CmdGetUidDevice(void);  //отправляет UID устройства

#endif
