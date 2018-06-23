#include <stdio.h>
#include "serial.h"
#include "lcdlib.h"
#include "s3c24xx.h"
#include "function.h"



int main()
{

    char f;
    uart0_init();   // 波特率115200，8N1(8个数据位，无校验位，1个停止位)
	init_led();
	
    while (1)
	{
		GPFDAT |= (0x7<<4);
		Test_Lcd_Tft_16Bit_480272();
		printf("\r\n##### Test Function Menu #####\r\n");
        printf("[a] LED test\n\r");
        printf("[b] KEY test\n\r");
        printf("[c] COM test\n\r");
        printf("[d] LCD test\n\r");
		printf("[e] NEW-FUNCTION test\n\r");
        printf("Enter your selection: ");

        f = getc();
        printf("%c\n\r", f);
        switch (f)
        {
            case 'a':
            {
				led_test();
				break;
            }
            
            case 'b':
            {
                ClearScr(0x001f);  // 清屏，绿色
                break;
            }

            case 'c':
            {
                ClearScr(0xf800);  // 清屏，蓝色
                break;
            }
            
            case 'd':
            {
                ClearScr(0xffff);  // 清屏，白色
                break;
            }
			
			case 'e':
            {
                ClearScr(0x0000);  // 清屏，黑色
                break;
            }
            
            default: 
			{
				printf("Error Selection!\n");
				break;
			}
        }
		
	}
    
    return 0;
}
