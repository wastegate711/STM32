#ifndef KOMPOBMEN_H
#define KOMPOBMEN_H

#include "stm32f4xx_hal.h"

//команды включения исполнительных механизмов
#define TEST                (uint8_t)0x01 //тестовый пакет, проверка связи
#define GET_ID_DEVICE       (uint8_t)0x02 //запрос UID устройства
#define GET_VERSION_SOFT    (uint8_t)0x03 //запрос версии ПО
#define TEST_MEHANIZM       (uint8_t)0x04 //команда на включение исполнительных механизмов


void CmdGetVersionSoft(void);    //отправляет версию ПО
void CmdTest(void);  //отправляет тестовый пакет
void CmdGetUidDevice(void);  //отправляет UID устройства
void TestMehanizm(void); //включение и выключение исполнительных механизмов

#endif
