/*
Author: 
	Raii Lee 
E-mail: 
	masterraii@icloud.com
����
	1.����ԭ�ӿ⺯��
	2.51hei-cjxtw    http://www.51hei.com/bbs/dpj-100243-1.html
	3.shaynerain    https://shaynerain.com/����������mpu9250�ٷ�dmp��ֲ/
	4.��ܰ@ UESTC, 2015/03/30
	5.inv�ٷ����ļ�
Platform: 
	STM32F4xx
Time: 
	03.03 2019
Version:
	V1.1
	�����DMP�������̬
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
	
	uart_init(115200);                      //��ʼ��USART
	printf("Usart init succeeed.\r\n");
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	LED_Init();                     //��ʼ��LED
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
