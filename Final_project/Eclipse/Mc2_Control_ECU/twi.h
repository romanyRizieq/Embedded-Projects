/*
 * twi.h
 *
 *  Created on: 24 July 2024
 *      Author: Romany Farouk
 */

#ifndef TWI_H_
#define TWI_H_

#include "std_types.h"

typedef enum
{
	SLAVE1=0b00000010,SLAVE2=0b00000100,SLAVE3=0b00001000,SLAVE4=0b00010000,SLAVE5=0b00100000,SLAVE6=0b01000000
}TWI_Address;

typedef enum
{
	NORMAL_MODE=0x08,FAST_MODE=0x02,FAST_MODE_PLUS,HIGH_SPEED_MODE
}TWI_BaudRate;

typedef struct{
TWI_Address address;
TWI_BaudRate bit_rate;
}TWI_ConfigType;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(const TWI_ConfigType * Config_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */
