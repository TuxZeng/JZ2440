#include <stdio.h>
#include "serial.h"
#include "lcdlib.h"
#include "s3c24xx.h"

int main()
{

    
    uart0_init();   // ������115200��8N1(8������λ����У��λ��1��ֹͣλ)
	
    Test_Lcd_Tft_16Bit_480272();
	
    while (1);
    
    return 0;
}
