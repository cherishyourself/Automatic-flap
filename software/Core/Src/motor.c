/*
 * @Author: cherish 1771907097@qq.com
 * @Date: 2023-01-30 11:12:05
 * @LastEditors: cherish 1771907097@qq.com
 * @LastEditTime: 2023-01-30 22:16:18
 * @FilePath: \MDK-ARMc:\Users\86131\Desktop\BFMA\BFMA\Code\Automatic_Flap\Core\Src\motor.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "motor.h"
#include "tim.h"
#include "stdio.h"
#include "IMU.h"
#include "math_Tool.h"
int CH1,CH2;//测试用，没有其他用途
void Servo_Control1(int CH) // left
{
   if (CH < 0)
      CH = 0;
	 

	 CH1=CH;
	 CH =((1.0 / 9.0) * CH + 5.0)*100;
   __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, (uint16_t)CH);
}
void Servo_Control2(int CH) // right
{
    if (CH < 0)
      CH = 0;
			 CH2=CH;
		CH=map(CH,0,90,90,0);
	 CH =((1.0 / 9.0) * CH + 5.0)*100;

   __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, (uint16_t)CH);
}