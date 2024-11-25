/*
 * Project3.c
 *
 *  Created on: 11 June 2024
 *      Author: Romany Farouk
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "gpio.h"
#include "lcd.h"
#include "adc.h"
#include "lm35_sensor.h"
#include "dc_motor.h"
#include "pwm.h"
#include "dc_motor.h"

#define Temp_1 30
#define Temp_2 60
#define Temp_3 90
#define Temp_4 120
int main(void) {
	uint8 temp;
	/* Initialize drivers and peripherals*/
	LM35_init();/* initialize Temperature sensor */
	LCD_init(); /* initialize LCD driver */
	DcMotor_Init();/* initialize Fan motor */
	/*initial messages on the screen*/
	LCD_moveCursor(0, 1);
	LCD_displayString("Fan is ");
	LCD_moveCursor(1, 1);
	LCD_displayString("Temp =     C");

	while (1) {
		// Continuously read temperature
		temp = LM35_getTemperature();

		/* Display the temperature value every time at same position */
		if ((temp < Temp_1)) {
			LCD_moveCursor(0, 8);
			LCD_displayString("OFF");
			LCD_moveCursor(1, 8);
			LCD_intgerToString(temp);
			// Stop the motor
			DcMotor_Rotate(STOP, 0);
		} else if ((temp >= Temp_1) && (temp < Temp_2)) {
			LCD_moveCursor(0, 8);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 8);
			LCD_intgerToString(temp);
			// Rotate the motor clockwise at 25% speed
			DcMotor_Rotate(CW, 25);
		} else if ((temp >= Temp_2) && (temp < Temp_3)) {
			LCD_moveCursor(0, 8);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 8);
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
			// Rotate the motor clockwise at 50% speed
			DcMotor_Rotate(CW, 50);
		} else if ((temp >= Temp_3) && (temp < Temp_4)) {
			LCD_moveCursor(0, 8);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 8);
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
			// Rotate the motor clockwise at 75% speed
			DcMotor_Rotate(CW, 75);
		} else if ((temp >= Temp_4)) {
			LCD_moveCursor(0, 8);
			LCD_displayString("ON ");
			LCD_moveCursor(1, 8);
			LCD_intgerToString(temp);
			// Rotate the motor clockwise at 100% speed
			DcMotor_Rotate(CW, 100);
		}

		_delay_ms(50); // Delay for stability
	}

	return 0;
}
