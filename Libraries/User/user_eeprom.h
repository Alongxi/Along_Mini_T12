#ifndef USER_EEPROM_H
#define USER_EEPROM_H
#include "headfile.h"

void eeprom_read(uint16 addr, uint8 *buf, uint8 len);
void eeprom_write(uint16 addr, uint8 *buf, uint8 len);
void eeprom_erase(uint16 addr);

#endif