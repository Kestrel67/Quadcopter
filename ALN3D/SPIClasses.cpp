/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

/*
 * SPI.cpp
 *
 *  Created on: 13 janv. 2014
 *      Author: Lucas
 */

#include "ALN3D.h"

#include <SPI.h>

SPIMaster::SPIMaster(void)
{
  SPI.begin();

  SPI.setClockDivider(SPI_CLOCK_DIVIDER);

  pinMode(MISO, INPUT);
}

void SPIMaster::addSlave(Pin_t SS_pin)
{
	pinMode(SS_pin, OUTPUT);

	digitalWrite(SS_pin, HIGH);
}

byte SPIMaster::send(Pin_t SS_pin, byte cmd)
{
	digitalWrite(SS_pin, LOW);

	byte ret = SPI.transfer(cmd);

	digitalWrite(SS_pin, HIGH);

	return ret;
}

SPISlave::SPISlave()
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

void SPISlave::reply(byte msg)
{
	SPDR = msg;
}
