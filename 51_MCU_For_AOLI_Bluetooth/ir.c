#define uchar unsigned char
#define uint unsigned int 

sbit out=P1^5;					//����IO��

/* �����յ�
 *
 * �û��� 0x01
 * S13��Դ 0x39		S09ģʽ 0xB9 	S5���� 0x69 	S1��+ 0x29
 * S14˯�� 0xD9		S10��ʱ 0xF9 	S6�ڷ� 0x49 	S2��- 0xA9
 * 
 **/
const uchar TabHL1[9]={0x01,0x39,0xD9,0xB9,0xF9,0x69,0x49,0x29,0xA9};//���������&2�ֽ��û���

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

void usercode()	  				//�����û��� 00FF
{
    Send8Bit(TabHL1[0]);
	Send8Bit(~TabHL1[0]);
}

void dianyuan()					//0011 1001 - 39 ��Դ
 {
    leadcode_a();
    usercode();
    Send8Bit(TabHL1[1]);
	Send8Bit(~TabHL1[1]);
	
	leadcode_a();
    usercode();
    Send8Bit(TabHL1[1]);
	Send8Bit(~TabHL1[1]);
 }

 void shuimian()				//1101 1001 - D9 ˯��
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[2]);
	 Send8Bit(~TabHL1[2]);
	 
	 leadcode_a();
     usercode();
	 Send8Bit(TabHL1[2]);
	 Send8Bit(~TabHL1[2]);
 }

 void moshi()					//1011 1001 - B9 ģʽ
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[3]);
	 Send8Bit(~TabHL1[3]);
	 
	 leadcode_a();
     usercode();
	 Send8Bit(TabHL1[3]);
	 Send8Bit(~TabHL1[3]);
 }

 void dingshi()					//1111 1001 - F9 ��ʱ
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[4]);
	 Send8Bit(~TabHL1[4]);
	 
	 leadcode_a();
     usercode();
	 Send8Bit(TabHL1[4]);
	 Send8Bit(~TabHL1[4]);
 }

 void fengsu()					//0100 1001 - 49 ����
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[5]);
	 Send8Bit(~TabHL1[5]);
	 
	 leadcode_a();
     usercode();
	 Send8Bit(TabHL1[5]);
	 Send8Bit(~TabHL1[5]);
 }

 void baifeng()					//0110 1001 - 69 �ڷ�
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[6]);
	 Send8Bit(~TabHL1[6]);
	 
	 leadcode_a();
     usercode();
	 Send8Bit(TabHL1[6]);
	 Send8Bit(~TabHL1[6]);
 }

 void wenjia()					//0010 1001 - 29 ��+
 {
     leadcode_a();
     usercode();
	 Send8Bit(TabHL1[7]);
	 Send8Bit(~TabHL1[7]);
	 
	 leadcode_a();
     usercode();
	 Send8Bit(TabHL1[7]);
	 Send8Bit(~TabHL1[7]);
 }

 void wenjian()					//1010 1001 - A9 ��-
 {
     leadcode_a();
     usercode();
     Send8Bit(TabHL1[8]);
	 Send8Bit(~TabHL1[8]);
	 
	 leadcode_a();
     usercode();
     Send8Bit(TabHL1[8]);
	 Send8Bit(~TabHL1[8]);
 }