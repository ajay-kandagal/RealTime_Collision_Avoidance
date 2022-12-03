#include "MKL25Z4.h"
#include "nxp_i2c.h"
#include "timer.h"

uint8_t g_nxp_device_addr = 0x00;

void nxp_i2c_set_slave_address(const uint8_t addr)
{
	g_nxp_device_addr = addr;
}

void I2C_WriteRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, /*unsigned*/ char u8Data)
{
	I2C_Start();	          
	I2C1->D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_Wait();

	I2C1->D = u8RegisterAddress;										/* Send register address */
	I2C_Wait();

	I2C1->D = u8Data;												/* Send the data */
	I2C_Wait();

	I2C_Stop();

	delay_ms(1);
}


void I2C_WriteMultiRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, unsigned char num, unsigned char *u8Data)
{
	I2C_Start();
	I2C1->D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_Wait();

	I2C1->D = u8RegisterAddress;										/* Send register address */
	I2C_Wait();

	for (unsigned char i = 0; i < num; i++) {
		I2C1->D = u8Data[i];												/* Send the data */
		I2C_Wait();
	}

	I2C_Stop();

	delay_ms(1);
}

unsigned char I2C_ReadRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress)
{
	unsigned char result;

	I2C_Start();	          
	I2C1->D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_Wait();										

	I2C1->D = u8RegisterAddress;										/* Send register address */
	I2C_Wait();

	I2C_RepeatedStart();

	I2C1->D = (u8SlaveAddress << 1) | 0x01;							/* Send I2C device address this time with W/R bit = 1 */
	I2C_Wait();	

	I2C_EnterRxMode();
	I2C_DisableAck();

	result = I2C1->D;
	I2C_Wait();
	I2C_Stop();  
	result = I2C1->D;
	delay_ms(1);
	return result;
}

void I2C_ReadMultiRegisters(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, unsigned char n, unsigned char *r)
{
	char i;

	I2C_Start();	          
	I2C1->D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_Wait();										

	I2C1->D = u8RegisterAddress;										/* Send register address */
	I2C_Wait();

	I2C_RepeatedStart();

	I2C1->D = (u8SlaveAddress << 1) | 0x01;							/* Send I2C device address this time with W/R bit = 1 */
	I2C_Wait();	

	I2C_EnterRxMode();
	I2C_EnableAck();

	i = I2C1->D;
	I2C_Wait();

	for(i=0; i<n-2; i++) 
	{
		*r = I2C1->D;
		r++;
		I2C_Wait();
	}

	I2C_DisableAck();
	*r = I2C1->D;
	r++;
	I2C_Wait();
	I2C_Stop();
	*r = I2C1->D;
	delay_ms(1);
}


uint8_t nxp_i2c_write_addr8_data8(uint8_t addr, uint8_t data)
{
	I2C_WriteRegister(g_nxp_device_addr, addr, data);
	//	return i2c_write_write(addr, &data, 1);
	return 1;
}

uint8_t nxp_i2c_write_addr8_data32(uint8_t addr, uint32_t data)
{
	I2C_WriteMultiRegister(g_nxp_device_addr, addr, 4, (uint8_t*)&data);
	//	return i2c_write_write(addr, (uint8_t*)&data, 1);
	return 1;
}

uint8_t nxp_i2c_write_addr8_bytes(uint8_t addr, uint8_t *bytes, uint16_t byte_count)
{
	I2C_WriteMultiRegister(g_nxp_device_addr, addr, byte_count, (uint8_t*)bytes);
	//	return i2c_write_write(addr, bytes, byte_count);
	return 1;
}

uint8_t nxp_i2c_read_addr8_data8(uint8_t addr, uint8_t *data)
{
	*data = I2C_ReadRegister(g_nxp_device_addr, addr);
	return 1;
}

uint8_t nxp_i2c_read_addr8_data16(uint8_t addr, uint16_t *data)
{
	I2C_ReadMultiRegisters(g_nxp_device_addr, addr, 2, (uint8_t*)data);
	return 1;
}

uint8_t nxp_i2c_read_addr8_data32(uint8_t addr, uint32_t *data)
{
	I2C_ReadMultiRegisters(g_nxp_device_addr, addr, 4, (uint8_t*)data);
	return 1;
}

uint8_t nxp_i2c_read_addr8_bytes(uint8_t addr, uint8_t *bytes, uint16_t byte_count)
{
	I2C_ReadMultiRegisters(g_nxp_device_addr, addr, byte_count, (uint8_t*)bytes);
	return 1;
}
