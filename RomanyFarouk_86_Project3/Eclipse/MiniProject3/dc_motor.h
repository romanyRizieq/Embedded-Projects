/*
 * dc_motor.h
 *
 *  Created on: 11 June 2024
 *      Author: Romany Farouk
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */
#include "PWM.h"
/*******************************************************************************
 *                                Definitions                                  *
 ******************************************************************************/
#define DC_Motor_Port PORTB_ID
#define DC_Motor_PIN0 PIN0_ID
#define DC_Motor_PIN1 PIN1_ID

// Define motor states
typedef enum {
	STOP, CW, ACW
} DcMotor_State;

/* Initialize GPIO pins and PWM for the motor */
void DcMotor_Init(void);
/* Rotate the DC motor based on the provided state and speed */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DC_MOTOR_H_ */
