/*
 * dc_motor.c
 *
 *  Created on: 11 June 2024
 *      Author: Romany Farouk
 */

#include "dc_motor.h"
#include "gpio.h"
#include "PWM.h"
#include "common_macros.h"
/* Initialize GPIO pins and PWM for the motor */
void DcMotor_Init(void) {
	/* Initialize GPIO pins for motor direction control */
	GPIO_setupPinDirection(DC_Motor_Port, DC_Motor_PIN0, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_Motor_Port, DC_Motor_PIN1, PIN_OUTPUT);
	// Configure GPIO pins for motor direction (e.g., CW and ACW)
	/* Stop the motor initially */
	GPIO_writePin(DC_Motor_Port, DC_Motor_PIN0, LOGIC_LOW);
	GPIO_writePin(DC_Motor_Port, DC_Motor_PIN1, LOGIC_LOW);
}

/* Rotate the DC motor based on the provided state and speed */
void DcMotor_Rotate(DcMotor_State state, uint8 speed) {
	/* Set motor direction based on the provided state */
	switch (state) {
	case CW:
		GPIO_writePin(DC_Motor_Port, DC_Motor_PIN0, LOGIC_HIGH);
		GPIO_writePin(DC_Motor_Port, DC_Motor_PIN1, LOGIC_LOW);
		break;
	case ACW:
		GPIO_writePin(DC_Motor_Port, DC_Motor_PIN0, LOGIC_LOW);
		GPIO_writePin(DC_Motor_Port, DC_Motor_PIN1, LOGIC_HIGH);
		break;
	case STOP:
	default:
		GPIO_writePin(DC_Motor_Port, DC_Motor_PIN0, LOGIC_LOW);
		GPIO_writePin(DC_Motor_Port, DC_Motor_PIN1, LOGIC_LOW);
		break;
	}
	/*set DC MOTOR SPEED using PWM
	 * Set PWM duty cycle based on the provided speed
	 *  Convert speed percentage to PWM duty cycle value
	 *  Apply PWM duty cycle to control motor speed
	 */
	PWM_Timer0_Start(speed);
}
