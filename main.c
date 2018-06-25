#include <stdio.h>
#include "serial.h"
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
		show_imag();
		printf("\r\n##### Test Function Menu #####\r\n");
        printf("[a] LED test\n\r");
        printf("[b] KEY test\n\r");
        printf("[c] COM test\n\r");
        printf("[d] LCD test\n\r");
		printf("[e] NEW-FUNCTION test\n\r");
        printf("Enter your selection: ");

        f = getc();
        printf("%c\n\r", f);
		while(f != 'a' && f != 'b' && f != 'c' && f != 'd' && f != 'e')
		{
			printf("Error Selection!\n");
			f = getc();
			printf("%c\n\r", f);
		}
        switch (f)
        {
            case 'a':
            {
				ClearScr(0x07e0);  // 清屏，红色
				led_test();
				break;
            }
            
            case 'b':
            {
				ClearScr(0x001f);  // 清屏，绿色
                key_test();
                break;
            }

            case 'c':
            {
				ClearScr(0xf800);  // 清屏，蓝色
                com_test();
                break;
            }
            
            case 'd':
            {
                lcd_test();
                break;
            }
			
			case 'e':
            {
				ascii_test();
                break;
            }
            
            default: 
				break;
        }
		
	}
    
    return 0;
}
