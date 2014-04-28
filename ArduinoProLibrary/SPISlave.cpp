/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ArduinoProLibrary.h"

SPISlave::SPISlave(void)
{
	// pins
	pinMode(MISO, OUTPUT);

	// prepare the first request
	SPDR = 0;

	// turn on SPI in slave mode
	SPCR |= _BV(SPE);

	// turn on interrupts
	SPCR |= _BV(SPIE);
}

byte SPISlave::get(void)
{
	return SPDR;
}

void SPISlave::reply(byte v)
{
	SPDR = v;
}
