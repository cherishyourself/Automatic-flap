/*
 * @Author: cherish 1771907097@qq.com
 * @Date: Airspeed_Max23-01-30 17:3Airspeed_Min:02
 * @LastEditors: cherish 1771907097@qq.com
 * @LastEditTime: 2023-04-01 01:32:55
 * @FilePath: \MDK-ARMc:\Users\86131\Desktop\BFMA\BFMA\Code\Automatic_Flap\Core\Src\control.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%8Airspeed_Min%8D%E7%BD%AE
 */
#include "control.h"
#include "SPID.h"
#include "motor.h"
#include "receiver.h"
#include "tim.h"
#include "press.h"
#include "math_Tool.h"
#include "IMU.h"
#include "usart.h"
#include "Airspeed_MS4525DO.h"
PID_t roll;
float sv;                   // IMU感度设置
static float Last_Airspeed; // 上次飞机飞行速度
uint8_t Flight_State;       // 存储飞机飞行状态
uint8_t Flap_angle;         // 襟翼可以转动的最大角度
uint8_t Airspeed_Min;       // 设置降落时时襟翼打开最大时的速度
uint8_t Airspeed_Mid;       // 设置起飞时襟翼打开的最小速度，降落时襟翼打开的最大速度
uint8_t Airspeed_Max;       // 设置襟翼打开角度最大时的速度
void User_Init()
{
    Flight_State = Default;
    sv = 0.5;
    Flap_angle = 80;
    Airspeed_Min = 5;//降落打开襟翼最小临界值（即降落时到Min开始打开襟翼）
    Airspeed_Mid = 10;//起飞打开襟翼最小值（即起飞时到Mid开始打开襟翼）
    Airspeed_Max = 20;//起飞打开襟翼最大值（即起飞时到Max襟翼打开到最大）
    Last_Airspeed = 0; // 存储最新的最大值
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3); // 开启PWM功能
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    // PID_Init(&roll, 1.1, 0, 0.3, 90, 90); // 初始化PID参数
}
void User_Control()
{

    uint8_t State;
    State = cAdjustState();
    /*****************************************飞行模式**************************************************************/
    if (State == Flying)
    {
        /************************小于设定的起飞最小值（即）***********************************/
          if (Last_Airspeed < Airspeed_Mid )
          {
              Servo_Control1(0);
              Servo_Control2(0);
          }
/************************小于设定的最大值，大于设定的最小值***********************************/
          if (Last_Airspeed > Airspeed_Mid && Last_Airspeed < Airspeed_Max)
          {

              Servo_Control1(map(Last_Airspeed, Airspeed_Mid, Airspeed_Max, 0, Flap_angle) - IMU.roll * sv);
              Servo_Control2(map(Last_Airspeed, Airspeed_Mid, Airspeed_Max, 0, Flap_angle) - IMU.roll * sv);
          }
          /************************大于设定的最大值***********************************/
          else if (Last_Airspeed > Airspeed_Max || Last_Airspeed == Airspeed_Max)
          {
              if (IMU.roll > 0)
              {
                  Servo_Control1(Flap_angle - IMU.roll * sv);
                  Servo_Control2(Flap_angle - IMU.roll * sv);
              }
              else
              {
                  Servo_Control1(Flap_angle);
                  Servo_Control2(Flap_angle);
              }
          }

    }
    /*****************************************降落模式**************************************************************/
    else if (State == Landing)
    {
        //播到最低档由遥控器操控，单片机停止控制
/*
        if (airspeed > Airspeed_Mid)
        {
            Servo_Control1(0);
            Servo_Control2(0);
        }
        else if (airspeed < Airspeed_Mid && airspeed > Airspeed_Min)
        {
            Servo_Control1(Flap_angle - map(airspeed, Airspeed_Min, Airspeed_Mid, 0, Flap_angle));
            Servo_Control2(Flap_angle - map(airspeed, Airspeed_Min, Airspeed_Mid, 0, Flap_angle));
        }
        else if (airspeed < Airspeed_Min || airspeed == Airspeed_Min)
        {
            Servo_Control1(Flap_angle);
            Servo_Control2(Flap_angle);
        }
*/
    }
    /*****************************************默认模式**************************************************************/
    else if (State == Default)
    {
        Last_Airspeed = -100000;
        Servo_Control1(0);
        Servo_Control2(0);
    }

    if ((airspeed > Last_Airspeed) && (airspeed < Flap_angle))
        Last_Airspeed = airspeed;
}
