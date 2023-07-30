/*
 * @Author: cherish 1771907097@qq.com
 * @Date: 2023-01-30 13:10:03
 * @LastEditors: cherish 1771907097@qq.com
 * @LastEditTime: 2023-02-06 11:30:46
 * @FilePath: \MDK-ARMc:\Users\86131\Desktop\BFMA\BFMA\Code\Automatic_Flap\Core\Src\IMU.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "IMU.h"
#include "stdio.h"
IMU_t IMU;
uint8_t IMU_Flag;
uint8_t JY_LEN =10;
uint8_t IMU_BUF[IMU_BUF_SIZE];
uint8_t IMU_DATA[IMU_BUF_SIZE];
static void vJY901B_Decode(uint8_t* DATA);
static void vGY25Z_Decode(uint8_t *DATA);
static void vGY25_Decode(uint8_t *DATA);
/**********************************************************************************************************
*函 数 名: jy901b_encode
*功能说明: 解析jy901b
*形    参: 无
*返 回 值: 无
***********************************************************************************************************/
void vJY901B_Decode(uint8_t* DATA)
{

	int i;
	for(i=0;i<IMU_BUF_SIZE;i++)
	{
	if(DATA[i]==0x55&&DATA[i+1]==0x53)
	{
		IMU.roll  = (float)((DATA[i+3]<<8)|DATA[i+2])/32768*180;
				IMU.pitch = (float)((DATA[i+5]<<8)|DATA[i+4])/32768*180;
				IMU.yaw   = (float)((DATA[i+7]<<8)|DATA[i+6]/32768*180);
				if(IMU.roll>180) IMU.roll-=360;
				if(IMU.pitch>180) IMU.pitch-=360;
				if(IMU.yaw>180) IMU.yaw-=360;
		//实际需要取反。根据情况定。我是发现陀螺仪抬头是负的
		IMU.roll=IMU.roll*-1;
	}
}
	}

/**********************************************************************************************************
*函 数 名: vGY25_Decode
*功能说明: 解析GY25数据
*形    参: 缓存区
*返 回 值: 状态
**********************************************************************************************************/
void vGY25_Decode(uint8_t *DATA)
{
int i=0;
while(DATA[i++]==0xaa&&DATA[i+6]==0x55)
{
	IMU.pitch   = ((DATA[i+2] << 8) | DATA[i+3])/100;
  IMU.yaw = ((DATA[i+4] << 8) | DATA[i+5])/100;
  IMU.roll= ((DATA[i] << 8) |DATA[i+1])/100;
	if(IMU.roll>180) IMU.roll-=655;
	IMU.roll=-IMU.roll;
	if(IMU.pitch>180) IMU.pitch-=655;
	if(IMU.yaw>180) IMU.yaw-=655;
}
}

/**********************************************************************************************************
*函 数 名: vGY25Z_Decode
*功能说明: 解析GY25Z数据
*形    参: 缓存区
*返 回 值: 状态
**********************************************************************************************************/
void vGY25Z_Decode(uint8_t *DATA)
{

int i=0;
while(DATA[i++]==0x5A)
{
	if(DATA[i]==0x5A)
	{  
		int j;
		for(j=i;j<15;j++)
		{if(DATA[j]==0x5A&&DATA[j+1]==0x5A) break;}

		IMU.roll =((DATA[i+3] << 8) | DATA[i+4])/100;
		IMU.pitch=((DATA[i+5] << 8) | DATA[i+6])/100;
		IMU.yaw=((DATA[i+7] << 8) | DATA[i+8])/100;
		if(IMU.roll>180) IMU.roll-=655;
		IMU.roll=-IMU.roll;
		if(IMU.pitch>180) IMU.pitch-=655;
		if(IMU.yaw>180) IMU.yaw-=655;
	}
}
}
/**********************************************************************************************************
*函 数 名: ImuData_Decode
*功能说明: 选择IMU当前类型并解析
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void ImuData_Decode(uint8_t imu_data[100])
{
//选择当前的传感器类型
if(IMU_Flag==GY25) vGY25_Decode(imu_data);
else if(IMU_Flag==GY25Z) vGY25Z_Decode(imu_data);
else if(IMU_Flag==JY901B) vJY901B_Decode(imu_data);
//printf("%d %d %d\r\n",imucurrent.pitch,imucurrent.roll,imucurrent.yaw);
}	
/**********************************************************************************************************
*函 数 名: vSetImuFlag
*功能说明: 设置IMU类型
*形    参: 缓存区
*返 回 值: 状态
**********************************************************************************************************/
void vSetImuFlag(uint8_t imuflag)
{
IMU_Flag=imuflag;
}
