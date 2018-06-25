#include "s3c24xx.h"
#include <stdio.h>
#include "serial.h"
#include "function.h"
#include "lcd.h"

extern char flag[4];
extern const unsigned char gImage_2[261120];
extern const unsigned char gImage_3[261120];

void EINT_Handle()
{
    unsigned long oft = INTOFFSET;
    int i,j;
    
    switch( oft )
    {
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
			else if(flag[0] == '2')
			{
				int i;
				int cl;
				for(i=0;i<261120;i+=2)
				{
					cl=((gImage_2[i]<<8)+gImage_2[i+1]);
					PutPixel((i%960)/2, i/960, cl);
				}
			} 
			else
			{
				clear();
				show_string(flag[2],"  KEY S2 down");
				for(i=0;i<100;i++)
					for(j=0;j<3600;j++);
			}
            break;
        }
        
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
			else if(flag[0] == '2')
			{
				int i;
				int cl;
				for(i=0;i<261120;i+=2)
				{
					cl=((gImage_3[i]<<8)+gImage_3[i+1]);
					PutPixel((i%960)/2, i/960, cl);
				}
			} 
			else
			{
				clear();
				show_string(flag[2],"  KEY S3 down");
				for(i=0;i<100;i++)
					for(j=0;j<3600;j++);
			}
            break;
        }

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
			else if(flag[0] == '2')
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
			else
			{
				clear();
				show_string(flag[2],"  KEY S4 down");
				for(i=0;i<100;i++)
					for(j=0;j<3600;j++);
			}		
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
