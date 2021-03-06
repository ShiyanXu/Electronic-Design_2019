#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"				//Register Definitions
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
//#include "uartstdio.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/timer.h"
#include "mypwm.h"

/******************************************************************************************************************
*函数名: PWM_Init()
*描	 述：PWM初始化函数
*输	 入：无
*线  路：PF2<->M1PWM6
				 PF3<->M1PWM7
******************************************************************************************************************/
void PWM_Init(void)
{
	//配置PWM时钟（设置USEPWMDIV分频器）
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);																									//PWM时钟 16M

	//使能时钟
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);			//使能PWM模块1时钟																		
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		//使能GPIOF时钟																		
	
	//使能引脚复用PWM功能
	GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_2);
	GPIOPinTypePWM(GPIO_PORTF_BASE,GPIO_PIN_3);
	
	//PWM信号分配
	GPIOPinConfigure(GPIO_PF2_M1PWM6);					//PF2->PWM模块1信号6																							
	GPIOPinConfigure(GPIO_PF3_M1PWM7);					//PF3->PWM模块1信号7																								

	//配置PWM发生器
	//模块1->发生器3->上下计数，不同步
	PWMGenConfigure(PWM1_BASE,PWM_GEN_3,PWM_GEN_MODE_UP_DOWN|PWM_GEN_MODE_NO_SYNC);	
	
	//配置PWM周期
	PWMGenPeriodSet(PWM1_BASE,PWM_GEN_3,64000);			//64*10^3/16/10^6=4ms																			
	
	//配置PWM占空比
	PWMPulseWidthSet(PWM1_BASE,PWM_OUT_6,PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.01);		//比较值为四分之一总计数值，25%
	PWMPulseWidthSet(PWM1_BASE,PWM_OUT_7,PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)*0.01);		//比较值为四分之三总计数值，75%

	//使能PWM模块1输出
	PWMOutputState(PWM1_BASE,PWM_OUT_6_BIT,true);
	PWMOutputState(PWM1_BASE,PWM_OUT_7_BIT,true);
	
	//使能PWM发生器
	PWMGenEnable(PWM1_BASE,PWM_GEN_3);
}



/******************************************************************************************************************
*函数名: SetDuty(uint32_t ui32Base,uint32_t ui32PWMOut,float duty)
*描	 述：PWM初始化函数
*输	 入：PWM模块编号、信号编号、占空比
******************************************************************************************************************/
void SetDuty(uint32_t ui32Base,uint32_t ui32PWMOut,float duty)
{
		uint32_t ui32Gen;
		uint32_t ui32OutBits;
	
		switch(ui32PWMOut)
		{
			case PWM_OUT_0:	ui32Gen=PWM_GEN_0,ui32OutBits=PWM_OUT_0_BIT;	break;
			case PWM_OUT_1:	ui32Gen=PWM_GEN_0,ui32OutBits=PWM_OUT_1_BIT;	break;
			case PWM_OUT_2:	ui32Gen=PWM_GEN_1,ui32OutBits=PWM_OUT_2_BIT;	break;
			case PWM_OUT_3:	ui32Gen=PWM_GEN_1,ui32OutBits=PWM_OUT_3_BIT;	break;
			case PWM_OUT_4:	ui32Gen=PWM_GEN_2,ui32OutBits=PWM_OUT_4_BIT;	break;
			case PWM_OUT_5:	ui32Gen=PWM_GEN_2,ui32OutBits=PWM_OUT_5_BIT;	break;
			case PWM_OUT_6:	ui32Gen=PWM_GEN_3,ui32OutBits=PWM_OUT_6_BIT;	break;
			case PWM_OUT_7:	ui32Gen=PWM_GEN_3,ui32OutBits=PWM_OUT_7_BIT;	break;
		}
	
    //配置占空比
    PWMPulseWidthSet(ui32Base, ui32PWMOut, PWMGenPeriodGet(ui32Base, ui32Gen)*duty);
    PWMOutputState(ui32Base, ui32OutBits, true);
    //使能发生器模块
    PWMGenEnable(ui32Base, ui32Gen);
}
