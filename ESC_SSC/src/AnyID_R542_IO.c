#include "AnyID_R542_IO.h"

void IO_Test()
{
    u8 index = 0;
    
    for(index = 0; index < FMSC_IO_MAX_NUM; index++)
    {
        IO_CtrOutHigh(index);
        IO_Delayms(100);
    }

    for(index = 0; index < FMSC_IO_MAX_NUM; index++)
    {
        IO_CtrOutLow(index);
        IO_Delayms(100);
    }
}

