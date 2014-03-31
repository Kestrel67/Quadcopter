/*
 * IO.cpp
 *
 *  Created on: 13 janv. 2014
 *      Author: Lucas
 */

#include "ArduinoProLibrary.h"

void IO_init(void)
{
	// LED
	pinMode(LED_RED, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);

	// set led status, on éteint les 2 leds
	turn_off(LED_RED);
	turn_off(LED_GREEN);

	// ESC, motors
	pinMode(MA, OUTPUT);
	pinMode(MB, OUTPUT);
	pinMode(MC, OUTPUT);
	pinMode(MD, OUTPUT);

	// ir receiver
	// pinMode(RM_RECV_PIN, INPUT);

	// potentiometer
	pinMode(POTENCIOMETER, INPUT);
}

uint8_t read_potenciometer_value(void)
{
	return analogRead(POTENCIOMETER) >> 2;
}
