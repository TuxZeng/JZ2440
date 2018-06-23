#include <stdio.h>
#include "serial.h"
#include "lcdlib.h"
#include "s3c24xx.h"
#include "function.h"



int main()
{

    char f;
    uart0_init();   // ������115200��8N1(8������λ����У��λ��1��ֹͣλ)
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
                ClearScr(0x001f);  // ��������ɫ
                break;
            }

            case 'c':
            {
                ClearScr(0xf800);  // ��������ɫ
                break;
            }
            
            case 'd':
            {
                ClearScr(0xffff);  // ��������ɫ
                break;
            }
			
			case 'e':
            {
                ClearScr(0x0000);  // ��������ɫ
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
