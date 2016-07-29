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

uint32_t speed_left;
uint32_t speed_right;
volatile uint32_t ui32Load;
volatile uint32_t ui32PWMClock;
volatile uint32_t ui8Adjust;


void motors_initialize(void)
{
	ui32PWMClock = SysCtlClockGet() /2;
	ui32Load = (ui32PWMClock / 20000) - 1;
	GPIOPinConfigure(GPIO_PF1_M1PWM5);
	GPIOPinConfigure(GPIO_PE5_M0PWM5);
	GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_4);
	GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);// change values
	PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
	PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1,ui32Load);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ui32Load);
	PWMGenEnable(PWM1_BASE, PWM_GEN_1);
	PWMGenEnable(PWM1_BASE, PWM_GEN_2);
	PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, true);
	PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
}


//Give PWM value for debugging
void motor_left(uint32_t pwm_value)
{
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, pwm_value*ui32Load/1000);
}
void motor_right(uint32_t pwm_value)
{
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, pwm_value*ui32Load/1000);
}
