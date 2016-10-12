#ifndef WORKFUNCTION_H
#define WORKFUNCTION_H

#include "stm32f4xx_hal.h"

void ValveCoolWater(GPIO_PinState newState); //Клапан холодная вода
void ValveHotWater(GPIO_PinState newState); //Клапан горячая вода
void ValvePena(GPIO_PinState newState); //Клапан пена
void ValveAir(GPIO_PinState newState); //клапан воздух
void ValveNasekom(GPIO_PinState newState); //клапан насекомые
void ValveOsmos(GPIO_PinState newState); //клапан осмос
void ValveSbros(GPIO_PinState newState); //клапан сброса избыточного давления
void DozatorVosk(GPIO_PinState newState); //дозатор воск
void DozatorPena(GPIO_PinState newState); //дозатор пена
void MotorRunRght(GPIO_PinState newState); //ключение правого вращения
void MotorRunLeft(GPIO_PinState newState); //вращение мотора влево

#endif
