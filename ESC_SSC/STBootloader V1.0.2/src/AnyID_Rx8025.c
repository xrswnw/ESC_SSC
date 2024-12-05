#include "AnyID_Rx8025.h"

BOOL Rx8025_ReadReg(u8 addr, u8 num, u8 *pBuffer)
{
    u8 i = 0;
    BOOL b = TRUE;

   if(num > 0)
   {
        //��ʼ
        if(!Rx8025_I2CStart())
        {
            b = FALSE;
        }

        //�豸��ַ�����ݸߵ�ַ
        if(b)
        {
            Rx8025_I2CSendByte(RX8025_ADDR_WRITE);
            if(!Rx8025_I2CWaitAck())
            {
                b = FALSE;
            }
        }

        //���ݵ͵�ַ
        if(b)
        {
            Rx8025_I2CSendByte(addr);
            b = Rx8025_I2CWaitAck();
        }


        //��ʼ
    	if(b)
    	{
    		if(!Rx8025_I2CStart())
    		{
    			b = FALSE;
            }
    	}

        //�豸��ַ
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
            //�����������ݣ����һ������Ҫ��NOACK��β
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
        //��ʼ
        if(!Rx8025_I2CStart())
        {
            b = FALSE;
        }

        //�豸��ַ�����ݸߵ�ַ
        if(b)
        {
            Rx8025_I2CSendByte(RX8025_ADDR_WRITE);
            if(!Rx8025_I2CWaitAck())
            {
                b = FALSE;
            }
        }

        //���ݵ͵�ַ
        if(b)
        {
            Rx8025_I2CSendByte(addr);
            b = Rx8025_I2CWaitAck();
        }
        
        //д������
        for(i = 0; i < num; i++)
        {
            if(b)
            {
                Rx8025_I2CSendByte(pBuffer[i]);
                b = Rx8025_I2CWaitAck();
            }
        }

        //ֹͣ
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
