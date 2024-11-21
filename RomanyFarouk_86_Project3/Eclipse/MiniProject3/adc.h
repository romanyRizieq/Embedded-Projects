/*
 * adc.h
 *
 *  Created on: 11 June 2024
 *      Author: Romany Farouk
 */

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_BITS					10
#define ADC_MAXIMUM_VALUE	    	1023
#define ADC_CHANNELS				8
#define ADC_REF_VOLT_VALUE			2.56

typedef uint8 ADC_ErrorType;

typedef enum {
	ADC_AREF = 0, ADC_AVCC = 1, ADC_INTERNAL = 3
} ADC_VrefType;

typedef enum {
	ADC_PRESCALER_2 = 1,
	ADC_PRESCALER_4 = 2,
	ADC_PRESCALER_8 = 3,
	ADC_PRESCALER_16 = 4,
	ADC_PRESCALER_32 = 5,
	ADC_PRESCALER_64 = 6,
	ADC_PRESCALER_128 = 7
} ADC_prescalerType;

typedef struct {
	ADC_VrefType vref;
	ADC_prescalerType prescaler;

} ADC_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_configType *a_config);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

/*
 * undo the initialization on the ADC module
 * @return void
 * */
void ADC_Deinit(void);

#endif /* ADC_H_ */
