#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "sensorlib/hw_mpu9150.h"
#include "sensorlib/hw_ak8975.h"
#include "sensorlib/i2cm_drv.h"
#include "sensorlib/ak8975.h"
#include "sensorlib/mpu9150.h"
#include "sensorlib/comp_dcm.h"
#include "drivers/rgb.h"
#include "driverlib/pwm.h"
#include "inc/hw_gpio.h"
#include "sensorhub.h" // make function that outputs angle value we need
#include "motor.h"
#include "PID.h"

int main(void)
{
	initsensorhub();
	motors_initialize();

	while(1)
	{
		sensor();
		PID(0,0,0,0.5);

	}
}
