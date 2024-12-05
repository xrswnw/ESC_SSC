#ifndef _ANYID_R542_IO_HL_
#define _ANYID_R542_IO_HL_

#include "AnyID_R542_Config.h"

#define FMSC_IO_MAX_NUM         16

#define  FMSC_IO_0              {GPIOD, GPIO_Pin_14}
#define  FMSC_IO_1              {GPIOD, GPIO_Pin_15}
#define  FMSC_IO_2              {GPIOD, GPIO_Pin_0}
#define  FMSC_IO_3              {GPIOD, GPIO_Pin_1}
#define  FMSC_IO_4              {GPIOE, GPIO_Pin_7}
#define  FMSC_IO_5              {GPIOE, GPIO_Pin_8}
#define  FMSC_IO_6              {GPIOE, GPIO_Pin_9}
#define  FMSC_IO_7              {GPIOE, GPIO_Pin_10}
#define  FMSC_IO_8              {GPIOE, GPIO_Pin_11}
#define  FMSC_IO_9              {GPIOE, GPIO_Pin_12}
#define  FMSC_IO_10             {GPIOE, GPIO_Pin_13}
#define  FMSC_IO_11             {GPIOE, GPIO_Pin_14}
#define  FMSC_IO_12             {GPIOE, GPIO_Pin_15}
#define  FMSC_IO_13             {GPIOD, GPIO_Pin_8}
#define  FMSC_IO_14             {GPIOD, GPIO_Pin_9}
#define  FMSC_IO_15             {GPIOD, GPIO_Pin_10}


extern const PORT_INF FMSC_DO_PORT[FMSC_IO_MAX_NUM];
extern u16 g_nIOStatus;
#define IO_CtrOutHigh(i)         do{FMSC_DO_PORT[i].Port->BSRRL = FMSC_DO_PORT[i].Pin; g_nIOStatus |= (1 << i);}while(0)
#define IO_CtrOutLow(i)          do{FMSC_DO_PORT[i].Port->BSRRH = FMSC_DO_PORT[i].Pin; g_nIOStatus &= ~(1 << i);}while(0)

void IO_Init();
void IO_Delayms(u32 n);
#endif

