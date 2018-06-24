#include "s3c24xx.h"
#include <stdio.h>

void EINT_Handle()
{
    unsigned long oft = INTOFFSET;
    unsigned long val;
    
    switch( oft )
    {
        // S2������
        case 0: 
        {
			printf("KEY S2 down.\n\r");
            /*
			GPFDAT |= (0x7<<4);   // ����LEDϨ��
            GPFDAT &= ~(1<<4);      // LED1����
			*/
            break;
        }
        
        // S3������
        case 2:
        {   
			printf("KEY S3 down.\n\r");
            /*
			GPFDAT |= (0x7<<4);   // ����LEDϨ��
            GPFDAT &= ~(1<<5);      // LED2����
			*/
            break;
        }

        // K4������
        case 5:
        { 
			printf("KEY S4 down.\n\r");
			/*
            GPFDAT |= (0x7<<4);   // ����LEDϨ��
            GPFDAT &= ~(1<<6);      // LED4���� 
			*/			
            break;
        }

        default:
            break;
    }

    //���ж�
    if( oft == 5 ) 
        EINTPEND = (1<<11);   // EINT8_23����IRQ5
    SRCPND = 1<<oft;
    INTPND = 1<<oft;
}


/*
//extern void I2CIntHandle(void);

void (*isr_handle_array[50])(void);

void Dummy_isr(void)
{
    while(1);
}

void init_irq(void)
{
    int i = 0;
    for (i = 0; i < sizeof(isr_handle_array) / sizeof(isr_handle_array[0]); i++)
    {
        isr_handle_array[i] = Dummy_isr;
    }

    INTMOD = 0x0;	      // �����ж϶���ΪIRQģʽ
    INTMSK = BIT_ALLMSK;  // �����������ж�

//	isr_handle_array[ISR_IIC_OFT]  = I2CIntHandle;
}

void IRQ_Handle(void)
{
	unsigned long oft = INTOFFSET;
    
	//���ж�
	if (oft == 4)
        EINTPEND = 1<<7;    //EINT4-7����IRQ4��ע��EINTPEND[3:0]����δ�ã�����Щλд��1���ܵ���δ֪���
	SRCPND = 1<<oft;	
	INTPND = INTPND;	 
    //�����жϷ������ 
    isr_handle_array[oft]();
}

*/

