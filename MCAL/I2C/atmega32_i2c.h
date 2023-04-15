/*
 * atmega32_i2c.h
 *
 *  Created on: Apr 11, 2023
 *      Author: moham
 */

#ifndef MCAL_I2C_ATMEGA32_I2C_H_
#define MCAL_I2C_ATMEGA32_I2C_H_

/***********Private macros*************/
#define STATUS_MASK              0b11111000


/***********Actions' IDs***************/

#define START_ACK                0x08 /* start has been sent */
#define REP_START_ACK            0x10 /* repeated start */
#define SLAVE_ADDR_AND_WR_ACK     0x18 /* Master transmit ( slave address + Write request ) ACK */
#define SLAVE_ADDR_AND_RD_ACK     0x40 /* Master transmit ( slave address + Read request ) ACK */
#define MSTR_WR_BYTE_ACK         0x28 /* Master transmit data ACK */
#define MSTR_RD_BYTE_WITH_ACK    0x50 /* Master received data with ACK */
#define MSTR_RD_BYTE_WITH_NACK   0x58 /* Master received data with not ACK */
#define SLAVE_ADDR_RCVD_RD_REQ    0xA8 /* means that slave address is received with read request */
#define SLAVE_ADDR_RCVD_WR_REQ    0x60 /* means that slave address is received with write request */
#define SLAVE_DATA_RECEIVED      0x80 /* means that a byte is received */
#define SLAVE_BYTE_TRANSMITTED   0xB8 /* means that the written byte is transmitted */


#include "atmega32.h"

typedef struct
{
	uint8_t I2C_Address;
	uint8_t I2C_Mode;
	uint8_t I2C_Prescaler;
}I2C_Config_t;


void I2C_Init(I2C_Config_t *pI2C_Config);


#endif /* MCAL_I2C_ATMEGA32_I2C_H_ */
