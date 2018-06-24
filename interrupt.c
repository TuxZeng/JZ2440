#include "s3c24xx.h"
#include <stdio.h>
#include "serial.h"
#include "framebuffer.h"

extern char flag[1];
extern const unsigned char gImage_2[261120];
extern const unsigned char gImage_3[261120];

void EINT_Handle()
{
    unsigned long oft = INTOFFSET;
    int i,j;
	
	/*
	unsigned long val;
	*/
    
    switch( oft )
    {
        // S2被按下
        case 0: 
        {
			if(flag[0] == '0')
			{
				printf("KEY S2 down.\n\r");
				for(i=0;i<100;i++)
					for(j=0;j<3600;j++);
            }
			else if(flag[0] == '1')
			{
				putc('1');
			}
			else
			{
				int i;
				int cl;
				for(i=0;i<261120;i+=2)
				{
					cl=((gImage_2[i]<<8)+gImage_2[i+1]);
					PutPixel((i%960)/2, i/960, cl);
				}
			}
			/*
			GPFDAT |= (0x7<<4);   // 所有LED熄灭
            GPFDAT &= ~(1<<4);      // LED1点亮
			*/
            break;
        }
        
        // S3被按下
        case 2:
        {   
			if(flag[0] == '0')
			{
				printf("KEY S3 down.\n\r");
				for(i=0;i<100;i++)
					for(j=0;j<3600;j++);
            }
			else if(flag[0] == '1')
			{
				putc('2');
			}
			else
			{
				int i;
				int cl;
				for(i=0;i<261120;i+=2)
				{
					cl=((gImage_3[i]<<8)+gImage_3[i+1]);
					PutPixel((i%960)/2, i/960, cl);
				}
			}
            /*
			GPFDAT |= (0x7<<4);   // 所有LED熄灭
            GPFDAT &= ~(1<<5);      // LED2点亮
			*/
            break;
        }

        // K4被按下
        case 5:
        { 
			if(flag[0] == '0')
			{
				printf("KEY S4 down.\n\r");
				for(i=0;i<100;i++)
					for(j=0;j<3600;j++);
            }
			else if(flag[0] == '1')
			{
				putc('3');
			}
			else
			{
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
			}
			/*
            GPFDAT |= (0x7<<4);   // 所有LED熄灭
            GPFDAT &= ~(1<<6);      // LED4点亮 
			*/			
            break;
        }

        default:
            break;
    }

    //清中断
    if( oft == 5 ) 
        EINTPEND = (1<<11);   // EINT8_23合用IRQ5
    SRCPND = 1<<oft;
    INTPND = 1<<oft;
}
