#define I2C_DisableAck()       I2C1->C1 |= I2C_C1_TXAK_MASK
#define I2C_EnableAck()        I2C1->C1 &= ~I2C_C1_TXAK_MASK
#define I2C_RepeatedStart()    I2C1->C1 |= I2C_C1_RSTA_MASK
#define I2C_EnterRxMode()      I2C1->C1 &= ~I2C_C1_TX_MASK
#define I2C_write_byte(data)   I2C1_D = data

#define I2C_Start()            I2C1->C1 |= I2C_C1_TX_MASK;\
                               I2C1->C1 |= I2C_C1_MST_MASK

#define I2C_Stop()             I2C1->C1 &= ~I2C_C1_MST_MASK;\
                               I2C1->C1 &= ~I2C_C1_TX_MASK

#define I2C_Wait()             while((I2C1->S & I2C_S_IICIF_MASK)==0) {} \
                               I2C1->S |= I2C_S_IICIF_MASK;

void I2C_WriteRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, /*unsigned*/ char u8Data);
unsigned char I2C_ReadRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress);
void I2C_ReadMultiRegisters(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, unsigned char n, unsigned char *r);


uint8_t nxp_i2c_read_addr8_data8(uint8_t addr, uint8_t *data);
uint8_t nxp_i2c_read_addr8_data16(uint8_t addr, uint16_t *data);
uint8_t nxp_i2c_read_addr8_data32(uint8_t addr, uint32_t *data);
uint8_t nxp_i2c_read_addr8_bytes(uint8_t addr, uint8_t *bytes, uint16_t byte_count);

uint8_t nxp_i2c_write_addr8_data8(uint8_t addr, uint8_t data);
uint8_t nxp_i2c_write_addr8_data32(uint8_t addr, uint32_t data);
uint8_t nxp_i2c_write_addr8_bytes(uint8_t addr, uint8_t *bytes, uint16_t byte_count);
