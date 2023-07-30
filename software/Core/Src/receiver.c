/*
 * @Author: cherish 1771907097@qq.com
 * @Date: 2023-03-11 02:16:32
 * @LastEditors: cherish 1771907097@qq.com
 * @LastEditTime: 2023-04-01 01:33:47
 * @FilePath: \MDK-ARMc:\Users\86131\Desktop\Automatic_Flap\Core\Src\receiver.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "receiver.h"
#include "usart.h"
#include "tim.h"
#include "control.h"
#include "stdio.h"

/*****************飞行模式********************************/
uint32_t capture_Buf_FLY[3] = {0}; // 存放计数值
uint8_t capture_Cnt_FLY = 0;	   // 状态标志位
int32_t high_time_FLY;			   // 高电平时间
static uint32_t high_time_FLY_old; // 高电平时间
/*****************降落模式********************************/
uint32_t capture_Buf_LAND[3] = {0}; // 存放计数值
uint8_t capture_Cnt_LAND = 0;		// 状态标志位
int32_t high_time_LAND;				// 高电平时间
static int32_t high_time_LAND_old;	// 高电平时间

/**********************************************************************************************************
 *函 数 名: capture
 *功能说明: 获取接收机特定通道的数据
 *形    参: 无
 *返 回 值: 无
 **********************************************************************************************************/
void capture()
{

	/**************************************飞行模式**************************************/
	switch (capture_Cnt_FLY)
	{
	case 0:
		capture_Cnt_FLY++;
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
		HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1); // 启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
		break;
	case 3:
		high_time_FLY = capture_Buf_FLY[1] - capture_Buf_FLY[0]; // 高电平时间
		HAL_Delay(10);											 // 延时1S
		capture_Cnt_FLY = 0;									 // 清空标志位
		break;
	}
	/**************************************降落模式**************************************/
	switch (capture_Cnt_LAND)
	{
	case 0:
		capture_Cnt_LAND++;
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
		HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2); // 启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
		break;
	case 3:
		high_time_LAND = capture_Buf_LAND[1] - capture_Buf_LAND[0]; // 高电平时间
		HAL_Delay(10);												// 延时1S
		capture_Cnt_LAND = 0;										// 清空标志位
		break;
	}
}
/**********************************************************************************************************
 *函 数 名: cAdjustState
 *功能说明: 判断操作
 *形    参: 无
 *返 回 值: 无
 **********************************************************************************************************/
uint8_t cAdjustState()
{
	if (high_time_FLY < 0) // 防抖操作，防止因为外面因素导致产生负数
		return -10;
	if (high_time_FLY < 0 || high_time_FLY > 4000)
		return 0;
	// printf("1:%d ",high_time_F00//LY);

	if (high_time_FLY > 800 && high_time_FLY < 1400)
		Flight_State = Default;
	else if ((high_time_FLY > 1400 && high_time_FLY < 1800))
		Flight_State = Flying;
	else if (high_time_FLY > 1800 && high_time_FLY < 2500)
		Flight_State = Landing;
	// printf("1:%d\r",Flight_State);

	/*if (high_time_FLY > 1000 && high_time_FLY < 1400)
		Flight_State = Flying;
	else if ((high_time_FLY > 1400 && high_time_FLY < 1800)||(high_time_LAND > 1400 && high_time_LAND < 1800))
		Flight_State = Default;
	else if (high_time_LAND > 1800 && high_time_LAND < 2200)
		Flight_State = Landing;
	*/

	return Flight_State;
}
