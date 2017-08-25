#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int 

sbit out=P1^5;						//����IO��

void delay(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)				//i=xms����ʱԼxms����
		for(j=112;j>0;j--);
}

void delay560us(void)				//560us�ӳٺ���			
{
	uint j;
	for(j=63;j>0;j--);
}

void delay4500us(void)				//4.5ms�ӳٺ���	
{
  	uint j;
	for(j=516;j>0;j--);
}

void khz_2(uint num)				//38KHZ���� ռ�ձ�1:2
{
    for(;num>0;num--)
	  out=~out;	
} 

void send0_a(void)					//����0
{  
   khz_2(42);
   out=1;
   delay560us();
}

void send1_a(void)					//����1
{  
   khz_2(42) ;
   out=1;
   delay560us();
   delay560us();
   delay560us();
}

void leadcode_a(void)				//����������
{
    khz_2(690) ;
	out=1;
   	delay4500us();

}

void Send8Bit(uchar d)			  	//����һ�ֽ�����
{
    if(d&0x80){	send1_a();}
	else{		send0_a();}
	if(d&0x40){	send1_a();}
	else{		send0_a();}
	if(d&0x20){	send1_a();}
	else{		send0_a();}
	if(d&0x10){	send1_a();}
	else{		send0_a();}
	if(d&0x08){	send1_a();}
	else{		send0_a();}
	if(d&0x04){	send1_a();}
	else{		send0_a();}
	if(d&0x02){	send1_a();}
	else{		send0_a();}
	if(d&0x01){	send1_a();}
	else{		send0_a();}
}

//����ҡ����
//const uchar TabHL1[12]={0x30,0x18,0x7a,0x10,0x38,0x5a,0x42,0x4a,0x52,0x00,0xff,0xa6};//���������1-9&2�ֽ��û���

/* �����յ�
 *
 * �û��� 0x01
 * S13��Դ 0x39		S09ģʽ 0xB9 	S5���� 0x69 	S1��+ 0x29
 * S14˯�� 0xD9		S10��ʱ 0xF9 	S6�ڷ� 0x49 	S2��- 0xA9
 * 
 **/
const uchar TabHL1[9]={0x01,0x39,0xD9,0xB9,0xF9,0x69,0x49,0x29,0xA9};//���������&2�ֽ��û���

void usercode()	  					//�����û��� 00FF
{
    Send8Bit(TabHL1[0]);
	Send8Bit(~TabHL1[0]);
}

void xuexiban_13()					//0011 1001 - 39 ��Դ
 {
    leadcode_a();
    usercode();
    Send8Bit(TabHL1[1]);
	Send8Bit(~TabHL1[1]);
 }

 void xuexiban_14()					//1101 1001 - D9 ˯��
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[2]);
	 Send8Bit(~TabHL1[2]);
 }

 void xuexiban_9()					//1011 1001 - B9 ģʽ
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[3]);
	 Send8Bit(~TabHL1[3]);
 }

 void xuexiban_10()					//1111 1001 - F9 ��ʱ
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[4]);
	 Send8Bit(~TabHL1[4]);
 }

 void xuexiban_5()					//0100 1001 - 49 ����
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[5]);
	 Send8Bit(~TabHL1[5]);
 }

 void xuexiban_6()					//0110 1001 - 69 �ڷ�
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[6]);
	 Send8Bit(~TabHL1[6]);
 }

 void xuexiban_1()					//0010 1001 - 29 ��+
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[7]);
	 Send8Bit(~TabHL1[7]);
 }

 void xuexiban_2()					//1010 1001 - A9 ��-
 {
     leadcode_a();
     usercode();
     Send8Bit(TabHL1[8]);
	 Send8Bit(~TabHL1[8]);
 }		
	  

void keyscan()				 		//����ɨ�躯��
{
	uchar temp;
	P3=0xf0;
	temp=P3;
    temp=temp&0xf0;
	if(temp!=0xf0){
    
		P3=0xfe;
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
		  delay(10);
		  temp=P3;
		  temp=temp&0xf0;
		  if(temp!=0xf0)
		  {
			temp=P3;
			switch(temp)
			{
			  case 0xee:
				   xuexiban_1();
				   xuexiban_1();			   
				   break;
			  case 0xde:
				   xuexiban_2();
				   xuexiban_2();
				   break;
			  //case 0xbe:
			  //     xuexiban_3();
			  //     break;
			  //case 0x7e:
			  //     xuexiban_4();
			  //     break;
			 }
			 while(temp!=0xf0)
			{ 
			   temp=P3;
			   temp=temp&0xf0;
			}
		  }
		}
		P3=0xfd;
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
		  delay(10);
		  temp=P3;
		  temp=temp&0xf0;
		  if(temp!=0xf0)
		  {
			temp=P3;
			switch(temp)
			{
			  case 0xed:
				   xuexiban_5();
				   xuexiban_5();
				   break;
			  case 0xdd:
				   xuexiban_6();
				   xuexiban_6();
				   break;
			  // case 0xbd:
				   // xuexiban_7();
				   // break;
			  // case 0x7d:
				   // xuexiban_8();
				   // break;
			}
			 while(temp!=0xf0)
			{
			   temp=P3;
			   temp=temp&0xf0; 
			}
		  }
		}
		P3=0xfb;
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
		  delay(10);
		  temp=P3;
		  temp=temp&0xf0;
		  if(temp!=0xf0)
		  {
			temp=P3;
			switch(temp)
			{
			  case 0xeb:
				   xuexiban_9();
				   xuexiban_9();
				   break;
			  case 0xdb:
				   xuexiban_10();
				   xuexiban_10();
				   break;
			  // case 0xbb:
				   // xuexiban_11();
				   // xuexiban_11();
				   // break;
			  // case 0x7b:
				   // xuexiban_12();
				   // xuexiban_12();
				   // break;
			}

			 while(temp!=0xf0)
			{
			   temp=P3;
			   temp=temp&0xf0;
			}
		  }
		}
		P3=0xf7;
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
		  delay(10);
		  temp=P3;
		  temp=temp&0xf0;
		  if(temp!=0xf0)
		  {
			temp=P3;
			switch(temp)
			{
			  case 0xe7:
				   xuexiban_13();
				   xuexiban_13();
				   break;
			  case 0xd7:
				   xuexiban_14();
				   xuexiban_14();
				   break;
			  // case 0xb7:
				   // xuexiban_15();
				   // xuexiban_15();
				   // break;
			  // case 0x77:
				   // xuexiban_16();
				   // xuexiban_16();
				   // break;
			}

			 while(temp!=0xf0)
			{
			   temp=P3;
			   temp=temp&0xf0;
			}
		  }
		}
	}
}	

void main(void)
{
   while(1)
       keyscan();
}