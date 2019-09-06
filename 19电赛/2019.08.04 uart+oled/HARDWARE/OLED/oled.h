#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	 

#define uchar unsigned char
#define uint unsigned char
		    						  
//-----------------OLED�˿ڶ���---------------- 
//�����̽���RST-F0��DC-F1��SDA��MOSI�����ߣ�-F2��SCL��CLKʱ���ߣ�-F3
//���ʹ���������ţ����Լ��޸���ЩIO�ĺ궨��
//�ǵ��޸�IO�ĳ�ʼ������
#define RST_L GPIO_ResetBits(GPIOF,GPIO_Pin_0)
#define RST_H GPIO_SetBits(GPIOF,GPIO_Pin_0)

#define DC_L GPIO_ResetBits(GPIOF,GPIO_Pin_1)
#define DC_H GPIO_SetBits(GPIOF,GPIO_Pin_1)

#define SDA_L GPIO_ResetBits(GPIOF,GPIO_Pin_2)
#define SDA_H GPIO_SetBits(GPIOF,GPIO_Pin_2)

#define SCL_L GPIO_ResetBits(GPIOF,GPIO_Pin_3)
#define SCL_H GPIO_SetBits(GPIOF,GPIO_Pin_3)
 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define Max_Column	128

void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len);
void OLED_ShowString(u8 x,u8 y, u8 *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
u32 oled_pow(u8 m,u8 n);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);

#endif  
	 



