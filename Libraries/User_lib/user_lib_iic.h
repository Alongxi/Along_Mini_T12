#ifndef __USER_LIB_IIC_H
#define __USER_LIB_IIC_H
#include "headfile.h"

void user_iic_write_reg(uint8 dev_add, uint8 reg, uint8 dat);
void user_iic_init();
void user_iic_delay();
#endif