/*
 * PID.c
 *
 *  Created on: Jul 24, 2016
 *      Author: Emmanuel
 */

#include <stdbool.h>
#include <stdint.h>
#include "PID.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "sensorhub.h" // make function that outputs angle value we need
#include "motor.h" //controls wheels

//#include kalman.h
//#include "steering.h" //checks for steering position, potentiometer
//#include "battery.h" // monitors battery value

volatile float PIDValue;
volatile float lastError;
volatile float integratedError;
volatile float Ki=0.2;
volatile float Kp=0.2;
volatile float Kd=0.4;
volatile float PIDLeft;
volatile float PIDRight;
volatile uint32_t maxspeed = 800;
volatile uint32_t minspeed = 200;
volatile uint32_t currentSpeed=550;

void PID(uint32_t restangle, uint32_t offset,  uint32_t turning,  uint32_t dt) {


	uint32_t error = (restangle - pitch); //define pitch, dt
	uint32_t pterm = Kp*error;
	integratedError += error * dt; //put constrain on error?
	uint32_t iterm = (Ki * 100) * integratedError;
	uint32_t dterm = (Kd/100) * (error - lastError)/dt;
	lastError = error;
	PIDValue = pterm + iterm + dterm;

	//currentSpeed = (currentSpeed + PIDValue * 0.004) * 0.999;

	currentSpeed = currentSpeed + PIDValue;

	if (currentSpeed > maxspeed)
	{
		currentSpeed = maxspeed;
	}
	if(currentSpeed<minspeed)
	{
		currentSpeed=minspeed;
	}
	// what are these values?
	//need to constrain speed to values that are safe

	PIDValue +=currentSpeed;
	PIDLeft = PIDValue;
	PIDRight = PIDValue;

	if (PIDLeft >= 0) // how to convert to 500 duty cycle
	{
		motor_left(PIDLeft);
	}

	  else
	  {
		  motor_left(-PIDLeft);
	  }
	  if (PIDRight >= 0)
	  {
		  motor_right(PIDRight);
	  }
	  else
	  {
		  motor_right(-PIDRight);
	}


}


//#if 0 // TODO: Estimate velocity and steer
  /* Steer robot sideways */

	/*
if (turning < 0) { // Left
    turning += abs((double)wheelVelocity / velocityScaleTurning); // Scale down at high speed
    if (turning > 0)
      turning = 0;
  } else if (turning > 0) { // Right
    turning -= abs((double)wheelVelocity / velocityScaleTurning); // Scale down at high speed
    if (turning < 0)
      turning = 0;
  }
#endif





// TODO: Turn opposite when going backwards
  uint32_t PIDLeft = PIDValue - turning;
  uint32_t PIDRight = PIDValue + turning;

  PIDLeft *= leftMotorScaler; // Compensate for difference in some of the motors
  PIDRight *= rightMotorScaler;
*/





void stopAndReset() {
  PIDLeft=500;
  PIDRight=500;
  motor_left(PIDLeft);
  motor_right(PIDRight);
  lastError = 0;
  integratedError = 0;
  currentSpeed = 0;
}

