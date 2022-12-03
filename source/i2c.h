/*
 * i2c.h
 *
 *  Created on: 24-Nov-2022
 *      Author: ajayk
 */

#ifndef I2C_H_
#define I2C_H_


#include "MKL25Z4.h"


void i2c_init();
void i2c_set_slave_address(const uint8_t addr);

uint8_t i2c_write_write(uint8_t index, uint8_t *bytes, uint16_t byte_count);
uint8_t i2c_write_read(uint8_t index, uint8_t *bytes, uint16_t byte_count);

uint8_t i2c_read_addr8_data8(uint8_t addr, uint8_t *data);
uint8_t i2c_read_addr8_data16(uint8_t addr, uint16_t *data);
uint8_t i2c_read_addr8_data32(uint8_t addr, uint32_t *data);
uint8_t i2c_read_addr8_bytes(uint8_t addr, uint8_t *bytes, uint16_t byte_count);

uint8_t i2c_write_addr8_data8(uint8_t addr, uint8_t data);
uint8_t i2c_write_addr8_data32(uint8_t addr, uint32_t data);
uint8_t i2c_write_addr8_bytes(uint8_t addr, uint8_t *bytes, uint16_t byte_count);


#endif /* I2C_H_ */
