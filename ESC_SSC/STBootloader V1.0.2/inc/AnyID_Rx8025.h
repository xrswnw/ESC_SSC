#ifndef _ANYID_RX8025_
#define _ANYID_RX8025_


#if defined(_ANYID_R542_)
    #include "AnyID_R542_Rx8025_HL.h"
#endif

#define RX8025_REG_SECOND           0x10
#define RX8025_REG_MINUTE           0x11
#define RX8025_REG_HOUR             0x12
#define RX8025_REG_WEEKDAY          0x13
#define RX8025_REG_DAY              0x14
#define RX8025_REG_MOUNTH           0x15
#define RX8025_REG_YEAR             0x16

#define RX8025_REG_AW_MINUTE        0x18
#define RX8025_REG_AW_HOUR          0x19
#define RX8025_REG_AW_WEEKDAY       0x1A

#define RX8025_REG_TIMER0           0x1B
#define RX8025_REG_TIMER1           0x1C

#define RX8025_REG_EXT              0x1D
#define RX8025_REG_FLAG             0x1E
#define RX8025_REG_CTRL             0x1F

#define RX8025_REG_RAM              0x20
#define RX8025_RAM_LEN              0x10

#define RX8025_REG_IRQ              0x32

#define RX8025_ADDR_READ            0x65
#define RX8025_ADDR_WRITE           0x64

#define RX8025_MSK_FSEL             0xC0
#define RX8025_BIT_USEL             0x20
#define RX8025_BIT_TE               0x10
#define RX8025_BIT_WADA             0x08
#define RX8025_MSK_TSEL             0x07

#define RX8025_BIT_UF               0x20
#define RX8025_BIT_TF               0x10
#define RX8025_BIT_AF               0x08
#define RX8025_BIT_VLF              0x02

#define RX8025_BIT_UIE              0x20
#define RX8025_BIT_TIF              0x10
#define RX8025_BIT_AIE              0x08
#define RX8025_BIT_TSTP             0x04

#define RX8025_BIT_TMPIN            0x04
#define RX8025_MSK_FOPIN            0x03

#define RX8025_BITS_FOPIN1          0x01
#define RX8025_BITS_FOPIN2          0x00

#define RX8025_BITS_FOOFF           0x00
#define RX8025_BITS_FO1HZ           0x40
#define RX8025_BITS_FO1KHZ          0x80
#define RX8025_BITS_FOERR           0xC0

#define RX8025_RTC_LEN              7

BOOL Rx8025_ReadReg(u8 addr, u8 num, u8 *pBuffer);
BOOL Rx8025_WriteReg(u8 addr, u8 num, u8 *pBuffer);

BOOL Rx8025_ClearRegBit(u8 addr, u8 bit);
BOOL Rx8025_SetRegBit(u8 addr, u8 bit);
BOOL Rx8025_MaskRegBit(u8 addr, u8 msk, u8 bit);

#endif
