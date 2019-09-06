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
#include "myuart.h"


extern int flag_power;
extern int flag0 , flag1 , flag2 , flag3 ;
extern uint8_t getChar;
extern int status;
extern int mode;
/******************************************************************************************************************
*������: io_interrupt(void)
*��	 ����EXTI������
*��	 �룺void
******************************************************************************************************************/
void io0_interrupt(void)
{
    uint32_t s = GPIOIntStatus(GPIO_PORTD_BASE, true);
    GPIOIntClear(GPIO_PORTD_BASE, s);
  
    if((s&GPIO_PIN_0) == GPIO_PIN_0)
    {
      if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0))                              //��1������
      {
        flag0 = 1;
      }
      else //if(GPIOPinRead(GPIO_PORTD_BASE, 0))
      {
        flag0 = 0;
      }
    }  
    
    if((s&GPIO_PIN_1) == GPIO_PIN_1)
    {
      if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1))                              //��1������
      {
        flag1 = 1;
      }
      else //if(GPIOPinRead(GPIO_PORTD_BASE, 0))
      {
        flag1 = 0;
      }
    }

    if((s&GPIO_PIN_2) == GPIO_PIN_2)
    {
      if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2))                              //��1������
      {
        flag2 = 1;
      }
      else //if(GPIOPinRead(GPIO_PORTD_BASE, 0))
      {
        flag2 = 0;
      }
    }

    if((s&GPIO_PIN_3) == GPIO_PIN_3)
    {
      if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3))                              //��1������
      {
        flag3 = 1;
      }
      else //if(GPIOPinRead(GPIO_PORTD_BASE, 0))
      {
        flag3 = 0;
      }
    }
}

void io1_interrupt(void)
{
  uint32_t s = GPIOIntStatus(GPIO_PORTF_BASE, true);
  GPIOIntClear(GPIO_PORTF_BASE, s);
    
  if((s&GPIO_PIN_4) == GPIO_PIN_4)
  {
      while(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))//�ȴ������ɿ�
          ;
      //getChar = status;
      //UARTCharPut(UART1_BASE,getChar);
      UARTprintf("status:%4d \n",status);
      UARTprintf("flag0:%d \n",flag0);
      UARTprintf("flag3:%d \n",flag3);
      mode = 1;
      UARTprintf("mode:%d \n",mode);
      
  }
}

void io2_interrupt(void)
{
    uint32_t s = GPIOIntStatus(GPIO_PORTA_BASE, true);
    GPIOIntClear(GPIO_PORTA_BASE, s);

    if((s&GPIO_PIN_2) == GPIO_PIN_2)
    {
      if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2))                              //��1������
      {
        flag_power = 0;
      }
      else //if(GPIOPinRead(GPIO_PORTD_BASE, 0))
      {
        flag_power = 1;
      }
    }
}
/******************************************************************************************************************
*������: EXTI_Init(void)
*��	 ����EXTI��ʼ������
*��	 �룺void
******************************************************************************************************************/
void EXTI_Init(void)
{
  //ʱ��Ƶ�ʣ�40MHz
  SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |  SYSCTL_XTAL_16MHZ);

  //��������
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
  {}
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  {} 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
  {} 
   
  /*����*/
  /* PD0|D1|D2|D3���� */
  GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0);
  GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_3);
   
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);                            //����SW2
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);                            //����SW1
    
  GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_2);                            //����ʶ
    
  /* ������������ */
  GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
   
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  
  GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
      
  //�����ж�
  GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_BOTH_EDGES);
  GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_BOTH_EDGES);
  
  GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
  GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
  
  GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_BOTH_EDGES);
      
  GPIOIntRegister(GPIO_PORTD_BASE, io0_interrupt);  
  GPIOIntRegister(GPIO_PORTF_BASE, io1_interrupt); 
  GPIOIntRegister(GPIO_PORTA_BASE, io2_interrupt); 
  
  //�����ж�
  GPIOIntEnable(GPIO_PORTD_BASE, GPIO_INT_PIN_0);
  GPIOIntEnable(GPIO_PORTD_BASE, GPIO_INT_PIN_3);
  IntEnable(INT_GPIOD);
  
  GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0);
  GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
  IntEnable(INT_GPIOF);
  
  GPIOIntEnable(GPIO_PORTA_BASE, GPIO_INT_PIN_2);
  IntEnable(INT_GPIOA);
  
  IntMasterEnable();

}
