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
#include "tim.h"

extern int flag0 , flag1 , flag2 , flag3 ;
extern int TIM_stop, TIM_start, TIM_slow, TIM_quick;
extern int flag;
extern int flag_start;


void TIMER_Init_2_start(void);

/******************************************************************************************************************
*函数名: IntHandle_TIMER0A(void)
*描	 述：定时器中断函数
*输	 入：void
******************************************************************************************************************/
void IntHandle_TIMER0A_1_start(void)//和你注册中断句柄时的名称保持一致
{
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  //清除标志位，第二个是中断类型，我这里是定时器A溢出中断
  
  flag_start = 1;
  TIMER_Init_2_start();
  
}

void IntHandle_TIMER1A_2_start(void)
{
  TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
  //清除标志位，第二个是中断类型，我这里是定时器A溢出中断
  
  //flag_start = 1;
  TIMER_Init_3_loop();
  
}

void IntHandle_TIMER2A_3_loop(void)//和你注册中断句柄时的名称保持一致
{
  TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
  //清除标志位，第二个是中断类型，我这里是定时器A溢出中断
  {
    flag ++;
    if(flag > 4)
    {
      flag = 1;
    }
	}
}

/******************************************************************************************************************
*函数名: TIMER_Init(void)
*描	 述：TIMER初始化函数
*输	 入：void
******************************************************************************************************************/
void TIMER_Init_1_start(void)
{
/* 设置中断优先级，TM4C123G的中断优先级有8个，0最高 */ 
  IntPrioritySet(INT_TIMER0A, 7);
          
  SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  //系统时钟设置
 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  //使能定时器模块Timer0。
 
  TimerConfigure(TIMER0_BASE,TIMER_CFG_ONE_SHOT);
  //配置定时器模块Timer0为Periodic单次计数模式。

  TimerLoadSet(TIMER0_BASE,TIMER_A,60*(SysCtlClockGet())-1);                     //定时1s    --2.5s
  //设定定时器模块Timer0的Load重装载值为系统时钟频率的一半再减一（为0.5秒）。

  TimerIntRegister(TIMER0_BASE,TIMER_A,IntHandle_TIMER0A_1_start);
  //注册中断服务函数，最后那个是中断服务函数句柄，
  //其实后面看库函数手册这一步也可以不用啦，那时候中断入口函数名字就是官方默认的（具体是什么忘了...）  
       
  IntEnable(INT_TIMER0A);
  //使能定时器模块Timer0的定时器A的中断。

  TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
  //使能单独的定时器中断源，第一个TIMER0_BASE为Timer0的基地址，
  //第二个是中断源启用的中断事件的标识码，TIMER_TIMA_TIMEOUT的意思是定时器A(TimerA)溢出(重装载)，以此为标志位，
  //当TimerA重装载时就会触发中断。
 
  IntMasterEnable();
  //使能处理器中断，使处理器能够响应中断。

  TimerEnable(TIMER0_BASE,TIMER_A);
  //使能定时器TimerA。
}

void TIMER_Init_2_start(void)
{
/* 设置中断优先级，TM4C123G的中断优先级有8个，0最高 */ 
  IntPrioritySet(INT_TIMER1A, 7);
          
  SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  //系统时钟设置
 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
  //使能定时器模块Timer0。
 
  TimerConfigure(TIMER1_BASE,TIMER_CFG_ONE_SHOT);
  //配置定时器模块Timer0为Periodic周期计数模式。

  TimerLoadSet(TIMER1_BASE,TIMER_A,1.8*(SysCtlClockGet())-1);                     //定时1s  
  //设定定时器模块Timer0的Load重装载值为系统时钟频率的一半再减一（为0.5秒）。

  TimerIntRegister(TIMER1_BASE,TIMER_A,IntHandle_TIMER1A_2_start);
  //注册中断服务函数，最后那个是中断服务函数句柄，
  //其实后面看库函数手册这一步也可以不用啦，那时候中断入口函数名字就是官方默认的（具体是什么忘了...）  
       
  IntEnable(INT_TIMER1A);
  //使能定时器模块Timer0的定时器A的中断。

  TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
  //使能单独的定时器中断源，第一个TIMER0_BASE为Timer0的基地址，
  //第二个是中断源启用的中断事件的标识码，TIMER_TIMA_TIMEOUT的意思是定时器A(TimerA)溢出(重装载)，以此为标志位，
  //当TimerA重装载时就会触发中断。
 
  IntMasterEnable();
  //使能处理器中断，使处理器能够响应中断。

  TimerEnable(TIMER1_BASE,TIMER_A);
  //使能定时器TimerA。
}

void TIMER_Init_3_loop(void)
{
/* 设置中断优先级，TM4C123G的中断优先级有8个，0最高 */ 
  IntPrioritySet(INT_TIMER2A, 7);
          
  SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  //系统时钟设置
 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
  //使能定时器模块Timer0。
 
  TimerConfigure(TIMER2_BASE,TIMER_CFG_PERIODIC);
  //配置定时器模块Timer0为Periodic单次计数模式。

  TimerLoadSet(TIMER2_BASE,TIMER_A,2.8*(SysCtlClockGet())-1);                     //定时1s    --2.5s
  //设定定时器模块Timer0的Load重装载值为系统时钟频率的一半再减一（为0.5秒）。

  TimerIntRegister(TIMER2_BASE,TIMER_A,IntHandle_TIMER2A_3_loop);
  //注册中断服务函数，最后那个是中断服务函数句柄，
  //其实后面看库函数手册这一步也可以不用啦，那时候中断入口函数名字就是官方默认的（具体是什么忘了...）  
       
  IntEnable(INT_TIMER2A);
  //使能定时器模块Timer0的定时器A的中断。

  TimerIntEnable(TIMER2_BASE,TIMER_TIMA_TIMEOUT);
  //使能单独的定时器中断源，第一个TIMER0_BASE为Timer0的基地址，
  //第二个是中断源启用的中断事件的标识码，TIMER_TIMA_TIMEOUT的意思是定时器A(TimerA)溢出(重装载)，以此为标志位，
  //当TimerA重装载时就会触发中断。
 
  IntMasterEnable();
  //使能处理器中断，使处理器能够响应中断。

  TimerEnable(TIMER2_BASE,TIMER_A);
  //使能定时器TimerA。
}





