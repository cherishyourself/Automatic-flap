#ifndef _I2C_H
#define _I2C_H

#include <inttypes.h>
#include "main.h"

/* 定义I2C总线连接的GPIO端口, 用户只需要修改下面4行代码即可任意改变SCL和SDA的引脚 */
//#define GPIO_PORT_PRESS	  GPIOB			            /* GPIO端口 */
//#define RCC_PRESS_PORT 	  RCC_APB2Periph_GPIOB	/* GPIO端口时钟 */
//#define PRESS_SCL_PIN		  GPIO_Pin_0			      /* 连接到SCL时钟线的GPIO */
//#define PRESS_SDA_PIN		  GPIO_Pin_1			      /* 连接到SDA数据线的GPIO */


/* 定义读写SCL和SDA的宏，增加代码的可移植性和可阅读性 */
#define PRESS_SCL_1()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET)		  /* SCL = 1 */
#define PRESS_SCL_0()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET)	/* SCL = 0 */

#define PRESS_SDA_1()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)		  /* SDA = 1 */
#define PRESS_SDA_0()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)		/* SDA = 0 */

#define PRESS_SDA_READ()  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)	/* 读SDA口线状态 */


#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */


#define PRESS_DEV_ADDR			0x28		  /* MS4525DO的设备地址（由购买时，产品的具体型号确定） */


extern float pressure_base;//用于数据初始化校准
extern float pressure;
extern float temperature;
extern void Press_GPIO_Config(void);

extern float Press_convert(void);
extern double Press_airspeed(float press);
extern float MS4525_GetSpeed(float press);

#endif


