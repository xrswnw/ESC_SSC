#include "AnyID_R542_Rx8025.h"

RTC_TIME g_sRtcTime = {0x15, 0x01, 0x01, 0x04, 0x01, 0x01, 0x01, 0}; //注意BCD码
//这个参数主要根据TagTick判断当前的标签记录是否完整了，不需要根据RTC计算
//用空间换时间
u32 g_nRtcMsTick = 0;

BOOL Rx8025_Init(void)
{
    BOOL b = FALSE;
    u8 reg = 0;

    Rx8025_ReadReg(RX8025_REG_FLAG, 1, &reg);
    if(reg & RX8025_BIT_VLF)
    {
        Rx8025_SetTime(&g_sRtcTime);
    }

    //设置秒更新中断输出
    b = Rx8025_ClearRegBit(RX8025_REG_EXT, RX8025_BIT_USEL);
    if(b)
    {
        b = Rx8025_SetRegBit(RX8025_REG_CTRL, RX8025_BIT_UIE);
    }

    return b;
}
const u8 g_aRx8025WeekDay[7] = {0x40, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, };
void Rx8025_GetTime(RTC_TIME *pRtc)
{
    u8 buffer[RX8025_RTC_LEN] = {0};

    if(Rx8025_ReadReg(RX8025_REG_SECOND, RX8025_RTC_LEN, buffer))
    {
        u8 i = 0;
        pRtc->second = buffer[RX8025_REG_SECOND & 0x0F];
        pRtc->minute = buffer[RX8025_REG_MINUTE & 0x0F];
        pRtc->hour = buffer[RX8025_REG_HOUR & 0x0F];
        pRtc->week = buffer[RX8025_REG_WEEKDAY & 0x0F];
        pRtc->day = buffer[RX8025_REG_DAY & 0x0F];
        pRtc->month = buffer[RX8025_REG_MOUNTH & 0x0F];
        pRtc->year = buffer[RX8025_REG_YEAR & 0x0F];

        for(i = 0; i < 7; i++)
        {
            if(g_aRx8025WeekDay[i] == pRtc->week)
            {
                pRtc->week = i;
                break;
            }
        }
    }
}

#define RX8025_START_YEAR       0x15
void Rx8025_SetTime(RTC_TIME *pRtc)
{
    u8 buffer[RX8025_RTC_LEN] = {0};

    buffer[RX8025_REG_SECOND & 0x0F] = pRtc->second;
    buffer[RX8025_REG_MINUTE & 0x0F] = pRtc->minute;
    buffer[RX8025_REG_HOUR & 0x0F] = pRtc->hour;
    if(pRtc->week == 0)
    {
        buffer[RX8025_REG_WEEKDAY & 0x0F] = 1 << 7;
    }
    else
    {
        buffer[RX8025_REG_WEEKDAY & 0x0F] = 1 << (pRtc->week - 1);
    }
    buffer[RX8025_REG_DAY & 0x0F] = pRtc->day;
    buffer[RX8025_REG_MOUNTH & 0x0F] = pRtc->month;
    if(pRtc->year < RX8025_START_YEAR)
    {
        pRtc->year = RX8025_START_YEAR;
    }
    buffer[RX8025_REG_YEAR & 0x0F] = pRtc->year;

    Rx8025_WriteReg(RX8025_REG_SECOND, RX8025_RTC_LEN, buffer);

    Rx8025_ClearRegBit(RX8025_REG_FLAG, RX8025_BIT_VLF);
}

#define RX8025_Y_NUM            100
#define RX8025_M_NUM            12
#define RX8025_D_NUM            31

const u32 g_aRx8025HourYear[RX8025_Y_NUM] = {
     0,   8784,  17544,  26304,
 35064,  43848,  52608,  61368,
 70128,  78912,  87672,  96432,
105192, 113976, 122736, 131496,
140256, 149040, 157800, 166560,
175320, 184104, 192864, 201624,
210384, 219168, 227928, 236688,
245448, 254232, 262992, 271752,
280512, 289296, 298056, 306816,
315576, 324360, 333120, 341880,
350640, 359424, 368184, 376944,
385704, 394488, 403248, 412008,
420768, 429552, 438312, 447072,
455832, 464616, 473376, 482136,
490896, 499680, 508440, 517200,
525960, 534744, 543504, 552264,
561024, 569808, 578568, 587328,
596088, 604872, 613632, 622392,
631152, 639936, 648696, 657456,
666216, 675000, 683760, 692520,
701280, 710064, 718824, 727584,
736344, 745128, 753888, 762648,
771408, 780192, 788952, 797712,
806472, 815256, 824016, 832776,
841536, 850320, 859080, 867840
};

const u16 g_aRx8025HourMonth[RX8025_M_NUM] = {0, 744, 1416, 2160, 2880, 3624, 4344, 5088, 5832, 6552, 7296, 8016};
const u16 g_aRx8025HourDay[RX8025_D_NUM] =
{0, 24, 48, 72, 96, 120, 144, 168, 192, 216, 240, 264, 288, 312, 336, 360, 384,
408, 432, 456, 480, 504, 528, 552, 576, 600, 624, 648, 672, 696, 720};


int Rx8025_DltHour(RTC_TIME *pRtc1, RTC_TIME *pRtc2)
{
    int mi = 0;
    int y1 = 0, m1 = 0, d1 = 0, h1 = 0, mi1 = 0, sum1 = 0;
    int y2 = 0, m2 = 0, d2 = 0, h2 = 0, mi2 = 0, sum2 = 0;

    y1 = (pRtc1->year & 0x0F) + ((pRtc1->year >> 4)) * 10;
    y2 = (pRtc2->year & 0x0F) + ((pRtc2->year >> 4)) * 10;

    m1 = (pRtc1->month & 0x0F) + ((pRtc1->month >> 4)) * 10;
    m2 = (pRtc2->month & 0x0F) + ((pRtc2->month >> 4)) * 10;

    d1 = (pRtc1->day & 0x0F) + ((pRtc1->day >> 4)) * 10;
    d2 = (pRtc2->day & 0x0F) + ((pRtc2->day >> 4)) * 10;

    h1 = (pRtc1->hour & 0x0F) + ((pRtc1->hour >> 4)) * 10;
    h2 = (pRtc2->hour & 0x0F) + ((pRtc2->hour >> 4)) * 10;

    mi1 = (pRtc1->minute & 0x0F) + ((pRtc1->minute >> 4)) * 10;
    mi2 = (pRtc2->minute & 0x0F) + ((pRtc2->minute >> 4)) * 10;

    sum1 += g_aRx8025HourYear[y1];
    sum1 += g_aRx8025HourMonth[m1 - 1];
    if((y1 & 0x03) == 0x00 && m1 > 2)
    {
        sum1 += 24; //闰年闰月多加1天
    }
    sum1 += g_aRx8025HourDay[d1 - 1];
    sum1 += h1;

    sum2 += g_aRx8025HourYear[y2];
    sum2 += g_aRx8025HourMonth[m2 - 1];
    if((y2 & 0x03) == 0x00 && m2 > 2)
    {
        sum2 += 24; //闰年闰月多加1天
    }
    sum2 += g_aRx8025HourDay[d2 - 1];
    sum2 += h2;

    mi = mi1 - mi2;
    if(mi > 30)
    {
        sum1++;
    }
    else if(mi < -30)
    {
        sum2++;
    }

    return sum1 - sum2;
}


