#include "workfunction.h"

void ValveCoolWater(GPIO_PinState newState) //Клапан холодная вода
{
    HAL_GPIO_WritePin(GPIOE, Valve_cool_water_Pin, newState);
}
/*#######################################*/
void ValveHotWater(GPIO_PinState newState) //Клапан горячая вода
{
    HAL_GPIO_WritePin(GPIOE, Valve_hot_water_Pin, newState);
}
/*#######################################*/
void ValvePena(GPIO_PinState newState) //Клапан пена
{
    HAL_GPIO_WritePin(GPIOE, Valve_pena_Pin, newState);
}
/*#######################################*/
void ValveAir(GPIO_PinState newState) //клапан воздух
{
    HAL_GPIO_WritePin(GPIOE, Valve_air_Pin, newState);
}
/*#######################################*/
void ValveNasekom(GPIO_PinState newState) //клапан насекомые
{
    HAL_GPIO_WritePin(Valve_nasekom_GPIO_Port, Valve_nasekom_Pin, newState);
}
/*#######################################*/
void ValveOsmos(GPIO_PinState newState) //клапан осмос
{
    HAL_GPIO_WritePin(Valve_osmos_GPIO_Port, Valve_osmos_Pin, newState);
}
/*#######################################*/
void ValveSbros(GPIO_PinState newState) //клапан сброса избыточного давления
{
    HAL_GPIO_WritePin(Valve_sbros_GPIO_Port, Valve_sbros_Pin, newState);
}
/*#######################################*/
void DozatorVosk(GPIO_PinState newState) //дозатор воск
{
    HAL_GPIO_WritePin(Dozator_vosk_GPIO_Port, Dozator_vosk_Pin, newState);
}
/*#######################################*/
void DozatorPena(GPIO_PinState newState) //дозатор пена
{
    HAL_GPIO_WritePin(Dozator_pena_GPIO_Port, Dozator_pena_Pin, newState);
}
/*#######################################*/
void MotorRunRght(GPIO_PinState newState) //ключение правого вращения
{
    HAL_GPIO_WritePin(Motor_run_right_GPIO_Port, Motor_run_right_Pin, newState);
}
/*#######################################*/
void MotorRunLeft(GPIO_PinState newState) //вращение мотора влево
{
    HAL_GPIO_WritePin(Motor_run_left_GPIO_Port, Motor_run_left_Pin, newState);
}
/*#######################################*/
