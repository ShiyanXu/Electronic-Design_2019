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
#include "TIM.h"

int flag = 2;

int flag_start = 0;

void GPIO_Init_new(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

  /* �ȴ�GPIOF׼����� */
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
  {
  }

  /* PC4|C5|C6|C7 PD6|D7 IO������Ϊ���ģʽ */
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);
  
  /*���ģ��*/
  /* PC4|C5|C6|C7���� */                          
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
}

int main()
{
  GPIO_Init_new();
  TIMER_Init_1_start();

  
  while(flag_start != 1)                                                        //1��
  {
      GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
      GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
      GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
      GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
  }
  while(1)                                                                      //��ʼ��flag = 2����2��
  {
    if(flag == 1)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
    }
    
    if(flag == 2)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
    }
    
    if(flag == 3)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
    }
    
    if(flag == 4)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
    }
  }
    
}
