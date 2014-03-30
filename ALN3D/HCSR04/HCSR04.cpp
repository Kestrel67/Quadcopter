#include "HCSR04.h"

HCSR04::HCSR04(unsigned char echo, unsigned char trig, unsigned char timeout) : _echo(echo), _trig(trig), _timeout(timeout * 1000)
{
	pinMode(_echo, INPUT);
	pinMode(_trig, OUTPUT);
	
	digitalWrite(_trig, LOW);
	
	Serial.println(_echo);
	Serial.println(_trig);
}

unsigned long HCSR04::getDuration(void)
{
	digitalWrite(_trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trig, LOW);
	
	return pulseIn(22, HIGH);
}

unsigned int HCSR04::getDistanceMM(void)
{
	return getDuration() / 5.88;
}

float HCSR04::getDistance(void)
{
	return getDuration() / 5880.0;
}
