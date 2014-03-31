#include "ArduinoProLibrary.h"

void timer0_set_phase_correct_mode(void)
{
	bitClear(TCCR0B, WGM02);
	bitClear(TCCR0A, WGM01);
	bitSet(TCCR0A, WGM00);
}

void timer0_set_prescaler(byte prescaler)
{
	TCCR0B &= ~0x07; // TCCR0B &= B11111000;

	TCCR0B |= prescaler;
}
