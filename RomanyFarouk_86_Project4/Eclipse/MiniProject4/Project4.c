/*
 * Project4.c
 *
 *  Created on: 25 June 2024
 *      Author: Romany Farouk
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "gpio.h"
#include "icu.h"
#include "lcd.h"
#include "Ultrasonic.h"

void main(void) {

	LCD_init(); /* initialize LCD driver */
	/*initial messages on the screen*/
	LCD_displayString("Distance =    cm");
	LCD_moveCursor(0, 11); /* Move cursor to position after "Distance = " */
	Ultrasonic_init();
	SREG |= (1 << 7); /* Enable global interrupts */

	while (1) {
		/* Clear the previous distance value on the LCD */
		LCD_moveCursor(0, 13);
		LCD_displayString(" "); /* Clear previous digits */
		/* Read and display the new distance */
		LCD_moveCursor(0, 11);
		LCD_intgerToString(Ultrasonic_readDistance());
		_delay_ms(250); /* Delay for stability */
	}
}
