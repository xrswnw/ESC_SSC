#include "AnyID_Rx8025.h"

BOOL Rx8025_ReadReg(u8 addr, u8 num, u8 *pBuffer)
{
    u8 i = 0;
    BOOL b = TRUE;

   if(num > 0)
   {
        //开始
        if(!Rx8025_I2CStart())
        {
            b = FALSE;
        }

        //设备地址和数据高地址
        if(b)
        {
            Rx8025_I2CSendByte(RX8025_ADDR_WRITE);
            if(!Rx8025_I2CWaitAck())
            {
                b = FALSE;
            }
        }

        //数据低地址
        if(b)
        {
            Rx8025_I2CSendByte(addr);
            b = Rx8025_I2CWaitAck();
        }


        //开始
    	if(b)
    	{
    		if(!Rx8025_I2CStart())
    		{
    			b = FALSE;
            }
    	}

        //设备地址
        if(b)
        {
            Rx8025_I2CSendByte(RX8025_ADDR_READ);
            if(!Rx8025_I2CWaitAck())
            {
                b = FALSE;
            }
        }

        	
    	if(b)
    	{
            //读出数据数据，最后一个数据要以NOACK结尾
    	    num--;	
    		for(i = 0; i < num; i++)
    		{
    			pBuffer[i] = Rx8025_I2CReceiveByte();
    			Rx8025_I2CAck();
    		}
    		pBuffer[i] = Rx8025_I2CReceiveByte();
    		Rx8025_I2CNoAck();
    	}
    	
        Rx8025_I2CStop();
    }
   return b;
}
BOOL Rx8025_WriteReg(u8 addr, u8 num, u8 *pBuffer)
{
    u8 i = 0;
    BOOL b = TRUE;

    for(i = 0; i < num; i++)
    {
        //开始
        if(!Rx8025_I2CStart())
        {
            b = FALSE;
        }

        //设备地址和数据高地址
        if(b)
        {
            Rx8025_I2CSendByte(RX8025_ADDR_WRITE);
            if(!Rx8025_I2CWaitAck())
            {
                b = FALSE;
            }
        }

        //数据低地址
        if(b)
        {
            Rx8025_I2CSendByte(addr);
            b = Rx8025_I2CWaitAck();
        }
        
        //写入数据
        for(i = 0; i < num; i++)
        {
            if(b)
            {
                Rx8025_I2CSendByte(pBuffer[i]);
                b = Rx8025_I2CWaitAck();
            }
        }

        //停止
        Rx8025_I2CStop();

        Rx8025_I2CDelay();
    }

    

    return b;
}

BOOL Rx8025_ClearRegBit(u8 addr, u8 bit)
{
    u8 reg = 0;
    BOOL b = FALSE;
    
    if(Rx8025_ReadReg(addr, 1, &reg))
    {
        reg &= (~bit);
        b = Rx8025_WriteReg(addr, 1, &reg);
    }
    
    return b;
}

BOOL Rx8025_SetRegBit(u8 addr, u8 bit)
{
    u8 reg = 0;
    BOOL b = FALSE;
    
    if(Rx8025_ReadReg(addr, 1, &reg))
    {
        reg |= bit;
        b = Rx8025_WriteReg(addr, 1, &reg);
    }
    
    return b;
}

BOOL Rx8025_MaskRegBit(u8 addr, u8 msk, u8 bit)
{
    u8 reg = 0;
    BOOL b = FALSE;
    
    if(Rx8025_ReadReg(addr, 1, &reg))
    {
        reg &= (~msk);
        
        reg |= bit;
        b = Rx8025_WriteReg(addr, 1, &reg);
    }
    
    return b;
}
