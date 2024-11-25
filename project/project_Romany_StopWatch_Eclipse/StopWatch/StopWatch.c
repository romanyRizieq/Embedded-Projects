/*
 * StopWatch.c
 *
 *  Created on: 12 May 2024
 *      Author: Romany Farouk
 */

#include <avr\io.h>
#include <avr\interrupt.h>
#include <util\delay.h>
unsigned char SECONDS = 0, MINUTES = 0, HOURS = 0, TICK = 0; /*initial values for Parameters for stop watch display*/
/*Timer1 in ATmega32 with CTC mode to count the Stop Watch time*/
void Timer1_CTC_Init(void) {
	TCNT1 = 0; /* Set timer1 initial count to zero */

	OCR1A = 15625; /* Set the Compare value to Ftimer=Fcpu/N   prescaler =64 Ftimer=15625*/

	TIMSK |= (1 << OCIE1A); /* Enable Timer1 Compare A Interrupt */

	/* Configure timer control register TCCR1A
	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1 FOC1B=0
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
	TCCR1A = (1 << FOC1A);

	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Prescaler = F_CPU/64 CS10=1 CS11=1 CS12=0
	 */
	TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);
	SREG |= (1 << 7);
}
/* External Timer1 Interrupt Service Routine */
ISR(TIMER1_COMPA_vect) {
	TICK++;
	if (TICK == 1) {
		SECONDS++;
		if (SECONDS == 60) {
			SECONDS = 0;
			MINUTES++;
		}
		if (MINUTES == 60) {
			SECONDS = 0;
			MINUTES = 0;
			HOURS++;
		}
		if (HOURS == 24) {
			SECONDS = 0;
			MINUTES = 0;
			HOURS = 0;
		}
		TICK = 0;
	}
}

/* Stop Watch time should be reset */
/* External INT0 enable and configuration function */
void INT0_Init(void) {
	DDRD &= (~(1 << PD2)); /* Configure INT0/PD2 as input pin*/
	MCUCR |= (1 << ISC01); /* Trigger INT0 with the falling edge*/
	MCUCR &= ~(1 << ISC00); /* Trigger INT0 with the falling edge*/
	GICR |= (1 << INT0); /* Enable external interrupt pin INT0*/
	SREG |= (1 << 7);
}
/* External INT0 Interrupt Service Routine */
ISR(INT0_vect) {
	SREG |= (1 << 7);
	SECONDS = 0;
	MINUTES = 0;
	HOURS = 0;
}
/* Stop Watch time should be paused */
/* External INT1 enable and configuration function */
void INT1_Init(void) {
	DDRD &= (~(1 << PD3)); /* Configure INT1/PD3 as input pin*/
	MCUCR |= (1 << ISC10) | (1 << ISC11); /* Trigger INT1 with the raising edge*/
	GICR |= (1 << INT1); /* Enable external interrupt pin INT1*/
	SREG |= (1 << 7);
}
/* External INT1 Interrupt Service Routine */
ISR(INT1_vect) {
	SREG |= (1 << 7);
	TCCR1B &= ~(1 << CS10) & ~(1 << CS11) & ~(1 << CS12);
}
/* Stop Watch time should be resumed */
/* External INT1 enable and configuration function */
void INT2_Init(void) {
	DDRB &= (~(1 << PB2)); /* Configure INT2/PB2 as input pin*/
	MCUCSR &= ~(1 << ISC2); /* Trigger INT2 with the failing edge*/
	GICR |= (1 << INT2); /* Enable external interrupt pin INT2*/
	SREG |= (1 << 7);
}
/* External INT2 Interrupt Service Routine */
ISR(INT2_vect) {
	SREG |= (1 << 7);
	TCCR1B |= (1 << CS11) | (1 << CS10);
}

void main(void) {
	DDRC |= 0x0F; /*Connect 7447 decoder 4-pins 0000 1111to the first 4-pins in PORTC*/
	PORTC &= 0XF0; /*0 for initial*/
	DDRA |= 0x3F; /*Use first 6-pins 0011 1111 in PORTA as the enable/disable pins for the six 7-segments(output)*/
	PORTA |= 0X3F; /* turn on*/
	SREG |= (1 << 7); /* Enable global interrupts in MC.*/
	Timer1_CTC_Init();
	INT0_Init();
	INT1_Init();
	INT2_Init();
	while (1) {
		PORTA = (PORTA & 0XC0) | 0X01;
		PORTC = (PORTC & 0XF0) | ((SECONDS % 10) & 0X0F);
		_delay_ms(2);
		PORTA = (PORTA & 0XC0) | 0X02;
		PORTC = (PORTC & 0XF0) | ((SECONDS / 10) & 0X0F);
		_delay_ms(2);
		PORTA = (PORTA & 0XC0) | 0X04;
		PORTC = (PORTC & 0XF0) | ((MINUTES % 10) & 0X0F);
		_delay_ms(2);
		PORTA = (PORTA & 0XC0) | 0X08;
		PORTC = (PORTC & 0XF0) | ((MINUTES / 10) & 0X0F);
		_delay_ms(2);
		PORTA = (PORTA & 0XC0) | 0X10;
		PORTC = (PORTC & 0XF0) | ((HOURS % 10) & 0X0F);
		_delay_ms(2);
		PORTA = (PORTA & 0XC0) | 0X20;
		PORTC = (PORTC & 0XF0) | ((HOURS / 10) & 0X0F);
		_delay_ms(2);
	}
}
