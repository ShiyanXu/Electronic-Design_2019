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
  //ʹ������
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  //���ø��ù���
	GPIOPinConfigure(GPIO_PB0_U1RX);
	GPIOPinConfigure(GPIO_PB1_U1TX);
	
	//����UART�ź�
	GPIOPinTypeUART(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1);
	
	//����UART����(�������ÿ�����UARTprintf)
	UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);	//ʹ��16MHz�ڲ��߾�������(PIOSC)��ΪUARTģ��ʱ��
	UARTStdioConfig(1,115200, 16000000);							//UART��š������ʡ�UARTʱ��Ƶ�ʣ�Ƶ��Ҫ����һ�����һ�£�
	
	UARTprintf("Enter Text: \n");
}
