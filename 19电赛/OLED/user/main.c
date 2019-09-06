#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "oled.h"

//本例程的OLED中的CE（部分厂家引脚标注为CS）引脚已接地，如果是7线引脚，将CE引脚直接接GND即可使用
	
 int main(void)
 {	
	 u8 t;
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);	    	 //延时函数初始化
	uart_init(115200);

	OLED_Init();
	OLED_Clear();
	 
	OLED_ShowCHinese(0,0,0);//杭
	OLED_ShowCHinese(18,0,1);//州
	OLED_ShowCHinese(36,0,2);//电
	OLED_ShowCHinese(54,0,3);//子
	OLED_ShowCHinese(72,0,4);//科
	OLED_ShowCHinese(90,0,5);//技
	OLED_ShowCHinese(0,2,6);//大
	OLED_ShowCHinese(18,2,7);//学
	 
 	OLED_ShowString(0,4,"welcome to you");  

	t = 0;
 
	while(1) 
	{		
		OLED_ShowNum(0,6,t,2);   
		
		delay_ms(500);
		t++;
	}	  
	
}

