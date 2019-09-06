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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
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
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART_SendData(USART1, USART_RX_BUF[t]);         //�򴮿�1��������
//        if(t == 2){distance = USART_RX_BUF[t+1];printf("distance is %d\n",distance);}
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//			}
      for(t=0;t<len;t++)
      {
        if((USART_RX_BUF[t] == 'd')&&(USART_RX_BUF[t+1] == 'a')&&(USART_RX_BUF[t+2] == 't'))
        {
           LED0=!LED0;                                                          //�յ�'dat'����
           distance = (USART_RX_BUF[t+3]-48)*10 + (USART_RX_BUF[t+4]-48);       //����  dat12x10y20\r\n   \r\n��ʵ����
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
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			//if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
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

