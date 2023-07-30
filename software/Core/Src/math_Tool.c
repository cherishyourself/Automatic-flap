/*
 * @Author: cherish 1771907097@qq.com
 * @Date: 2023-02-07 11:51:39
 * @LastEditors: cherish 1771907097@qq.com
 * @LastEditTime: 2023-02-07 12:39:53
 * @FilePath: \MDK-ARMc:\Users\86131\Desktop\Automatic_Flap\Core\Src\math_Tool.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: cherish 1771907097@qq.com
 * @Date: 2022-09-28 17:13:01
 * @LastEditors: cherish 1771907097@qq.com
 * @LastEditTime: 2023-02-06 14:11:49
 * @FilePath: \MDK-ARMd:\Avionics control\solar power\stm32\competition\2023POWER_1\Core\Src\math_Tool.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "math_Tool.h"
#include "string.h"

/***********************************************************************************
 *函 数 名: map
 *功能说明: 定义域的映射
 *形    参: 对象 对象最小值 对象最大值 目标最小值 目标最大值
 *返 回 值: 映射之后的范围
 **********************************************************************************************************/
float map(float val, float I_Min, float I_Max, float O_Min, float O_Max)
{
	return (((val - I_Min) * ((O_Max - O_Min) / (I_Max - I_Min))) + O_Min);
}
/*****************
   取绝对值
****************/

int Abs(int val)
{
	return val > 0 ? val : -val;
}
/**********************************************************************************************************
 *函 数 名: transition
 *功能说明: 角度转对于PWM
 *形    参: 角度值
 *返 回 值: 转化后的PWM值
 **********************************************************************************************************/
int16_t transition(int16_t x)
{
	return ((x / 9 + 5) * 100);
}
/**********************************************************************************************************
 *函 数 名: ChartoInt
 *功能说明: 字符串数组转整数
 *形    参: 数组
 *返 回 值: 转化后的整数
 **********************************************************************************************************/
int ChartoInt(char *c)
{
	char t;
	int num = 0;
	int len = sizeof(c) / 2;
	char d[sizeof(c) / 2] = {0};
	for (int i = 0, j = 0; j < sizeof(c); i++, j += 2)
		d[i] = (c[j] << 4) | c[j + 1];
	for (int i = 0, j = len - 1; i < len / 2; i++, j--)
		t = d[i], d[i] = d[j], d[j] = t;
	strncpy((char *)&num, d, len);
	return num;
}
/**********************************************************************************************************
*函 数 名: deletestr
*功能说明: start：字符串下标
		   deletestr函数：从str[start]开始删除长度为len的字符串
*形    参: 字符串下标 删除的长度 数组
*返 回 值: 1
**********************************************************************************************************/
int deletestr(int start, int len, char *str)
{
	int length = strlen(str);
	if (start > length || start < 0)
		return 0;
	int i;
	for (i = start + len; i < length; i++)
	{
		str[i - len] = str[i];
	}
	str[i - len] = '\0';
	return 1;
}

/**********************************************************************************************************
 *函 数 名: Medium_Filter
 *功能说明: 中值滤波
 *形    参: input 输入参数 n为窗口大小
 *返 回 值: 滤波结果
 **********************************************************************************************************/
float Medium_Filter(float input)
{
	const uint8_t n=15;
	/* 输入的缓冲区 */
	static float x[n] = {0};

	/* 输入的缓冲区更新 */
	for (uint8_t i = n - 1; i > 0; i--)
	{
		x[i] = x[i - 1];
	}
	x[0] = input;

	/* 输入缓冲区拷贝，排序会被打乱顺序 */
	float x_copy[n] = {0};
	memcpy(x_copy, x, sizeof(float) * n);

	/* 升序冒泡排序 */
	for (uint8_t j = 0; j < n - 1; j++)
	{
		for (uint8_t i = 0; i < n - j - 1; i++)
		{
			/* ÉýÐòÅÅÐò */
			if (x_copy[i] > x_copy[i + 1])
			{
				float temp = x_copy[i];
				x_copy[i] = x_copy[i + 1];
				x_copy[i + 1] = temp;
			}
		}
	}

	/* 窗口大小为偶数个 */
	if (n % 2 == 0)
	{
		return (x_copy[n / 2] + x_copy[n / 2 - 1]) / 2.0f;
	}
	/* 窗口大小为奇数个 */
	else
	{
		return x_copy[(n - 1) / 2];
	}
}

/**********************************************************************************************************
 *函 数 名: filter
 *功能说明: 限幅滤波
 *形    参: 上次值 实际值 滑窗
 *返 回 值: 滤波结果
 **********************************************************************************************************/
float filter(float effective_value, float new_value,float delat_max)
{
	if ((new_value - effective_value > delat_max) || (effective_value - new_value > delat_max))
		return effective_value;
	return new_value;
}