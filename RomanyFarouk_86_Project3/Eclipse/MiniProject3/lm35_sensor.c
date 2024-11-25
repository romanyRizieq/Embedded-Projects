/*
 * lm35_sensor.c
 *
 *  Created on: 11 June 2024
 *      Author: Romany Farouk
 */

#include "lm35_sensor.h"
#include "adc.h"

/*
 * Description:
 * init the sensor's channel for the adc.
 * */
void LM35_init(void) {
	/*Some other configuration maybe implemented here */
	ADC_configType config = { ADC_INTERNAL, ADC_PRESCALER_8 };
	ADC_init(&config);
}

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void) {
	uint8 temp_value = 0;

	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value =
			(uint8) (((uint32) adc_value * SENSOR_MAX_TEMPERATURE
					* ADC_REF_VOLT_VALUE)
					/ (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}

