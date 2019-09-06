#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"				//Register Definitions
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "uartstdio.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/timer.h"
#include "exti.h"
#include "tim.h"
#include "mygpio.h"
#include "mypwm.h"
#include "myuart.h"


#define delay_ms(n); SysCtlDelay(n*(SysCtlClockGet()/3000));

int flag_power = 1;
int flag0 = 0, flag1 = 1, flag2 = 1, flag3 = 0;
int status;
int TIM_stop = 0,TIM_start = 0, TIM_slow = 0, TIM_quick = 0;
uint8_t getChar;
int mode = 1;

int Getstatus(int a,int b, int c, int d)                                        //��õ�ǰ����״̬
{
  //return a*1000 + b*100 + c*10 + d*1;                                         //�ĺ���ʱ
  return a*1000 + 1*100 + 1*10 + d*1;                                           //��������������  a 1 1 d
}

int Return_mode(int a,int b,int c)
{
  if(a&&(!b)&&(!c)) return 1;
  if((!a)&&(b)&&(!c)) return 2;
  if((!a)&&(!b)&&(c)) return 3;
  return 0;
}

int main()
{ 
  GPIO_Init();
	SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);		//ϵͳʱ��16M
	PWM_Init();
  EXTI_Init();
  Myuart_Init();
  
//  while(mode == 0)
//  {}
  
/******************************************************************************************************************
��һ״̬
******************************************************************************************************************/
//while (mode == 1)
//{
//  TIMER_Init_Q1_stop();
//  UARTprintf("mode 1 begin");
//	while(mode == 1)                                                                      //���ڵ�һ��
//	{  
//     status = Getstatus(flag0, flag1, flag2, flag3);                            //��õ�ǰ����״̬����⵽���߷���1   
//                                                                                   
//     switch(status)
//     {
//       case 110:                                                                //����
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//            break;
//       case 1110:                                                               //��
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//            break;
//       case 111:                                                                //��
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
//            break;
//       default:
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//            break;
//     }
//     while((mode == 1)&&(TIM_stop == 1))
//     {
//       SetDuty(PWM1_BASE,PWM_OUT_6,0.01);
//       SetDuty(PWM1_BASE,PWM_OUT_7,0.01);
//     }
//    }
//}
    
    
    
/******************************************************************************************************************
�ڶ�״̬
******************************************************************************************************************/ 
//while(mode == 2)
//{
//   UARTprintf("mode 2 begin");
//   while(1)
//   {                                                                            //���ڵڶ���
//     status = Getstatus(flag0, flag1, flag2, flag3);
//     
//     switch(status)
//     {
//       case 110:                                                                //����
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.95);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.62);
//            break;
//       case 1110:                                                               //��
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//            break;
//       case 111:                                                                //��
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
//            break;
//       default:
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.95);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.62);
//            break;
//     }
//   }
// }

/******************************************************************************************************************
����״̬_1
******************************************************************************************************************/
//while(mode == 3)
//while(1)
//{
//    UARTprintf("mode 3 begin");
//    TIMER_Init_Q3_start();
//    
//    status = Getstatus(flag0, flag1, flag2, flag3);
//    
//    while(1)
//    {                                                                           
//      while(TIM_start == 0)                                                     //����60s����
//      {}
//        
///*****************************************************************************************************************/       
//      while((TIM_slow == 0)&&(TIM_quick == 0))
//      {
//        status = Getstatus(flag0, flag1, flag2, flag3);
//        
//        switch(status)                                                          //�������ٶ�
//        {
//          case 110:                                                             //����
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//                break;
//          case 1110:                                                            //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
//               break;
//          default:
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//               break;
//         }
//       }
//      
///*****************************************************************************************************************/ 
//      while((TIM_slow == 1)&&(TIM_quick == 0))
//      {
//        status = Getstatus(flag0, flag1, flag2, flag3);
//        
//        switch(status)                                                          //���ڿ�������
//        {
//          case 110:                                                             //����
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.1);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.05);
//                break;
//          case 1110:                                                            //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
//               break;
//          default:
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.1);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.05);
//               break;
//         }
//       }

///*****************************************************************************************************************/ 
//      while((TIM_slow == 0)&&(TIM_quick == 1))
//      {
//        status = Getstatus(flag0, flag1, flag2, flag3);
//        
//        switch(status)                                                          //����Զ�����
//        {
//          case 110:                                                             //����
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//                break;
//          case 1110:                                                            //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
//               break;
//          default:
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//               break;
//         }
//       }
//     }
//    
//   }

/******************************************************************************************************************
����״̬_2
******************************************************************************************************************/
//while(mode == 3)
//while(1)
//{
//    UARTprintf("mode 3 begin");
//    //TIMER_Init_Q3_start();
//    
//    //status = Getstatus(flag0, flag1, flag2, flag3);
//    
//    while(1)
//    {                                                                           
////      while(TIM_start == 0)                                                     //����60s����
////      {}
//      
//      int a = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3); UARTprintf("лл0000��%d",a);
//      int m = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);
//      int n = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6);
//      int o = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7);
///*****************************************************************************************************************/
//      switch (Return_mode(m,n,o)){
//        case 1:
//          
//        }
//      while(!a)
//      {
//        UARTprintf("xxxxxx:%d",Return_mode(m,n,o));
//        
//        
//        a = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);
//        //UARTprintf("лл��%d",a);
//        status = Getstatus(flag0, flag1, flag2, flag3);
//        
//        switch(status)                                                          //�������ٶ�
//        {
//          case 110:                                                             //����
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//                break;
//          case 1110:                                                            //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
//               break;
//          default:
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//               break;
//         }
//       }
      
/*****************************************************************************************************************/ 

//        status = Getstatus(flag0, flag1, flag2, flag3);
//        
//        switch(status)                                                          //���ڿ�������
//        {
//          case 110:                                                             //����
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.1);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.05);
//                break;
//          case 1110:                                                            //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
//               break;
//          default:
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.1);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.05);
//               break;
//         }


///*****************************************************************************************************************/ 
//      while((TIM_slow == 0)&&(TIM_quick == 1))
//      {
//        status = Getstatus(flag0, flag1, flag2, flag3);
//        
//        switch(status)                                                          //����Զ�����
//        {
//          case 110:                                                             //����
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//                break;
//          case 1110:                                                            //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //��
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
//               break;
//          default:
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//               break;
//         }
//       }
//     }
//    
//   }

   
   
   
   
/******************************************************************************************************************
����״̬_1
******************************************************************************************************************/     
int m = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);
int n = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6);
int o = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7);
int mno = Return_mode(m,n,o);
   
while (mno == 0)
{
  status = Getstatus(flag0, flag1, flag2, flag3);                               //��õ�ǰ����״̬����⵽���߷���1  
}
while (mno == 1)
{
  GPIO_Init_repair();
  TIMER_Init_Q1_stop();
  UARTprintf("mode 1 begin");
	while(mno == 1)                                                                      //���ڵ�һ��
	{  
     status = Getstatus(flag0, flag1, flag2, flag3);                            //��õ�ǰ����״̬����⵽���߷���1   
                                                                                   
     switch(status)
     {
       case 110:                                                                //����
            SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
            break;
       case 1110:                                                               //��
            SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
            break;
       case 111:                                                                //��
            SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
            break;
       default:
            SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
            break;
     }
     while((mode == 1)&&(TIM_stop == 1))
     {
       SetDuty(PWM1_BASE,PWM_OUT_6,0.01);
       SetDuty(PWM1_BASE,PWM_OUT_7,0.01);
     }
    }
}
while (mno == 2)
{

   UARTprintf("mode 2 begin");
   GPIO_Init_repair();
   while(1)
   {                                                                            //���ڵڶ���
     status = Getstatus(flag0, flag1, flag2, flag3);
     
     switch(status)
     {
       case 110:                                                                //����
            SetDuty(PWM1_BASE,PWM_OUT_6,0.95);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.62);
            break;
       case 1110:                                                               //��
            SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
            break;
       case 111:                                                                //��
            SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
            break;
       default:
            SetDuty(PWM1_BASE,PWM_OUT_6,0.95);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.62);
            break;
     }
    }
}


while (mno == 3)
{
    UARTprintf("mode 3 begin");
    GPIO_Init_repair();
    GPIO_Init_Q3_start();
    
    //TIMER_Init_Q3_start();
    //TIMER_Init_Q3_slow();   
    
    //status = Getstatus(flag0, flag1, flag2, flag3);
    
    while(1)
    {                                                                           
//      while(TIM_start == 0)                                                     //����60s����
//      {}
      UARTprintf("mode 3 begin");
/*****************************************************************************************************************/
      int a = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
/*****************************************************************************************************************/
        UARTprintf("mode 3 beginsssssss:%d",a);
        while(!a)
      {      
        a = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
        status = Getstatus(flag0, flag1, flag2, flag3);
        UARTprintf("mode 3 beginxxxxx");
        
        switch(status)                                                          //�������ٶ�
        {
          case 110:                                                             //����
               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
                break;
          case 1110:                                                            //��
               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
               break;
          case 111:                                                             //��
               SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
               break;
          default:
               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
               break;
         }
       }    
/*****************************************************************************************************************/ 

        status = Getstatus(flag0, flag1, flag2, flag3);
        UARTprintf("mode 3 beginqqqqqq");
        switch(status)                                                          //���ڿ�������
        {
          case 110:                                                             //����
               SetDuty(PWM1_BASE,PWM_OUT_6,0.1);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.05);
                break;
          case 1110:                                                            //��
               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
               break;
          case 111:                                                             //��
               SetDuty(PWM1_BASE,PWM_OUT_6,0.45);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.15);
               break;
          default:
               SetDuty(PWM1_BASE,PWM_OUT_6,0.1);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.05);
               break;
         }
     }
    
}
/******************************************************************************************************************
����״̬
******************************************************************************************************************/

// while(1)
//    { int a = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);
////      if(flag_power == 1)
////      {
////        SetDuty(PWM1_BASE,PWM_OUT_6,0.5);
////        SetDuty(PWM1_BASE,PWM_OUT_7,0.5);
////      }
////      else
////      {
////        SetDuty(PWM1_BASE,PWM_OUT_6,0.02);
////        SetDuty(PWM1_BASE,PWM_OUT_7,0.02);
////      }
//      
//   UARTprintf("xx:%d",a);
//    }
     
/******************************************************************************************************************
�����ǵĴ����ŵ���һ��
******************************************************************************************************************/
}
     

 



