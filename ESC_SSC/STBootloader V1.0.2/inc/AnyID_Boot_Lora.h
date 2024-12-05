#ifndef _ANYID_R542_LORA_
#define _ANYID_R542_LORA_

#include "AnyID_Boot_Lora_HL.h"

#include "AnyID_Uart_Receive.h"

extern UART_RCVFRAME g_sLoraRcvFrame;


#define LORA_MODE_DTU           0x00                //透传模式
#define LORA_MODE_AIM           0x01                //定点模式

#define LORA_ADDR_DEFULET       0x00

#define LORA_AIRRATE_2400       0x00

typedef struct loraParams{
    u8 mode;
    u8 addr;
    u8 airRate;
    u8 channel;
    u8 pwr;
    u16 rfu1;
    u16 rfu2;
}LORA_PARAMS;



#define LORA_INFO_STAT_LORA_BUSY           0x00
#define LORA_INFO_STAT_LORA_LOADING        0x01
#define LORA_INFO_STAT_LORA_IDLE           0x02

#define Lora_Idle()           (g_sLoraInfo.sate == LORA_INFO_STAT_LORA_IDLE)
typedef struct loraInfo{
    u8 aux;
    u8 sate; 
    u8 romTime;
    u32 busyTick;
}LORA_INFO;

extern LORA_INFO g_sLoraInfo;
#endif

