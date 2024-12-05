#ifndef _ANYID_R542_LORA_HL_
#define _ANYID_R542_LORA_HL_

#include "AnyID_Boot_Config.h"

#define LORA_PORT               UART5
#define LORA_BAUDRARE           9600
#define Lora_RxIRQHandler       UART5_IRQHandler

#define LORA_DMA_CHANNEL                  DMA_Channel_4
#define LORA_DMA_STREAM                   DMA1_Stream7
#define LORA_DR_ADDRESS                   (LORA_PORT->DR)

#define LORA_DMA_STREAM_IRQ               DMA1_Stream7_IRQn
#define LORA_DMA_IT_TCIF                  DMA_IT_TCIF7
#define Lora_DMAIRQHandler                DMA1_Stream7_IRQHandler


#define Lora_TxDmaEnable(addr, size)      do{ \
                                                (LORA_DMA_STREAM)->M0AR = (u32)(addr);\
                                                ((LORA_DMA_STREAM)->NDTR = (size));\
                                                DMA_ClearITPendingBit(LORA_DMA_STREAM, LORA_DMA_IT_TCIF); \
                                                LORA_DMA_STREAM->CR |= DMA_SxCR_EN; \
                                            }while(0)

#define Lora_TxDmaDisable()               do{\
                                                DMA_ClearITPendingBit(LORA_DMA_STREAM, LORA_DMA_IT_TCIF);\
                                                LORA_DMA_STREAM->CR &= (~DMA_SxCR_EN);\
                                            }while(0)

#define Lora_EnableTxInt()      do{USART_ClearITPendingBit(LORA_PORT, USART_FLAG_TC); USART_ITConfig(LORA_PORT, USART_IT_TC, ENABLE);}while(0)
#define Lora_DisableTxInt()     do{USART_ClearITPendingBit(LORA_PORT, USART_FLAG_TC); USART_ITConfig(LORA_PORT, USART_IT_TC, DISABLE);}while(0)

#define Lora_ReadByte()       ((u16)(LORA_PORT->DR & (u16)0x01FF))
                                              
                                              
extern const PORT_INF LORA_PORT_AUX;
#define Lora_DataIdle()         ((LORA_PORT_AUX.Port->IDR & LORA_PORT_AUX.Pin) != (uint32_t)Bit_RESET)

extern const PORT_INF LORA_M0_CFG;
#define Lora_CfgM0Low()             LORA_M0_CFG.Port->BSRRL = LORA_M0_CFG.Pin
#define Lora_CfgM0High()            LORA_M0_CFG.Port->BSRRH = LORA_M0_CFG.Pin

extern const PORT_INF LORA_M1_CFG;
#define Lora_CfgM1Low()             LORA_M1_CFG.Port->BSRRL = LORA_M1_CFG.Pin
#define Lora_CfgM1High()            LORA_M1_CFG.Port->BSRRH = LORA_M1_CFG.Pin

#define Lora_EnterModeNormal()                  do{Lora_CfgM0Low(); Lora_CfgM1Low(); Lora_Delayms(2);}while(0)                 //正常工作模式    
#define Lora_EnterModeWor()                     do{Lora_CfgM0High(); Lora_CfgM1Low(); Lora_Delayms(2);}while(0)                //WOR模式
#define Lora_EnterModeCfg()                     do{Lora_CfgM0Low(); Lora_CfgM1High(); Lora_Delayms(2);}while(0)                //参数配置模式
#define Lora_EnterModeSleep()                   do{Lora_CfgM0High(); Lora_CfgM1High(); Lora_Delayms(2);}while(0)               //深度休眠模式

void Lora_InitInterface(u32 baudrate);
void Lora_ConfigDma(u8 *pTxBuffer, u32 size);
void Lora_ConfigInt(void);
void Lora_EnableInt(FunctionalState rxState, FunctionalState txState);
void Lora_WriteByte(u8 ch);
void Lora_WriteBuffer(u8 *pBuffer, u32 len);
void Lora_WriteStrings(u8 *pStr);
void Lora_WriteFrame(u8 *pFrame, u16 len);

#define Lora_ClearReg()       Lora_ReadByte()




#endif

