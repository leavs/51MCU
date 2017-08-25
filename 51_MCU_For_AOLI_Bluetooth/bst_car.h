#ifndef __BSTCAR_H__
#define __BSTCAR_H__
/************BST-V51智能小车头文件*************/

/*超声波*/
sbit INPUT  = P3^2;                //回声接收端口
sbit OUTPUT = P2^1;                //超声触发端口

#define VELOCITY_30C	3495       //30摄氏度时的声速，声速V= 331.5 + 0.6*温度； 
#define VELOCITY_23C	3453       //23摄氏度时的声速，声速V= 331.5 + 0.6*温度； 

//定义小车驱动模块输入IO口 
sbit IN1=P1^2;
sbit IN2=P1^3;
sbit IN3=P1^6;
sbit IN4=P1^7;
sbit EN1=P1^4;
sbit EN2=P1^5;

//定义按键
sbit K4=P3^7;

//蜂鸣器驱动口定义
sbit FM=P2^3; 

//定义点灯
sbit LED = P1^0;
sbit FIRE = P1^1;


#define Left_moto_go      {IN1=0,IN2=1;}   //左电机向前走
//#define Left_moto_back    {IN1=1,IN2=0;}   //左边电机向后转
#define Left_moto_Stop    {IN1=0,IN2=0;}         //左边电机停转    //EN1=0;   
                
#define Right_moto_go     {IN3=1,IN4=0;}   //右边电机向前走
//#define Right_moto_back   {IN3=0,IN4=1;}   //右边电机向后走
#define Right_moto_Stop   {IN3=0,IN4=0;}	       //右边电机停转  //EN2=0;
 
#define Left_moto_back      {IN1=1,IN2=0;}   //左电机向后走
#define Right_moto_back     {IN3=0,IN4=1;}   //右电机向后走



#endif