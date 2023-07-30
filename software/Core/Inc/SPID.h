/*
 * @Author: cherish 1771907097@qq.com
 * @Date: 2022-09-28 17:07:21
 * @LastEditors: cherish 1771907097@qq.com
 * @LastEditTime: 2022-10-18 15:42:20
 * @FilePath: \MDK-ARMd:\Avionics control\solar power\stm32\competition\2023POWER_1\Core\Inc\SPID.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __SPID_H_
#define __SPID_H_
typedef struct 
{
	float kp,ki,kd;
	float error,lastError;
	float integral,maxIntegral;
	float output,maxOutput;
}PID_t;
extern float PID_SingleCalc(PID_t *pid,float reference,float feedback);
extern void PID_Init(PID_t *pid,float p,float i,float d,float maxI,float maxOut);
#endif