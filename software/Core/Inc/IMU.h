/*
 * @Author: cherish 1771907097@qq.com
 * @Date: 2023-01-30 13:09:55
 * @LastEditors: cherish 1771907097@qq.com
 * @LastEditTime: 2023-01-30 14:37:11
 * @FilePath: \MDK-ARMc:\Users\86131\Desktop\BFMA\BFMA\Code\Automatic_Flap\Core\Inc\IMU.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __IMU_H_
#define __IMU_H_
#include "main.h"

/*********************************
 * IMU���Ͷ���
 * *******************************/
enum
{
    GY25 = 1,
    GY25Z,
    JY901B
};

typedef struct
{
    int16_t GYRO[4];
    float pitch;
    float yaw;
    float roll;
} IMU_t;

#define IMU_BUF_SIZE 100
extern IMU_t IMU;
extern uint8_t IMU_Flag;
extern uint8_t IMU_BUF[IMU_BUF_SIZE];
extern uint8_t IMU_DATA[IMU_BUF_SIZE];

extern void ImuData_Decode(uint8_t imu_data[100]);
extern void vSetImuFlag(uint8_t imuflag);
#endif