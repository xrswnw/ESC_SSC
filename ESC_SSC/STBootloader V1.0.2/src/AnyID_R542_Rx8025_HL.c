#include "AnyID_R542_Rx8025_HL.h"

const PORT_INF RX8025_SDA_PORT = {GPIOE, GPIO_Pin_10};
const PORT_INF RX8025_SCL_PORT = {GPIOE, GPIO_Pin_9};
const PORT_INF RX8025_IRQ_PORT = {GPIOE, GPIO_Pin_8};
void Rx8025_InitInterface(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;        
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    

    GPIO_InitStructure.GPIO_Pin = RX8025_SDA_PORT.Pin;
    GPIO_Init(RX8025_SDA_PORT.Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = RX8025_SCL_PORT.Pin;
    GPIO_Init(RX8025_SCL_PORT.Port, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                

    GPIO_InitStructure.GPIO_Pin = RX8025_IRQ_PORT.Pin;
    GPIO_Init(RX8025_IRQ_PORT.Port, &GPIO_InitStructure);
}

void Rx8025_InitExitInt(void)
{
    EXTI_InitTypeDef   EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource8); 
    
    EXTI_InitStructure.EXTI_Line = RX8025_IRQ_EXIT;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                 //中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;             //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                           //使能LINE0
    EXTI_Init(&EXTI_InitStructure);                                     //配置
    
    NVIC_InitStructure.NVIC_IRQChannel = RX8025_SCD_INT;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = INT_PRIORITY_RTC >> 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = INT_PRIORITY_RTC & 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void Rx8025_I2CDelay(void)
{
    u32 i = 0;

    i = 100;
    while(i--);
}


BOOL Rx8025_I2CStart(void)
{
    RX8025_I2C_SDA_H;
    RX8025_I2C_SCL_H;
    Rx8025_I2CDelay();
    if(!Rx8025_I2CGetSda())return FALSE;    //SDA线为低电平则总线忙,退出
    RX8025_I2C_SDA_L;
    Rx8025_I2CDelay();
    if(Rx8025_I2CGetSda()) return FALSE;    //SDA线为高电平则总线出错,退出
    RX8025_I2C_SDA_L;
    Rx8025_I2CDelay();
    return TRUE;
}

void Rx8025_I2CStop(void)
{
    RX8025_I2C_SCL_L;
    Rx8025_I2CDelay();
    RX8025_I2C_SDA_L;
    Rx8025_I2CDelay();
    RX8025_I2C_SCL_H;
    Rx8025_I2CDelay();
    RX8025_I2C_SDA_H;
    Rx8025_I2CDelay();
}

void Rx8025_I2CAck(void)
{
    RX8025_I2C_SCL_L;
    Rx8025_I2CDelay();
    RX8025_I2C_SDA_L;
    Rx8025_I2CDelay();
    RX8025_I2C_SCL_H;
    Rx8025_I2CDelay();
    RX8025_I2C_SCL_L;
    Rx8025_I2CDelay();
}

void Rx8025_I2CNoAck(void)
{
    RX8025_I2C_SCL_L;
    Rx8025_I2CDelay();
    RX8025_I2C_SDA_H;
    Rx8025_I2CDelay();
    RX8025_I2C_SCL_H;
    Rx8025_I2CDelay();
    RX8025_I2C_SCL_L;
    Rx8025_I2CDelay();
}

BOOL Rx8025_I2CWaitAck(void)      //返回为:=1有ACK,=0无ACK
{
    RX8025_I2C_SCL_L;
    Rx8025_I2CDelay();
    RX8025_I2C_SDA_H;
    Rx8025_I2CDelay();
    RX8025_I2C_SCL_H;
    Rx8025_I2CDelay();
    if(Rx8025_I2CGetSda())
    {
        RX8025_I2C_SCL_L;
        return FALSE;
    }
    RX8025_I2C_SCL_L;
    return TRUE;
}

void Rx8025_I2CSendByte(u8 SendByte) //数据从高位到低位//
{
    u8 i = 8;
    while(i--)
    {
        RX8025_I2C_SCL_L;
        Rx8025_I2CDelay();
        if(SendByte&0x80)
        {
            RX8025_I2C_SDA_H;
        }
        else
        {
            RX8025_I2C_SDA_L;
        }
        SendByte <<= 1;
        RX8025_I2C_SCL_H;
        Rx8025_I2CDelay();
    }
    RX8025_I2C_SCL_L;
}

u8 Rx8025_I2CReceiveByte(void)  //数据从高位到低位
{
    u8 i = 8;
    u8 ReceiveByte = 0;

    RX8025_I2C_SDA_H;
    while(i--)
    {
        ReceiveByte <<= 1;
        RX8025_I2C_SCL_L;
        Rx8025_I2CDelay();
        RX8025_I2C_SCL_H;
        Rx8025_I2CDelay();
        if(Rx8025_I2CGetSda())
        {
            ReceiveByte |= 0x01;
        }
    }
    RX8025_I2C_SCL_L;
    return ReceiveByte;
}

