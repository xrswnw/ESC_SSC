#include "AnyID_Boot_Lora_HL.h"

#define LORA_INT_CHANNEL        UART5_IRQn

//const PORT_INF LORA_PORT_LNK = {GPIOB, GPIO_Pin_14};
const PORT_INF LORA_M0_CFG = {GPIOC, GPIO_Pin_1};
const PORT_INF LORA_M1_CFG = {GPIOC, GPIO_Pin_0};
const PORT_INF LORA_PORT_TX = {GPIOC, GPIO_Pin_12};
const PORT_INF LORA_PORT_RX = {GPIOD, GPIO_Pin_2};
const PORT_INF LORA_PORT_AUX = {GPIOB, GPIO_Pin_5};
void Lora_InitInterface(u32 baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    USART_DeInit(LORA_PORT);

    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   /* GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = LORA_M0_CFG.Pin;
    GPIO_Init(LORA_M0_CFG.Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LORA_M1_CFG.Pin;
    GPIO_Init(LORA_M1_CFG.Port, &GPIO_InitStructure);
*/

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = LORA_PORT_TX.Pin;
    GPIO_Init(LORA_PORT_TX.Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LORA_PORT_RX.Pin;
    GPIO_Init(LORA_PORT_RX.Port, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Pin = LORA_PORT_AUX.Pin;
    GPIO_Init(LORA_PORT_AUX.Port, &GPIO_InitStructure);
    
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(LORA_PORT, &USART_InitStructure);

    USART_ITConfig(LORA_PORT, USART_IT_RXNE, ENABLE);
    USART_Cmd(LORA_PORT, ENABLE);

}

void Lora_ConfigInt(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = LORA_INT_CHANNEL;

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = INT_PRIORITY_UART_RX >> 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = INT_PRIORITY_UART_RX & 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void Lora_EnableInt(FunctionalState rxState, FunctionalState txState)
{
    USART_ClearITPendingBit(LORA_PORT, USART_IT_RXNE | USART_FLAG_TXE);

    USART_ITConfig(LORA_PORT, USART_IT_RXNE, rxState);
    USART_ITConfig(LORA_PORT, USART_IT_TC, txState);
}

void Lora_WriteByte(u8 ch)
{
    while(((LORA_PORT)->SR & USART_FLAG_TXE) == (u16)RESET);
	(LORA_PORT)->DR = (ch & (u16)0x01FF);
}

void Lora_WriteBuffer(u8 *pBuffer, u32 len)
{
    u32 i = 0;
    for(i = 0; i < len; i++)
    {
        Lora_WriteByte(pBuffer[i]);
    }
}
void Lora_WriteStrings(u8 *pStr)
{
    u8 ch = 0;
    if(pStr != NULL)
    {
        while(*pStr != '\0')
        {
            ch = *pStr;
            Lora_WriteByte(ch);
            pStr++;
        }
    }

    Lora_WriteByte('\r');
    Lora_WriteByte('\n');
}

void Lora_Delayms(u32 n)
{
    n *= 0x7FFF;
    n++;
    while(n--);
}

void Lora_WriteFrame(u8 *pFrame, u16 len)
{
    u16 i = 0;
    Lora_DisableTxInt();
    Lora_Delayms(1);
    for(i = 0; i < len; i++)
    {
        Lora_WriteByte(pFrame[i]);
    }
    Lora_Delayms(1);
    Lora_EnableTxInt();
}