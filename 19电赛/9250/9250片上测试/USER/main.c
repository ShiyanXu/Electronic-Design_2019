/*
Author: 
	Raii Lee 
E-mail: 
	masterraii@icloud.com
基于
	1.正点原子库函数
	2.51hei-cjxtw    http://www.51hei.com/bbs/dpj-100243-1.html
	3.shaynerain    https://shaynerain.com/九轴陀螺仪mpu9250官方dmp移植/
	4.王馨@ UESTC, 2015/03/30
	5.inv官方库文件
Platform: 
	STM32F4xx
Time: 
	03.03 2019
Version:
	V1.1
	添加了DMP库解算姿态
*/





#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "mpu9250.h"
#include "myiic.h"
#include "timer.h"

extern float Pitch, Roll, Yaw;
extern u8 TIMER3_10ms_Ticktock_FLAG;

int main(void)
{
	
	uart_init(115200);                      //初始化USART
	printf("Usart init succeeed.\r\n");
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	LED_Init();                     //初始化LED
	TIM3_Int_Init(5000-1,8400-1);
	if(MPU9250_Init())
		printf("MPU without DMP init Failed.\r\n\r\n");
	else 
		printf("MPU withouut DMP init succeed.\r\n\r\n");	
	MPU_DMP_Init();
		
	while(1){
		MPU_Data_Push_by_DMP();
		if(TIMER3_10ms_Ticktock_FLAG){
			printf("Pitch:%4.2f  ",Pitch);
			printf("Roll:%4.2f  ",Roll);
			printf("Yaw:%4.2f",Yaw);
			printf("\r\n");
			TIMER3_10ms_Ticktock_FLAG=0;
		}
		delay_ms(10);
	}
}
