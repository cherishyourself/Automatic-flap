#ifndef __MATH_H_
#define __MATH_H_
#include "math.h"
#include "stm32f1xx_hal.h"
float map(float val, float I_Min, float I_Max, float O_Min, float O_Max);
/**********************************************************************************************************
*�� �� ��: LIMIT
*����˵��: ����x��������
*��    ��: x�����޺�����
*�� �� ֵ: ʵ��xֵ
**********************************************************************************************************/
#define LIMIT(x,min,max) (x)=(((x)<=(min))?(min):(((x)>=(max))?(max):(x)))

int16_t transition(int16_t x);

extern int ChartoInt(char* c);
extern int deletestr(int start,int len,char *str);
extern double Bounds_Filter(double new_value,double old_value);
extern float Medium_Filter(float input);
extern float filter(float effective_value, float new_value,float delat_max);
#endif
