#ifndef __BSTCAR_H__
#define __BSTCAR_H__
/************BST-V51����С��ͷ�ļ�*************/

/*������*/
sbit INPUT  = P3^2;                //�������ն˿�
sbit OUTPUT = P2^1;                //���������˿�

#define VELOCITY_30C	3495       //30���϶�ʱ�����٣�����V= 331.5 + 0.6*�¶ȣ� 
#define VELOCITY_23C	3453       //23���϶�ʱ�����٣�����V= 331.5 + 0.6*�¶ȣ� 

//����С������ģ������IO�� 
sbit IN1=P1^2;
sbit IN2=P1^3;
sbit IN3=P1^6;
sbit IN4=P1^7;
sbit EN1=P1^4;
sbit EN2=P1^5;

//���尴��
sbit K4=P3^7;

//�����������ڶ���
sbit FM=P2^3; 

//������
sbit LED = P1^0;
sbit FIRE = P1^1;


#define Left_moto_go      {IN1=0,IN2=1;}   //������ǰ��
//#define Left_moto_back    {IN1=1,IN2=0;}   //��ߵ�����ת
#define Left_moto_Stop    {IN1=0,IN2=0;}         //��ߵ��ͣת    //EN1=0;   
                
#define Right_moto_go     {IN3=1,IN4=0;}   //�ұߵ����ǰ��
//#define Right_moto_back   {IN3=0,IN4=1;}   //�ұߵ�������
#define Right_moto_Stop   {IN3=0,IN4=0;}	       //�ұߵ��ͣת  //EN2=0;
 
#define Left_moto_back      {IN1=1,IN2=0;}   //���������
#define Right_moto_back     {IN3=0,IN4=1;}   //�ҵ�������



#endif