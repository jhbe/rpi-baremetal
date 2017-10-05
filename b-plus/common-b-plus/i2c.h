#ifndef I2C_H
#define I2C_H

void i2c1_init(unsigned char slaveAddr);

void          i2c1_writereg(unsigned char reg, unsigned char value);
unsigned char i2c1_readreg (unsigned char reg);

void i2c1_writeregs(unsigned char reg, unsigned char *data, int length);
void i2c1_readregs (unsigned char reg, unsigned char *data, int length);

#endif
