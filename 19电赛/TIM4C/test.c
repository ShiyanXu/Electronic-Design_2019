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

int Getstatus(int a,int b, int c, int d)                                        //获得当前红外状态
{
  //return a*1000 + b*100 + c*10 + d*1;                                         //四红外时
  return a*1000 + 1*100 + 1*10 + d*1;                                           //仅考虑两个红外  a 1 1 d
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
	SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);		//系统时钟16M
	PWM_Init();
  EXTI_Init();
  Myuart_Init();
  
//  while(mode == 0)
//  {}
  
/******************************************************************************************************************
第一状态
******************************************************************************************************************/
//while (mode == 1)
//{
//  TIMER_Init_Q1_stop();
//  UARTprintf("mode 1 begin");
//	while(mode == 1)                                                                      //用于第一题
//	{  
//     status = Getstatus(flag0, flag1, flag2, flag3);                            //获得当前红外状态，检测到黑线返回1   
//                                                                                   
//     switch(status)
//     {
//       case 110:                                                                //理想
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//            break;
//       case 1110:                                                               //右
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//            break;
//       case 111:                                                                //左
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
第二状态
******************************************************************************************************************/ 
//while(mode == 2)
//{
//   UARTprintf("mode 2 begin");
//   while(1)
//   {                                                                            //用于第二题
//     status = Getstatus(flag0, flag1, flag2, flag3);
//     
//     switch(status)
//     {
//       case 110:                                                                //理想
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.95);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.62);
//            break;
//       case 1110:                                                               //右
//            SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//            SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//            break;
//       case 111:                                                                //左
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
第三状态_1
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
//      while(TIM_start == 0)                                                     //用于60s启动
//      {}
//        
///*****************************************************************************************************************/       
//      while((TIM_slow == 0)&&(TIM_quick == 0))
//      {
//        status = Getstatus(flag0, flag1, flag2, flag3);
//        
//        switch(status)                                                          //用于起步速度
//        {
//          case 110:                                                             //理想
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//                break;
//          case 1110:                                                            //右
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //左
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
//        switch(status)                                                          //用于靠近减速
//        {
//          case 110:                                                             //理想
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.1);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.05);
//                break;
//          case 1110:                                                            //右
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //左
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
//        switch(status)                                                          //用于远离加速
//        {
//          case 110:                                                             //理想
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//                break;
//          case 1110:                                                            //右
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //左
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
第三状态_2
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
////      while(TIM_start == 0)                                                     //用于60s启动
////      {}
//      
//      int a = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3); UARTprintf("谢谢0000：%d",a);
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
//        //UARTprintf("谢谢：%d",a);
//        status = Getstatus(flag0, flag1, flag2, flag3);
//        
//        switch(status)                                                          //用于起步速度
//        {
//          case 110:                                                             //理想
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//                break;
//          case 1110:                                                            //右
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //左
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
//        switch(status)                                                          //用于靠近减速
//        {
//          case 110:                                                             //理想
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.1);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.05);
//                break;
//          case 1110:                                                            //右
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //左
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
//        switch(status)                                                          //用于远离加速
//        {
//          case 110:                                                             //理想
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
//                break;
//          case 1110:                                                            //右
//               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
//               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
//               break;
//          case 111:                                                             //左
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
最终状态_1
******************************************************************************************************************/     
int m = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);
int n = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6);
int o = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7);
int mno = Return_mode(m,n,o);
   
while (mno == 0)
{
  status = Getstatus(flag0, flag1, flag2, flag3);                               //获得当前红外状态，检测到黑线返回1  
}
while (mno == 1)
{
  GPIO_Init_repair();
  TIMER_Init_Q1_stop();
  UARTprintf("mode 1 begin");
	while(mno == 1)                                                                      //用于第一题
	{  
     status = Getstatus(flag0, flag1, flag2, flag3);                            //获得当前红外状态，检测到黑线返回1   
                                                                                   
     switch(status)
     {
       case 110:                                                                //理想
            SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
            break;
       case 1110:                                                               //右
            SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
            break;
       case 111:                                                                //左
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
   {                                                                            //用于第二题
     status = Getstatus(flag0, flag1, flag2, flag3);
     
     switch(status)
     {
       case 110:                                                                //理想
            SetDuty(PWM1_BASE,PWM_OUT_6,0.95);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.62);
            break;
       case 1110:                                                               //右
            SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
            SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
            break;
       case 111:                                                                //左
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
//      while(TIM_start == 0)                                                     //用于60s启动
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
        
        switch(status)                                                          //用于起步速度
        {
          case 110:                                                             //理想
               SetDuty(PWM1_BASE,PWM_OUT_6,0.65);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.42);
                break;
          case 1110:                                                            //右
               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
               break;
          case 111:                                                             //左
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
        switch(status)                                                          //用于靠近减速
        {
          case 110:                                                             //理想
               SetDuty(PWM1_BASE,PWM_OUT_6,0.1);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.05);
                break;
          case 1110:                                                            //右
               SetDuty(PWM1_BASE,PWM_OUT_6,0.15);
               SetDuty(PWM1_BASE,PWM_OUT_7,0.45);
               break;
          case 111:                                                             //左
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
测试状态
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
给我们的大括号单列一行
******************************************************************************************************************/
}
     

 



