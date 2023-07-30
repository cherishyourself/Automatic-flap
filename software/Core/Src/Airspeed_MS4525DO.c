/*
 * @Author: cherish 1771907097@qq.com
 * @Date: 2023-02-07 15:27:48
 * @LastEditors: cherish 1771907097@qq.com
 * @LastEditTime: 2023-02-17 11:19:46
 * @FilePath: \MDK-ARMd:\Avionics control\BFMA\BFMA\Code\Automatic_Flap\Core\Src\Airspeed_MS4525DO.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "press.h"
#include "stdio.h"
#include "math_Tool.h"
#include "Airspeed_MS4525DO.h"
float airspeed = 0;
float old_airspeed = 0;
void Airspeed_Init()
{
    Press_GPIO_Config();
    Press_convert();
    HAL_Delay(100);
    Press_convert();
    pressure_base = pressure; // 空速计数据初始记录
}
void Airspeed_MS4525DO()
{
	//printf("%.1f ", pressure);
    pressure = Medium_Filter(Press_convert()); // 空速计数据读取 (中值滤波)
    pressure -= pressure_base;                 // 空速计数据基于初始的数据校准
    //printf("%.1f ", pressure);

    airspeed = Press_airspeed(-1 * (pressure));
    filter(old_airspeed, airspeed,10); // 空速限幅滤波
//	if(pressure==0)
	//	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);

    old_airspeed = airspeed;
}