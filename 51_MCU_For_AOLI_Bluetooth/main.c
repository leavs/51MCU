/**********************�����������ݺ�����ư����յ�**************
*  ƽ̨��BST-V51  + Keil uVision2 + STC89C52RC 
*  ���ƣ������������ݺ�����ư����յ� 
*  ��д��Madi
*  ���ڣ�2016-5-10
*  ����:11.0592MHZ
*  Ӳ�����ã�����ģ��+���ⷢ��ͷ+BST-V51������ 
******************************************************************/

#include "reg52.h"	     //����52ϵͳͷ�ļ�
#include <string.h>
#include "bst_car.h"	 //����bst_car.h����С��ͷ�ļ�
#include "ir.c"			 //�������ⷢ�ͺ���

bit startBit = 0;  				//���ڽ��տ�ʼ��־λ
bit newLineReceived = 0; 		//����һ֡Э����������

unsigned char inputString[50];  //��������Э��

 /******************************************************************/
/* �����жϳ���*/
/******************************************************************/

void UART_SER () interrupt 4
{
	unsigned char n; 	//������ʱ����
	static int num = 0;
	if(RI) 		//�ж��ǽ����жϲ���
	{
		RI = 0; 	//��־λ����
		n = SBUF; //���뻺������ֵ

	    if(n == '$')
	    {
	      startBit = 1;
		  num = 0;
	    }
	    if(startBit == 1)
	    {
	       inputString[num] = n;     
	    }  
	    if (n == '#') 
	    {
	       newLineReceived = 1; 
	       startBit = 0;
	    }
		num++;
		if(num >= 50)
		{
			num = 0;
			startBit = 0;
			newLineReceived	= 0;
		}
	}
}

//�������ڳ�ʼ��
void BleInit(void)
{
   
   	SCON = 0x50; 	// SCON: ģʽ1, 8-bit UART, ʹ�ܽ���
	TMOD |= 0x20;
	TH1=0xfd; 		//������9600 ��ֵ
	TL1=0xfd;
	TR1= 1;
	EA = 1;	    	//�����ж�
	ES= 1; 			//�򿪴����ж�
}
    
//������
void main(void)
{	
	BleInit();

	while(1)	//����ѭ��
	{  		 
		if (newLineReceived)
	   	{
			switch(inputString[1])
			{
				case '0':   
					fengsu();
					break;
				case '1':   
					wenjia();
					break;
				case '2':  
					moshi();
					break;
				case '3': 
					shuimian();
					break;
				case '4':  
					wenjian();
					break;
				case '5':  
					dingshi();
					break;
				case '6':  
					baifeng();
					break;
				case '7':  
					dianyuan();
					break;
				default:
					;
					break;
			}
			
			newLineReceived = 0;  
		    memset(inputString, 0x00, sizeof(inputString));  
	    }
	}
}
   


