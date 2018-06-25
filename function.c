#include "s3c24xx.h"
#include <stdio.h>
#include "function.h"
#include "lcd.h"

#define	GPF4_out	(1<<(4*2))
#define	GPF5_out	(1<<(5*2))
#define	GPF6_out	(1<<(6*2))

#define	GPF4_msk	(3<<(4*2))
#define	GPF5_msk	(3<<(5*2))
#define	GPF6_msk	(3<<(6*2))

extern const unsigned char gImage_1[261120];
extern const unsigned char gImage_2[261120];
extern const unsigned char gImage_3[261120];

char flag[1]={'0'};

void stop_irq()
{
	// EINT0、EINT2、EINT8_23不使能
    INTMSK   |= (1<<0) | (1<<2) | (1<<5);
}

void start_irq()
{
	// EINT0、EINT2、EINT8_23使能
    INTMSK   &= (~(1<<0)) & (~(1<<2)) & (~(1<<5));
}

void init_led()
{
	GPFCON &= ~(GPF4_msk | GPF5_msk | GPF6_msk);
	GPFCON |= GPF4_out | GPF5_out | GPF6_out;
}

void show_imag()
{
    Lcd_Port_Init();                     // 设置LCD引脚
	printf("\n.....Initializing GPIO ports.....\n");
    Tft_Lcd_Init(); // 初始化LCD控制器
    Lcd_PowerEnable(0, 1);               // 设置LCD_PWREN有效，它用于打开LCD的电源
    Lcd_EnvidOnOff(1);                   // 使能LCD控制器输出信号

    ClearScr(0x0);  // 清屏，黑色
	
	int i;
	int cl;
	for(i=0;i<261120;i+=2)
	{
		cl=((gImage_1[i]<<8)+gImage_1[i+1]);
		PutPixel((i%960)/2, i/960, cl);
	}			
    //Lcd_EnvidOnOff(0);
}

void led_test()
{
	ClearScr(0x07e0);  // 清屏，红色
	printf("Input 'q' to exit.\n\r");
    char g = '0';
	while(g != 'q')
	{
		g = getc();
		printf("%c", g);
		switch(g)
		{
			case '0':
			{
				GPFDAT |= (0x7<<4);
				break;
			}
			case '1':
			{
				GPFDAT |= (0x7<<4);   // 所有LED熄灭
				GPFDAT &= ~(1<<4);      // LED1点亮
				break;
			}
			case '2':
			{
				GPFDAT |= (0x7<<4);   // 所有LED熄灭
				GPFDAT &= ~(1<<5);      // LED2点亮
				break;	
			}
			case '3':
			{
				GPFDAT |= (0x7<<4);   // 所有LED熄灭
				GPFDAT &= ~(1<<4);   	// LED1点亮
				GPFDAT &= ~(1<<5);      // LED2点亮
				break;
			}
			case '4':
			{
				GPFDAT |= (0x7<<4);   // 所有LED熄灭
				GPFDAT &= ~(1<<6);      // LED4点亮                
				break;
			}
			case '5':
			{
				GPFDAT |= (0x7<<4);   // 所有LED熄灭
				GPFDAT &= ~(1<<4);   	// LED1点亮
				GPFDAT &= ~(1<<6);      // LED4点亮
				break;
			}
			case '6':
			{
				GPFDAT |= (0x7<<4);   // 所有LED熄灭
				GPFDAT &= ~(1<<5);   	// LED2点亮
				GPFDAT &= ~(1<<6);      // LED4点亮
				break;
			}
			case '7':
			{
				GPFDAT |= (0x7<<4);   // 所有LED熄灭
				GPFDAT &= ~(1<<4);   	// LED1点亮
				GPFDAT &= ~(1<<5);   	// LED2点亮
				GPFDAT &= ~(1<<6);      // LED4点亮
				break;
			}
			case 'q':
				printf("\n\r");
				break;
			default:
			{
				printf("\n\rWrong Input!\n");
				break;
			}
		}
	}
}

void key_test()
{
	flag[0]='0';
	ClearScr(0x001f);  // 清屏，绿色
	printf("Input 'q' to exit.\n\r");
	start_irq();
    char g = '0';
	while(g != 'q')
	{
		g = getc();
		if(g == 'q')
			printf("%c\n\r", g);
	}
	stop_irq();
}

void com_test()
{
	GPFDAT |= (0x7<<4);   // 所有LED熄灭
	char g;
	int i,j;
	ClearScr(0xf800);  // 清屏，蓝色
	flag[0]='1';
	printf("Input 'q' to exit.\n\r");
	start_irq();
	while(1)
	{
		g = getc();
		switch(g)
		{
			case '1':
			{
				GPFDAT |= (0x7<<4);   // 所有LED熄灭
				GPFDAT &= ~(1<<4);      // LED1点亮
				for(i=0;i<100;i++)
					for(j=0;j<1000;j++);
				break;
			}
			
			case '2':
			{   
				GPFDAT |= (0x7<<4);   // 所有LED熄灭
				GPFDAT &= ~(1<<5);      // LED2点亮
				for(i=0;i<100;i++)
					for(j=0;j<1000;j++);
				break;
			}
			
			case '3':
			{   
				GPFDAT |= (0x7<<4);   // 所有LED熄灭
				GPFDAT &= ~(1<<6);      // LED4点亮
				for(i=0;i<100;i++)
					for(j=0;j<1000;j++);                
				break;
			}

			default:
				break;
		}
	}
	stop_irq();
}

void lcd_test()
{
	Lcd_Port_Init();                     // 设置LCD引脚
	printf("\n.....Initializing GPIO ports.....\n");
    Tft_Lcd_Init(); // 初始化LCD控制器
    Lcd_PowerEnable(0, 1);               // 设置LCD_PWREN有效，它用于打开LCD的电源
    Lcd_EnvidOnOff(1);                   // 使能LCD控制器输出信号

    ClearScr(0x0);  // 清屏，黑色
	flag[0]='2';
	start_irq();
	printf("Input 'q' to exit.\n\r");
	char g = '0';
	int i=0;
	int cl,x,y;
	for(i=0;i<261120;i+=4)
	{
		cl=((gImage_2[i]<<8)+gImage_2[i+1]);
		PutPixel((i%960)/2, i/960, cl);
	}
	for(i=2;i<261120;i+=4)
	{
		cl=((gImage_3[i]<<8)+gImage_3[i+1]);
		PutPixel((i%960)/2, i/960, cl);
	}
	while(g != 'q')
	{
		g = getc();
		if(g == 'q')
			printf("%c\n\r", g);
	}
	stop_irq();
}

