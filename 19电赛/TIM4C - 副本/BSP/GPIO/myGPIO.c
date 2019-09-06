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
#include "mygpio.h"

/******************************************************************************************************************
*������: GPIO_Init()
*��	 ����GPIO��ʼ������
*��	 �룺��
*��  ·��PC4|C5|C6|C7<->3.3
				 PD6|D7      <->GND
******************************************************************************************************************/
void GPIO_Init(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  /* �ȴ�GPIOF׼����� */
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
  {
  }
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
  {
  }
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
  {
  }

  /* PC4|C5|C6|C7 PD6|D7 IO������Ϊ���ģʽ */
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);
  
  GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6);
  GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_7);
  
  GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_5);
  GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_6);
  GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_7);
  
  
  /*���*/
  /* PC4|C5|C6|C7�ø� */                          
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
  
  /* PD6|D7�õ� */
  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0);
  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_7, 0);
  
}
void GPIO_Init_repair(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
  {
  }
  
  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5);
  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6);
  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);
  
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
}
