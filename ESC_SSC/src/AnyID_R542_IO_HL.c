#include "AnyID_R542_IO_HL.h"

const PORT_INF FMSC_DO_PORT[FMSC_IO_MAX_NUM] = 
{ 
  FMSC_IO_0, FMSC_IO_1, FMSC_IO_2, FMSC_IO_3, FMSC_IO_4, FMSC_IO_5, FMSC_IO_6, FMSC_IO_7, FMSC_IO_8, FMSC_IO_9, FMSC_IO_10, FMSC_IO_11, FMSC_IO_12, FMSC_IO_13, FMSC_IO_14, FMSC_IO_15
};

u16 g_nIOStatus = 0;

void IO_Init()
{
    u8 index = 0;
    
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;        
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    

    for(index = 0; index < FMSC_IO_MAX_NUM; index++)
    {
        GPIO_InitStructure.GPIO_Pin = FMSC_DO_PORT[index].Pin;
        GPIO_Init(FMSC_DO_PORT[index].Port, &GPIO_InitStructure);
    }
}


void IO_Delayms(u32 n)
{
    n *= 0x7FFF;
    n++;
    while(n--);
}