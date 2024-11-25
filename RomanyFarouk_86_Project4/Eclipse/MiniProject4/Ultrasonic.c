/*
 * Ultrasonic.c
 *
 *  Created on: 25 June 2024
 *      Author: Romany Farouk
 */

#include "Ultrasonic.h"

void Ultrasonic_init(void) {
	/* Initialize ICU (Input Capture Unit) for measuring pulse width */
	ICU_ConfigType ICU_configured = { F_CPU_8, RAISING };
	ICU_init(&ICU_configured);
	/* Setup the ICU call back function */
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	/* Setup the direction for the trigger pin as output pin through the GPIO driver */
	GPIO_setupPinDirection(Trigger_portID, Trigger_pinID, PIN_OUTPUT);
}

void Ultrasonic_Trigger(void) {
	/* Send the Trigger pulse to the ultrasonic */
	GPIO_writePin(Trigger_portID, Trigger_pinID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(Trigger_portID, Trigger_pinID, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void) {
	/* Send the trigger pulse by using Ultrasonic_Trigger function */
	Ultrasonic_Trigger();
	/* Start the measurements by the ICU from this moment */
	/* Wait for the ICU to capture the pulse width */
	_delay_ms(50); /* Adjust delay as needed based on maximum expected distance */
	return (uint16) distance_cm;
}

/* Define a callback function for ICU edge processing */
void Ultrasonic_edgeProcessing(void) {
	/* This function will be automatically called by ICU ISR */
	count++;
	if (count == 1) {
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	} else if (count == 2) {
		/* Get the pulse width from ICU */
		pulse_width = ICU_getInputCaptureValue();
		/* Calculate distance in centimeters */
		distance_cm = ((pulse_width / 57.6));
		ICU_setEdgeDetectionType(RAISING);
		count = 0;
	}
}
