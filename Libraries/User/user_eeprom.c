#include "headfile.h"
#include "user_eeprom.h"


void eeprom_read(uint16 addr, uint8 *buf, uint8 len)
{
    iap_init();//eeprom使能
    iap_read_bytes(addr,buf,len);
    iap_idle();//eeprom失能
}
void eeprom_write(uint16 addr, uint8 *buf, uint8 len)
{


    iap_init();//eeprom使能
	  
    iap_write_bytes(addr,buf,len);
    iap_idle();//eeprom失能


}
void eeprom_erase(uint16 addr)
{
    iap_init();//eeprom使能
    iap_erase_page(addr);
    iap_idle();//eeprom失能
}