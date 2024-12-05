#ifndef _ANYID_R542_RX8025_HL_
#define _ANYID_R542_RX8025_HL_

#include "AnyID_Boot_Config.h"

extern const PORT_INF RX8025_SDA_PORT;
extern const PORT_INF RX8025_SCL_PORT;

#define RX8025_I2C_SCL_H            RX8025_SCL_PORT.Port->BSRRL = RX8025_SCL_PORT.Pin
#define RX8025_I2C_SCL_L            RX8025_SCL_PORT.Port->BSRRH  = RX8025_SCL_PORT.Pin

#define RX8025_I2C_SDA_H            RX8025_SDA_PORT.Port->BSRRL = RX8025_SDA_PORT.Pin
#define RX8025_I2C_SDA_L            RX8025_SDA_PORT.Port->BSRRH  = RX8025_SDA_PORT.Pin

#define Rx8025_I2CGetScl()          RX8025_SCL_PORT.Port->IDR  & RX8025_SCL_PORT.Pin
#define Rx8025_I2CGetSda()          RX8025_SDA_PORT.Port->IDR  & RX8025_SDA_PORT.Pin

#define RX8025_IRQ_EXIT                 EXTI_Line8           
#define RX8025_SCD_INT                  EXTI9_5_IRQn
#define Rx8025_ClearIntFlag()           (EXTI->PR = RX8025_IRQ_EXIT)
void Rx8025_InitExitInt(void);



void Rx8025_InitInterface(void);

void Rx8025_I2CDelay(void);

BOOL Rx8025_I2CStart(void);
void Rx8025_I2CStop(void);

void Rx8025_I2CAck(void);
void Rx8025_I2CNoAck(void);

BOOL Rx8025_I2CWaitAck(void);
u8 Rx8025_I2CReceiveByte(void);
void Rx8025_I2CSendByte(u8 SendByte);





#endif

