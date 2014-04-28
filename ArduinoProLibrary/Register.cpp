/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ArduinoProLibrary.h"

byte REG[APL_MAX_REGISTERS];
bool REG_UPDATED[APL_MAX_REGISTERS];

void reg_write(Reg_t reg, byte value)
{
	if (reg < APL_MAX_REGISTERS and REG[reg] != value)
	{
		REG[reg] = value;
		REG_UPDATED[reg] = 1;
	}
}

byte reg_read(Reg_t reg)
{
	if (reg < APL_MAX_REGISTERS)
	{
		REG_UPDATED[reg] = 0;
		return REG[reg];
	}
}

bool reg_updated(Reg_t reg)
{
	return (bool) (reg < APL_MAX_REGISTERS and REG_UPDATED[reg]);
}

void reg_debug(HardwareSerial *ser)
{
	ser->println("debug start : ");
	for(uint8_t reg = 0; reg < APL_MAX_REGISTERS; reg++)
	{
		ser->print(reg);
		ser->print(" : ");
		ser->println(REG[reg]);
	}
	ser->println("end");
}

