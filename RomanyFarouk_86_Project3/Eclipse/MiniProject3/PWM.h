/*
 * PWM.h
 *
 *  Created on: 11 June 2024
 *      Author: Romany Farouk
 */

#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>
#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* For GET_BIT Macro */
#include "lcd.h"
#include "gpio.h"
#include "std_types.h"

/*
 * Description:
 * Generate a PWM signal with frequency 500Hz
 * Timer0 will be used with pre-scaler F_CPU/8
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 * Duty Cycle can be changed by updating the value
 * in The Compare Register
 */

void PWM_Timer0_Start(uint8 set_duty_cycle);

#endif /* PWM_H_ */
