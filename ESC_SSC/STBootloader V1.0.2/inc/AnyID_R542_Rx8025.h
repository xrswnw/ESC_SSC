#ifndef _ANYID_R542_RX8025_
#define _ANYID_R542_RX8025_

#include "AnyID_Rx8025.h"

extern u32 g_nRtcMsTick;

typedef struct rtc_time{
    u8 year;
    u8 month;
    u8 day;
    u8 week;
    u8 hour;
    u8 minute;
    u8 second;
    u8 ms;
}RTC_TIME;
extern RTC_TIME g_sRtcTime;

void Rx8025_SetTime(RTC_TIME *pRtc);
void Rx8025_GetTime(RTC_TIME *pRtc);

int Rx8025_DltHour(RTC_TIME *pRtc1, RTC_TIME *pRtc2);

BOOL Rx8025_Init(void);


#endif

