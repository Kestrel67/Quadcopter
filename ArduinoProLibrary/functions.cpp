#include "ArduinoProLibrary.h"

void APL_delay(unsigned long time)
{
	unsigned long current = millis();

	if (!(TCCR0B & (1<<WGM02)) & !(TCCR0A & (1<<WGM01)) & (TCCR0A & (1<<WGM00)))
	{
		while(millis() - current < time / 2);
	}
	else
	{
		delay(time);
	}
}

void turn_on(Pin_t led)
{
	digitalWrite(led, LOW);
}

void turn_off(Pin_t led)
{
	digitalWrite(led, HIGH);
}
