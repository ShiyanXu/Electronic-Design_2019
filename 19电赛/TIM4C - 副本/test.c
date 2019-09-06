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

  /* 等待GPIOF准备完毕 */
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
  {
  }

  /* PC4|C5|C6|C7 PD6|D7 IO口配置为输出模式 */
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);
  
  /*充电模块*/
  /* PC4|C5|C6|C7拉低 */                          
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
}

int main()
{
  GPIO_Init_new();
  TIMER_Init_1_start();

  
  while(flag_start != 1)                                                        //1开
  {
      GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
      GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
      GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
      GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
  }
  while(1)                                                                      //初始令flag = 2，从2开
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
