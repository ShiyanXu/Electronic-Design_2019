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
#include "myuart.h"

void Myuart_Init(void)
{
  SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
  //使能外设
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  //配置复用功能
	GPIOPinConfigure(GPIO_PB0_U1RX);
	GPIOPinConfigure(GPIO_PB1_U1TX);
	
	//分配UART信号
	GPIOPinTypeUART(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1);
	
	//配置UART参数(这样配置可以用UARTprintf)
	UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);	//使用16MHz内部高精度振荡器(PIOSC)作为UART模块时钟
	UARTStdioConfig(1,115200, 16000000);							//UART编号、波特率、UART时钟频率（频率要和上一行设的一致）
	
	UARTprintf("Enter Text: \n");
}
