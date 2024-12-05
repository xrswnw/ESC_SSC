#ifndef _ANYID_R542_READER_
#define _ANYID_R542_READER_


#include "stdio.h"
#include "AnyID_R542_SysTick_HL.h"
#include "AnyID_R542_FRam.h"
#include "AnyID_R542_IO.h"
#define READER_VERSION_SIZE             50
extern const u8 READER_VERSION[READER_VERSION_SIZE];


#define READER_UHF_DELAY_TIME_DEAFULT       0
typedef struct flashDevicePar{
    u8 config;
    u16 addr;
    u16 crc;
}READER_DEVICE_PARAMETER;
extern READER_DEVICE_PARAMETER g_sDeviceParamenter;


void Reader_Delayms(u32 n);
void Reader_ResetDeviceParamenter(void);
BOOL Reader_WriteDeviceParamenter(void);
void Reader_ReadDeviceParamenter(void);
#endif