#include "s3c24xx.h"
#include <stdio.h>
#include "framebuffer.h"

#define	GPF4_out	(1<<(4*2))
#define	GPF5_out	(1<<(5*2))
#define	GPF6_out	(1<<(6*2))

#define	GPF4_msk	(3<<(4*2))
#define	GPF5_msk	(3<<(5*2))
#define	GPF6_msk	(3<<(6*2))


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
	ClearScr(0x001f);  // 清屏，绿色
	printf("Input 'q' to exit.\n\r");
	start_irq();
    char g = '0';
	while(g != 'q')
	{
		g = getc();
		printf("%c\n\r", g);
	}
	stop_irq();
}

