#ifndef __RECEIVER_H_
#define __RECEIVER_H_
#include "main.h"

enum
{
    Default,
    Flying,
    Landing
};

extern uint32_t capture_Buf_FLY[3];
extern uint8_t capture_Cnt_FLY;
extern int32_t high_time_FLY;			
extern uint32_t capture_Buf_LAND[3]; 
extern uint8_t capture_Cnt_LAND ;	   
extern int32_t high_time_LAND;		
void capture(void);
uint8_t cAdjustState(void);

#endif