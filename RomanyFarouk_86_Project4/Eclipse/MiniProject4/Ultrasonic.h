/*
 * Ultrasonic.h
 *
 *  Created on: 25 June 2024
 *      Author: Romany Farouk
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <util/delay.h> /* For the delay functions */
#include "std_types.h"  /* Assuming this header includes standard data types like uint16, etc. */
#include "icu.h"        /* Including ICU driver header for Input Capture Unit functionality */
#include "gpio.h"       /* Including GPIO driver header for GPIO pin control */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Trigger_portID   PORTB_ID   /* Define the port ID for the trigger pin */
#define Trigger_pinID    PIN5_ID    /* Define the pin ID for the trigger pin */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile uint16 pulse_width = 0;   /* Global variable to store pulse width */
static volatile uint16 distance_cm = 0;    /* Global variable to store distance in cm */
static volatile uint8 count = 0;           /* Counter variable for edge processing */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the ultrasonic module.
 * This function initializes the ICU (Input Capture Unit) for measuring pulse width,
 * sets up the callback function for edge processing, and configures the GPIO pin
 * for the ultrasonic trigger.
 */
void Ultrasonic_init(void);

/*
 * Description:
 * Function to trigger the ultrasonic sensor.
 * This function sends a trigger pulse to the ultrasonic sensor using GPIO pin control.
 */
void Ultrasonic_Trigger(void);

/*
 * Description:
 * Function to read the distance measured by the ultrasonic sensor.
 * This function triggers the sensor, waits for the measurement to complete,
 * and returns the measured distance in centimeters.
 *
 * Returns:
 * uint16 - The measured distance in centimeters.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description:
 * Callback function for edge processing.
 * This function is automatically called by the ICU ISR (Interrupt Service Routine)
 * to process the pulse width measurement and calculate the distance.
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
