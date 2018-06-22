#include <stdio.h>
#include "serial.h"
#include "lcdlib.h"
#include "s3c24xx.h"

int main()
{

    
    uart0_init();   // 波特率115200，8N1(8个数据位，无校验位，1个停止位)
	
    Test_Lcd_Tft_16Bit_480272();
	
    while (1);
    
    return 0;
}
