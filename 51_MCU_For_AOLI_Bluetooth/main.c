/**********************蓝牙接收数据红外控制奥力空调**************
*  平台：BST-V51  + Keil uVision2 + STC89C52RC 
*  名称：蓝牙接收数据红外控制奥力空调 
*  编写：Madi
*  日期：2016-5-10
*  晶振:11.0592MHZ
*  硬件设置：蓝牙模块+红外发送头+BST-V51开发板 
******************************************************************/

#include "reg52.h"	     //包含52系统头文件
#include <string.h>
#include "bst_car.h"	 //包含bst_car.h智能小车头文件
#include "ir.c"			 //包含红外发送函数

bit startBit = 0;  				//串口接收开始标志位
bit newLineReceived = 0; 		//串口一帧协议包接收完成

unsigned char inputString[50];  //接收数据协议

 /******************************************************************/
/* 串口中断程序*/
/******************************************************************/

void UART_SER () interrupt 4
{
	unsigned char n; 	//定义临时变量
	static int num = 0;
	if(RI) 		//判断是接收中断产生
	{
		RI = 0; 	//标志位清零
		n = SBUF; //读入缓冲区的值

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

//蓝牙串口初始化
void BleInit(void)
{
   
   	SCON = 0x50; 	// SCON: 模式1, 8-bit UART, 使能接收
	TMOD |= 0x20;
	TH1=0xfd; 		//波特率9600 初值
	TL1=0xfd;
	TR1= 1;
	EA = 1;	    	//开总中断
	ES= 1; 			//打开串口中断
}
    
//主函数
void main(void)
{	
	BleInit();

	while(1)	//无限循环
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
   


