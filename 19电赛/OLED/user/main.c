#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "oled.h"

//�����̵�OLED�е�CE�����ֳ������ű�עΪCS�������ѽӵأ������7�����ţ���CE����ֱ�ӽ�GND����ʹ��
	
 int main(void)
 {	
	 u8 t;
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);	    	 //��ʱ������ʼ��
	uart_init(115200);

	OLED_Init();
	OLED_Clear();
	 
	OLED_ShowCHinese(0,0,0);//��
	OLED_ShowCHinese(18,0,1);//��
	OLED_ShowCHinese(36,0,2);//��
	OLED_ShowCHinese(54,0,3);//��
	OLED_ShowCHinese(72,0,4);//��
	OLED_ShowCHinese(90,0,5);//��
	OLED_ShowCHinese(0,2,6);//��
	OLED_ShowCHinese(18,2,7);//ѧ
	 
 	OLED_ShowString(0,4,"welcome to you");  

	t = 0;
 
	while(1) 
	{		
		OLED_ShowNum(0,6,t,2);   
		
		delay_ms(500);
		t++;
	}	  
	
}

