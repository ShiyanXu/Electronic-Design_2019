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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
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
           x = (USART_RX_BUF[t+6]-48)*10 + (USART_RX_BUF[t+7]-48);              //      0123456789
           y = (USART_RX_BUF[t+9]-48)*10 + (USART_RX_BUF[t+10]-48);
           
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
			if(times%5000==0)
			{
				printf("\r\nALIENTEK ̽����STM32F407������ ����ʵ��\r\n");
				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
			}
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			//if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}
}

