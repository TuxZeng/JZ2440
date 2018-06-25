#include "s3c24xx.h"
#include <stdio.h>
#include <string.h>
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
extern const unsigned char highletter[26][16];
extern const unsigned char lowletter[26][16];
extern const unsigned char number[11][16];
extern const unsigned char symbol[1][16];

char flag[4]={'0',0,0,0};

void start_irq()
{
	// EINT0、EINT2、EINT8_23使能
    INTMSK   &= (~(1<<0)) & (~(1<<2)) & (~(1<<5));
}

void stop_irq()
{
	// EINT0、EINT2、EINT8_23不使能
    INTMSK   |= (1<<0) | (1<<2) | (1<<5);
}

void clear()
{
	int x,y;
	char cl=0x0;
	for (y = flag[2]*16; y < (flag[2]*16+16); y++)
        for (x = 0; x < 160; x++)
            PutPixel(x, y, cl);
}

void clear_output()
{
	int x,y;
	char cl=0x0;
	for (y = 8*16; y < (8*16+16*3); y++)
        for (x = 0; x < 160; x++)
            PutPixel(x, y, cl);
}

void show_char(int x,int y,char z)
{
	char l;
	int cl=0xffff;
	int i,j;
	char shield;
	if(z>='A' && z<='Z')
	{
		l=z-'A';
		for(j=0;j<16;j++)
		{
			shield=0x80;
			for(i=0;i<8;i++)
			{
				if(highletter[l][j] & shield)
				{
					PutPixel(8*x+i,16*y+j,cl);
				}
				shield = shield>>1;
			}
		}
	}
	else if(z>='a' && z<='z')
	{
		l=z-'a';
		for(j=0;j<16;j++)
		{
			shield=0x80;
			for(i=0;i<8;i++)
			{
				if(lowletter[l][j] & shield)
				{
					PutPixel(8*x+i,16*y+j,cl);
				}
				shield = shield>>1;
			}
		}
	}
	else if(z>='0' && z<= ':')
	{
		l=z-'0';
		for(j=0;j<16;j++)
		{
			shield=0x80;
			for(i=0;i<8;i++)
			{
				if(number[l][j] & shield)
				{
					PutPixel(8*x+i,16*y+j,cl);
				}
				shield = shield>>1;
			}
		}
	}
	else
	{
		for(j=0;j<16;j++)
		{
			shield=0x80;
			for(i=0;i<8;i++)
			{
				if(symbol[0][j] & shield)
				{
					PutPixel(8*x+i,16*y+j,cl);
				}
				shield = shield>>1;
			}
		}
	}
	flag[1]=(char)x;
	flag[2]=(char)y;
}

void show_string(int y,char sentence[])
{
	int len;
	len=strlen(sentence);
	int i;
	for(i=0;i<len;i++)
	{
		show_char(i,y,sentence[i]);
	}
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
	if(flag[3] == 0)
	{
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
	else
	{
		show_string(flag[2]+1,"  Input q to exit");
		flag[2]+=1;
		char g = '0';
		while(g != 'q')
		{
			g = getc();
			clear();
			show_char(2,flag[2],g);
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
					break;
				default:
				{
					show_string(flag[2],"   Wrong selection");
					break;
				}
			}
		}
	}
	GPFDAT |= (0x7<<4);   // 所有LED熄灭
}

void key_test()
{
	if(flag[3] == 0)
	{	
		flag[0]='0';
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
	else
	{
		flag[0]='3';
		show_string(flag[2]+1,"  Input q to exit");
		flag[2]+=1;
		start_irq();
		char g = '0';
		while(g != 'q')
		{
			g = getc();
		}
		stop_irq();
	}
}

void com_test()
{
	GPFDAT |= (0x7<<4);   // 所有LED熄灭
	char g;
	int i,j;
	flag[0]='1';
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

void ascii_test()
{
	char g = '0';
	printf("Input 'q' to exit.\n\r");
	
		flag[3]=1;
		ClearScr(0x0);  // 清屏，黑色
		show_string(0,"    welcome to test    ");
		show_string(1,"  Test Function Menu:  ");
		show_string(2,"  a: LED Test");
		show_string(3,"  b: KEY Test");
		show_string(4,"  c: COM Test");
		show_string(5,"  d: LCD Test");
		show_string(6,"  q: TO EXIT ");
		show_string(7,"  Enter your selection:");
	while(g != 'q')
	{
		g = getc();
		show_char(2,8,g);
		while(g != 'a' && g != 'b' && g != 'c' && g != 'd' && g != 'q')
		{
			show_string(flag[2],"   Wrong selection ");
			g = getc();
			clear();
			show_char(2,flag[2],g);
		}
		switch (g)
		{
			case 'a':
			{
				led_test();
				clear_output();
				break;
			}
            
			case 'b':
			{
				key_test();
				clear_output();
				break;
			}
	
			case 'c':
			{
				com_test();
				break;
			}
			case 'd':
			{
				lcd_test();
				ClearScr(0x0);  // 清屏，黑色
				show_string(0,"    welcome to test    ");
				show_string(1,"  Test Function Menu:  ");
				show_string(2,"  a: LED Test");
				show_string(3,"  b: KEY Test");
				show_string(4,"  c: COM Test");
				show_string(5,"  d: LCD Test");
				show_string(6,"  q: TO EXIT ");
				show_string(7,"  Enter your selection:");
				break;
			}
			case 'q':
			{			
				flag[3]=0;
				break;
			}
			default: 
				break;
		}
	}
}
