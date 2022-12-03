#include "MKL25Z4.h"

void i2c_init();

void i2c_set_slave_address(const uint8_t addr);

uint8_t i2c_write_addr8_data8(const uint8_t reg_addr, const uint8_t byte);
uint8_t i2c_write_addr8_data32(const uint8_t reg_addr, const uint32_t bytes);
uint8_t i2c_write_addr8_bytes(const uint8_t reg_addr, uint8_t* const bytes, const uint16_t byte_count);

uint8_t i2c_read_addr8_data8(const uint8_t reg_addr, uint8_t* const byte);
uint8_t i2c_read_addr8_data16(const uint8_t reg_addr, uint16_t* const bytes);
uint8_t i2c_read_addr8_data32(const uint8_t reg_addr, uint32_t* const bytes);
uint8_t i2c_read_addr8_bytes(const uint8_t reg_addr, uint8_t* const bytes, const uint16_t byte_count);
