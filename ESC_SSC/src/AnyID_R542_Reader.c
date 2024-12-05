#include "AnyID_R542_Reader.h"

const u8 READER_VERSION[READER_VERSION_SIZE]@0x08005000 = "D543FNX 24091101 D543-MB-SCH-230701";

READER_DEVICE_PARAMETER g_sDeviceParamenter = {0};  
void Reader_Delayms(u32 n)
{
    n *= 0x7FFF;
    n++;
    while(n--);
}


void Reader_ResetDeviceParamenter(void)
{
    memset(&g_sDeviceParamenter, 0, sizeof(g_sDeviceParamenter));
}

BOOL Reader_WriteDeviceParamenter(void)
{
    g_sDeviceParamenter.crc = a_GetCrc((u8 *)(&g_sDeviceParamenter), sizeof(g_sDeviceParamenter) - 2);
    return FRam_WriteBuffer(FRAME_INFO_ADDR, sizeof(g_sDeviceParamenter), (u8 *)(&g_sDeviceParamenter));
}

void Reader_ReadDeviceParamenter(void)
{
    BOOL b = FALSE;
    if(FRam_ReadBuffer(FRAME_INFO_ADDR, sizeof(g_sDeviceParamenter), (u8 *)(&g_sDeviceParamenter)))
    {
        u16 crc = 0;

        crc = a_GetCrc((u8 *)(&g_sDeviceParamenter), sizeof(g_sDeviceParamenter) - 2);
        if(crc == g_sDeviceParamenter.crc)
        {
            b = TRUE;
        }
    }
    
    if(!b)
    {
        Reader_ResetDeviceParamenter();
        Reader_WriteDeviceParamenter();
    }

    
    Fram_ReadBootParamenter();
    if((g_sFramBootParamenter.appState != FRAM_BOOT_APP_OK) ||
       (g_sFramBootParamenter.br != FRAM_BOOT_BAUDRATE115200) ||
       (g_sFramBootParamenter.addr != g_sDeviceParamenter.addr))
    {
        g_sFramBootParamenter.appState = FRAM_BOOT_APP_OK;
        g_sFramBootParamenter.br = FRAM_BOOT_BAUDRATE115200;
        g_sFramBootParamenter.addr = g_sDeviceParamenter.addr;
        Fram_WriteBootParamenter();
        Fram_WriteBackupBootParamenter();
    }
}