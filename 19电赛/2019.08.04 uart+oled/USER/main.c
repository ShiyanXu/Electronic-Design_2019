#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "oled.h"



int main(void)
{ 
 
	u8 t;
	u8 len;	
	u16 times=0;  
  u16 distance, x, y;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init();		  		//初始化与LED连接的硬件接口  
  OLED_Init();
	OLED_Clear();
	while(1)
	{
    OLED_ShowString(0,0,"distance");
    OLED_ShowNum(100,0,distance,2);
    OLED_ShowString(0,2,"x");    
    OLED_ShowNum(100,2,x,2); 
    OLED_ShowString(0,4,"y");
    OLED_ShowNum(100,4,y,2); 
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART_SendData(USART1, USART_RX_BUF[t]);         //向串口1发送数据
//        if(t == 2){distance = USART_RX_BUF[t+1];printf("distance is %d\n",distance);}
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
//			}
      for(t=0;t<len;t++)
      {
        if((USART_RX_BUF[t] == 'd')&&(USART_RX_BUF[t+1] == 'a')&&(USART_RX_BUF[t+2] == 't'))
        {
           LED0=!LED0;                                                          //收到'dat'亮灯
           distance = (USART_RX_BUF[t+3]-48)*10 + (USART_RX_BUF[t+4]-48);       //输入  dat12x10y20\r\n   \r\n其实无用
           x = (USART_RX_BUF[t+6]-48)*10 + (USART_RX_BUF[t+7]-48);              //      0123456789
           y = (USART_RX_BUF[t+9]-48)*10 + (USART_RX_BUF[t+10]-48);
           
           printf("distance is %d\n", distance);
           printf("x is %d\n", x);
           printf("y is %d\n", y);
        }
      }
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nALIENTEK 探索者STM32F407开发板 串口实验\r\n");
				printf("正点原子@ALIENTEK\r\n\r\n\r\n");
			}
			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
			//if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
	}
}

