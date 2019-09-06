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

/******************************************************************************************************************
*������: IntHandle_TIMER0A(void)
*��	 ������ʱ���жϺ���
*��	 �룺void
******************************************************************************************************************/
void IntHandle_TIMER0A_Q1_stop(void)//����ע���жϾ��ʱ�����Ʊ���һ��
{
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  //�����־λ���ڶ������ж����ͣ��������Ƕ�ʱ��A����ж�
  {
    TIM_stop = 1;
    UARTprintf("TIM_stop = 1;");
	} 
}
void IntHandle_TIMER0A_Q3_start(void)//����ע���жϾ��ʱ�����Ʊ���һ��
{
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  //�����־λ���ڶ������ж����ͣ��������Ƕ�ʱ��A����ж�
  {
    TIM_start = 1;
    UARTprintf("TIM_start = 1;");
    TIMER_Init_Q3_slow();
	} 
}
void IntHandle_TIMER1A_Q3_slow(void)//����ע���жϾ��ʱ�����Ʊ���һ��
{
  TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
  //�����־λ���ڶ������ж����ͣ��������Ƕ�ʱ��A����ж�
  {
    TIM_slow = 1;
    TIM_quick = 0;
    UARTprintf("TIM_slow = 1;");
    TIMER_Init_Q3_quick();
	} 
}
void IntHandle_TIMER2A_Q3_quick(void)//����ע���жϾ��ʱ�����Ʊ���һ��
{
  TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
  //�����־λ���ڶ������ж����ͣ��������Ƕ�ʱ��A����ж�
  {
    TIM_slow = 0;
    TIM_quick = 1;
    UARTprintf("TIM_quick = 1;");
    TIMER_Init_Q3_slow();
	} 
}

/******************************************************************************************************************
*������: TIMER_Init(void)
*��	 ����TIMER��ʼ������
*��	 �룺void
******************************************************************************************************************/
void TIMER_Init_Q1_stop(void)
{
/* �����ж����ȼ���TM4C123G���ж����ȼ���8����0��� */ 
  IntPrioritySet(INT_TIMER0A, 7);
          
  SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  //ϵͳʱ������
 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  //ʹ�ܶ�ʱ��ģ��Timer0��
 
  TimerConfigure(TIMER0_BASE,TIMER_CFG_ONE_SHOT);
  //���ö�ʱ��ģ��Timer0ΪPeriodic���μ���ģʽ��

  TimerLoadSet(TIMER0_BASE,TIMER_A,2.5*(SysCtlClockGet())-1);                     //��ʱ1s    --2.5s
  //�趨��ʱ��ģ��Timer0��Load��װ��ֵΪϵͳʱ��Ƶ�ʵ�һ���ټ�һ��Ϊ0.5�룩��

  TimerIntRegister(TIMER0_BASE,TIMER_A,IntHandle_TIMER0A_Q1_stop);
  //ע���жϷ�����������Ǹ����жϷ����������
  //��ʵ���濴�⺯���ֲ���һ��Ҳ���Բ���������ʱ���ж���ں������־��ǹٷ�Ĭ�ϵģ�������ʲô����...��  
       
  IntEnable(INT_TIMER0A);
  //ʹ�ܶ�ʱ��ģ��Timer0�Ķ�ʱ��A���жϡ�

  TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
  //ʹ�ܵ����Ķ�ʱ���ж�Դ����һ��TIMER0_BASEΪTimer0�Ļ���ַ��
  //�ڶ������ж�Դ���õ��ж��¼��ı�ʶ�룬TIMER_TIMA_TIMEOUT����˼�Ƕ�ʱ��A(TimerA)���(��װ��)���Դ�Ϊ��־λ��
  //��TimerA��װ��ʱ�ͻᴥ���жϡ�
 
  IntMasterEnable();
  //ʹ�ܴ������жϣ�ʹ�������ܹ���Ӧ�жϡ�

  TimerEnable(TIMER0_BASE,TIMER_A);
  //ʹ�ܶ�ʱ��TimerA��
}

void TIMER_Init_Q3_start(void)
{
/* �����ж����ȼ���TM4C123G���ж����ȼ���8����0��� */ 
  IntPrioritySet(INT_TIMER0A, 7);
          
  SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  //ϵͳʱ������
 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  //ʹ�ܶ�ʱ��ģ��Timer0��
 
  TimerConfigure(TIMER0_BASE,TIMER_CFG_ONE_SHOT);
  //���ö�ʱ��ģ��Timer0ΪPeriodic���μ���ģʽ��

  TimerLoadSet(TIMER0_BASE,TIMER_A,44*(SysCtlClockGet())-1);                     //��ʱ1s    --57s
  //�趨��ʱ��ģ��Timer0��Load��װ��ֵΪϵͳʱ��Ƶ�ʵ�һ���ټ�һ��Ϊ0.5�룩��

  TimerIntRegister(TIMER0_BASE,TIMER_A,IntHandle_TIMER0A_Q3_start);
  //ע���жϷ�����������Ǹ����жϷ����������
  //��ʵ���濴�⺯���ֲ���һ��Ҳ���Բ���������ʱ���ж���ں������־��ǹٷ�Ĭ�ϵģ�������ʲô����...��  
       
  IntEnable(INT_TIMER0A);
  //ʹ�ܶ�ʱ��ģ��Timer0�Ķ�ʱ��A���жϡ�

  TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
  //ʹ�ܵ����Ķ�ʱ���ж�Դ����һ��TIMER0_BASEΪTimer0�Ļ���ַ��
  //�ڶ������ж�Դ���õ��ж��¼��ı�ʶ�룬TIMER_TIMA_TIMEOUT����˼�Ƕ�ʱ��A(TimerA)���(��װ��)���Դ�Ϊ��־λ��
  //��TimerA��װ��ʱ�ͻᴥ���жϡ�
 
  IntMasterEnable();
  //ʹ�ܴ������жϣ�ʹ�������ܹ���Ӧ�жϡ�

  TimerEnable(TIMER0_BASE,TIMER_A);
  //ʹ�ܶ�ʱ��TimerA��
}

void TIMER_Init_Q3_slow(void)
{
/* �����ж����ȼ���TM4C123G���ж����ȼ���8����0��� */ 
  IntPrioritySet(INT_TIMER1A, 7);
          
  SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  //ϵͳʱ������
 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
  //ʹ�ܶ�ʱ��ģ��Timer1��
 
  TimerConfigure(TIMER1_BASE,TIMER_CFG_ONE_SHOT);
  //���ö�ʱ��ģ��Timer1ΪPeriodic���ڼ���ģʽ��

  TimerLoadSet(TIMER1_BASE,TIMER_A,2.2*(SysCtlClockGet())-1);                     //��ʱ1s    
  //�趨��ʱ��ģ��Timer1��Load��װ��ֵΪϵͳʱ��Ƶ�ʵ�һ���ټ�һ��Ϊ0.5�룩��

  TimerIntRegister(TIMER1_BASE,TIMER_A,IntHandle_TIMER1A_Q3_slow);
  //ע���жϷ�����������Ǹ����жϷ����������
  //��ʵ���濴�⺯���ֲ���һ��Ҳ���Բ���������ʱ���ж���ں������־��ǹٷ�Ĭ�ϵģ�������ʲô����...��   
       
  IntEnable(INT_TIMER1A);
  //ʹ�ܶ�ʱ��ģ��Timer1�Ķ�ʱ��A���жϡ�

  TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
  //ʹ�ܵ����Ķ�ʱ���ж�Դ����һ��TIMER0_BASEΪTimer0�Ļ���ַ��
  //�ڶ������ж�Դ���õ��ж��¼��ı�ʶ�룬TIMER_TIMA_TIMEOUT����˼�Ƕ�ʱ��A(TimerA)���(��װ��)���Դ�Ϊ��־λ��
  //��TimerA��װ��ʱ�ͻᴥ���жϡ�
  
  IntMasterEnable();
  //ʹ�ܴ������жϣ�ʹ�������ܹ���Ӧ�жϡ�

  TimerEnable(TIMER1_BASE,TIMER_A);
  //ʹ�ܶ�ʱ��TimerA��
}

void TIMER_Init_Q3_quick(void)
{
  /* �����ж����ȼ���TM4C123G���ж����ȼ���8����0��� */ 
  IntPrioritySet(INT_TIMER2A, 7);
          
  SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
  //ϵͳʱ������
 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
  //ʹ�ܶ�ʱ��ģ��Timer1��
 
  TimerConfigure(TIMER2_BASE,TIMER_CFG_ONE_SHOT);
  //���ö�ʱ��ģ��Timer1ΪPeriodic���ڼ���ģʽ��

  TimerLoadSet(TIMER2_BASE,TIMER_A,2.5*(SysCtlClockGet())-1);                     //��ʱ1s    
  //�趨��ʱ��ģ��Timer1��Load��װ��ֵΪϵͳʱ��Ƶ�ʵ�һ���ټ�һ��Ϊ0.5�룩��

  TimerIntRegister(TIMER2_BASE,TIMER_A,IntHandle_TIMER2A_Q3_quick);
  //ע���жϷ�����������Ǹ����жϷ����������
  //��ʵ���濴�⺯���ֲ���һ��Ҳ���Բ���������ʱ���ж���ں������־��ǹٷ�Ĭ�ϵģ�������ʲô����...��   
       
  IntEnable(INT_TIMER2A);
  //ʹ�ܶ�ʱ��ģ��Timer1�Ķ�ʱ��A���жϡ�

  TimerIntEnable(TIMER2_BASE,TIMER_TIMA_TIMEOUT);
  //ʹ�ܵ����Ķ�ʱ���ж�Դ����һ��TIMER0_BASEΪTimer0�Ļ���ַ��
  //�ڶ������ж�Դ���õ��ж��¼��ı�ʶ�룬TIMER_TIMA_TIMEOUT����˼�Ƕ�ʱ��A(TimerA)���(��װ��)���Դ�Ϊ��־λ��
  //��TimerA��װ��ʱ�ͻᴥ���жϡ�
  
  IntMasterEnable();
  //ʹ�ܴ������жϣ�ʹ�������ܹ���Ӧ�жϡ�

  TimerEnable(TIMER2_BASE,TIMER_A);
  //ʹ�ܶ�ʱ��TimerA��
}

