/*
 * Motors.c
 *
 *  Created on: Jun 25, 2016
 *      Author: Nelson Raym Grajales
 */

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "motor.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#define PWM_FREQUENCY 20000


uint32_t speed_left;
uint32_t speed_right;
volatile uint32_t ui32Load;
volatile uint32_t ui32PWMClock;
volatile uint32_t ui8Adjust;


void motors_initialize(void)
{
/*
	ui32PWMClock = SysCtlClockGet() /2;
	ui32Load = (ui32PWMClock / 20000) - 1;
	GPIOPinConfigure(GPIO_PF1_M1PWM5);
	GPIOPinConfigure(GPIO_PE4_M0PWM4);
	GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_5);
	GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);// change values
	PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
	PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1,ui32Load);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ui32Load);
	PWMGenEnable(PWM1_BASE, PWM_GEN_1);
	PWMGenEnable(PWM1_BASE, PWM_GEN_2);
	PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, true);
	PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
*/


					ROM_SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
					ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_2);
					ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
					ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
					ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
					ROM_GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
					ROM_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
					ROM_GPIOPinConfigure(GPIO_PE4_M1PWM2);
					ROM_GPIOPinConfigure(GPIO_PF1_M1PWM5);
					ui32PWMClock = SysCtlClockGet() / 2;
					ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;
					PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
					PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, ui32Load);
					//ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, ui8Adjust * ui32Load / 1000);
					ROM_PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
					ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_1);
					PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
					PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ui32Load);
					//ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui8Adjust * ui32Load / 1000);
					ROM_PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
					ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_2);

}


//Give PWM value for debugging
void motor_left(uint32_t pwm_value)
{
	//PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, pwm_value*ui32Load/1000);
	ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, pwm_value*ui32Load/1000);
}
void motor_right(uint32_t pwm_value)
{
	//PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, pwm_value*ui32Load/1000);
	ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, pwm_value*ui32Load/1000);
}
