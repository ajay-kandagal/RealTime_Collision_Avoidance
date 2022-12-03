/*
 * i2c.c
 *
 *  Created on: 24-Nov-2022
 *      Author: ajayk
 */
#include "i2c.h"
#include "fsl_debug_console.h"


#define I2C1_SCL_PIN 1
#define I2C1_SDA_PIN 0
#define DATA_BUS_SPEED 24000000U


#define I2C1_SEND_START			 	(I2C1->C1 |= I2C_C1_MST_MASK)
#define I2C1_SEND_STOP			 	(I2C1->C1 &= ~I2C_C1_MST_MASK)
#define I2C1_SEND_RESTART		 	(I2C1->C1 |= I2C_C1_RSTA_MASK)

#define I2C1_SET_TRANSMIT_MODE		(I2C1->C1 |= I2C_C1_TX_MASK)
#define I2C1_SET_RECEIVE_MODE 		(I2C1->C1 &= ~I2C_C1_TX_MASK)

#define I2C1_ACK_STATUS				(I2C1->S & I2C_S_RXAK_MASK)
#define I2C1_IS_BUSY				(I2C1->S & I2C_S_BUSY_MASK)

#define I2C1_DISABLE_ACK			(I2C1->C1 |= I2C_C1_TXAK_MASK)
#define I2C1_ENABLE_ACK				(I2C1->C1 &= ~I2C_C1_TXAK_MASK)

#define I2C1_TX_STATUS				(I2C1->S & I2C_S_TCF_MASK)

#define I2C1_WAIT_PERIOD			10000

#define I2C1_WAIT					while((I2C1->S & I2C_S_IICIF_MASK) == 0);I2C1->S |= I2C_S_IICIF_MASK;

uint8_t g_device_addr = 0x00;

void Pause(int number)
{
	int cnt;
	for(cnt=0; cnt<number; cnt++)
	{
		asm("nop");
	};
}

void i2c_init()
{
	// Enable clock gating for I2C1 and PORTE
	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// Set I2C pins
	PORTE->PCR[I2C1_SCL_PIN] |= PORT_PCR_MUX(6);
	PORTE->PCR[I2C1_SDA_PIN] |= PORT_PCR_MUX(6);

	// Setting baud-rate to 400kHz
	I2C1->F = I2C_F_ICR(0x11) | I2C_F_MULT(0);

	// Disable DMA transfer
	I2C1->C1 &= ~I2C_C1_DMAEN_MASK;

	// Enable I2C1 interrupts
	I2C1->C1 = I2C_C2_HDRS_MASK | I2C_C1_IICEN_MASK;
}


void i2c_set_slave_address(const uint8_t addr)
{
	g_device_addr = addr;
}


uint8_t i2c_write_write(uint8_t index, uint8_t *bytes, uint16_t byte_count)
{
	I2C1_SET_TRANSMIT_MODE;
	I2C1_SEND_START;
	I2C1->D = (g_device_addr & 0xFE);		// Write address

	I2C1_WAIT;

	I2C1->D = index;		// Register address to be written
	I2C1_WAIT;

	I2C1_SEND_RESTART;
	I2C1->D = (g_device_addr & 0xFE);	// Receive data on bus
	I2C1_WAIT;

	for (uint8_t i = 0; i < byte_count; i++)
	{
		I2C1->D = bytes[i];
		I2C1_WAIT;
	}

	I2C1_SEND_STOP;

	Pause(50);

	return 1;
}

uint8_t i2c_write_read(uint8_t index, uint8_t *bytes, uint16_t byte_count)
{
	I2C1_SET_TRANSMIT_MODE;
	I2C1_SEND_START;
	I2C1->D = (g_device_addr & 0xFE);		// Write address
	I2C1_WAIT;

	I2C1->D = index;		// Write register address to be read
	I2C1_WAIT;

	I2C1_SEND_RESTART;
	I2C1->D = (g_device_addr | 0x01);	// Receive data on bus
	I2C1_WAIT;

	I2C1_SET_RECEIVE_MODE;
	I2C1_ENABLE_ACK;

	//	data[0] = I2C1->D;
	//	I2C1_WAIT;

	for (uint8_t i = 0; i < byte_count; i++)
	{
		bytes[i] = I2C1->D;
		I2C1_WAIT;
	}

	Pause(50);

	I2C1_DISABLE_ACK;
	I2C1_SEND_STOP;

	return 1;
}

uint8_t i2c_write_addr8_data8(uint8_t addr, uint8_t data)
{
	return i2c_write_write(addr, &data, 1);
}

uint8_t i2c_write_addr8_data32(uint8_t addr, uint32_t data)
{
	return i2c_write_write(addr, (uint8_t*)&data, 1);
}

uint8_t i2c_write_addr8_bytes(uint8_t addr, uint8_t *bytes, uint16_t byte_count)
{
	return i2c_write_write(addr, bytes, byte_count);
}

uint8_t i2c_read_addr8_data8(uint8_t addr, uint8_t *data)
{
	return i2c_write_read(addr, data, 1);
}

uint8_t i2c_read_addr8_data16(uint8_t addr, uint16_t *data)
{
	return i2c_write_read(addr, (uint8_t*)data, 2);
}

uint8_t i2c_read_addr8_data32(uint8_t addr, uint32_t *data)
{
	return i2c_write_read(addr, (uint8_t*)data, 4);
}

uint8_t i2c_read_addr8_bytes(uint8_t addr, uint8_t *bytes, uint16_t byte_count)
{
	return i2c_write_read(addr, bytes, byte_count);
}
