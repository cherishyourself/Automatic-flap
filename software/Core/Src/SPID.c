/*
 * @Author: cherish 1771907097@qq.com
 * @Date: 2022-09-28 17:09:01
 * @LastEditors: cherish 1771907097@qq.com
 * @LastEditTime: 2022-09-28 17:25:20
 * @FilePath: \MDK-ARMd:\Avionics control\solar power\stm32\competition\2023POWER_1\Core\Src\SPID.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "SPID.h"
#include "math_Tool.h"
#define err 7
//单级pid计算
float PID_SingleCalc(PID_t *pid,float reference,float feedback)
{
	//更新数据
	pid->lastError=pid->error;
	pid->error=reference-feedback;
	//抗闭环死区
	if(fabs((double)pid->error)>fabs((double)err)) pid->error=pid->error;
	else if(fabs((double)pid->error)<=fabs((double)err)) pid->error=0;
	//计算微分
	pid->output=(pid->error-pid->lastError)*pid->kd;
	//计算比例
	pid->output+=pid->error*pid->kp;
	//计算积分
	pid->integral+=pid->error*pid->ki;
	//积分限幅
	LIMIT(pid->integral,-pid->maxIntegral,pid->maxIntegral);
	pid->output+=pid->integral;
	//输出限幅
	return(LIMIT(pid->output,-pid->maxOutput,pid->maxOutput));

}
void PID_Init(PID_t *pid,float p,float i,float d,float maxI,float maxOut)
{
	pid->kp=p;
	pid->ki=i;
	pid->kd=d;
	pid->maxIntegral=maxI;
	pid->maxOutput=maxOut;
}