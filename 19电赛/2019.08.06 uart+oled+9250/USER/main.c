#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "oled.h"
#include "mpu9250.h"
#include "myiic.h"
#include "timer.h"



int main(void)
{ 
 
	u8 t;
	u8 len;	
	u16 times=0;  
  u16 distance = 0, x = 0, y = 0;
  extern float Pitch, Roll, Yaw;
  extern u8 TIMER3_10ms_Ticktock_FLAG;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init();		  		//初始化与LED连接的硬件接口  
  OLED_Init();
	OLED_Clear();
  TIM3_Int_Init(5000-1,8400-1);
	if(MPU9250_Init())
		printf("MPU without DMP init Failed.\r\n\r\n");
	else 
		printf("MPU withouut DMP init succeed.\r\n\r\n");	
	MPU_DMP_Init();
	while(1)
	{
//    OLED_ShowString(0,0,"Pitch");
//    OLED_ShowNum(70,0,Pitch,6);
//    OLED_ShowString(0,2,"Roll");    
//    OLED_ShowNum(70,2,Roll,6); 
//    OLED_ShowString(0,4,"Yaw");
//    OLED_ShowNum(70,4,Yaw,6);
    
    OLED_ShowString(0,0,"distance");
    OLED_ShowNum(70,0,distance,6);
    OLED_ShowString(0,2,"x");
    OLED_ShowNum(70,2,x,6);
    OLED_ShowString(0,4,"y");    
    OLED_ShowNum(70,4,y,6); 

    
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
           if(distance > 500) distance = 500;
           x = (USART_RX_BUF[t+6]-48)*10 + (USART_RX_BUF[t+7]-48);              //      0123456789
           if(x > 160 || x < 0) x = 0;
           y = (USART_RX_BUF[t+9]-48)*10 + (USART_RX_BUF[t+10]-48);
           if(y > 120 || y < 0) y = 0;
           
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
			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
			//if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
    
//    MPU_Data_Push_by_DMP();
//		if(TIMER3_10ms_Ticktock_FLAG){
//			printf("Pitch:%4.2f  ",Pitch);
//			printf("Roll:%4.2f  ",Roll);
//			printf("Yaw:%4.2f",Yaw);
//			printf("\r\n");
//			TIMER3_10ms_Ticktock_FLAG=0;
//		}
//		delay_ms(10);
	}
}

