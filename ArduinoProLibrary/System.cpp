/*
 * System.cpp
 *
 *  Created on: 13 janv. 2014
 *      Author: Lucas
 */

#include "ArduinoProLibrary.h"

uint8_t system_status = 0;

unsigned long last_serial_display;

void system_setup(bool synchronization)
{
	// timer0 à 500Hz (delay --> APL_delay)
	timer0_set_phase_correct_mode();

	// SPI slave mode
	SPISlave ArduinoPro = SPISlave();

#if APL_SERIAL_DISPLAY == 1
	// debug
	Serial.begin(APL_DEFAULT_SERIAL_BAUDRATE);
#endif

	// input outputs
	IO_init();

	// esc initialisation
	esc_init(ESC_FAST_INIT);

	// synchronisation SPI
	if (synchronization)
		SPI_synchronization();

	// led effect : system on
	turn_off(LED_RED);
}

void system_loop(void)
{
	for(;;)
	{
		if (reg_updated(APL_REG_STATUS))
			system_status = reg_read(APL_REG_STATUS);

		// IMU mode
		if (system_status == SYS_ON)
		{
			turn_on(LED_GREEN);

			apply_motors_duty();

			manage_imu_red_led();

#if APL_SERIAL_DISPLAY == 1

			// on affiche les valeurs des moteurs à une fréquence de 25Hz
			if (millis() - last_serial_display > FREQUENCY_25Hz)
			{
				serial_display_motors_throttle();
				last_serial_display = millis();
			}
#endif
		}
		else
		{
			system_pause();
		}
	}
}

void system_pause(void)
{
	turn_off(LED_GREEN);

	stop_motors();

#if APL_SERIAL_DISPLAY == 1
	Serial.print("wait ... : ");
	Serial.println(system_status);
#endif

	APL_delay(1000);
}

void apply_motors_duty(void)
{
	// moteur A
	if (reg_updated(APL_REG_MOTORA))
		THRUST(MA, reg_read(APL_REG_MOTORA));

	// moteur B
	if (reg_updated(APL_REG_MOTORB))
		THRUST(MB, reg_read(APL_REG_MOTORB));

	// moteur C
	if (reg_updated(APL_REG_MOTORC))
		THRUST(MC, reg_read(APL_REG_MOTORC));

	// moteur D
	if (reg_updated(APL_REG_MOTORD))
		THRUST(MD, reg_read(APL_REG_MOTORD));
}

void manage_imu_red_led(void)
{
	if (reg_updated(APL_REG_BLK))
	{
		switch (reg_read(APL_REG_BLK))
		{
		// off
		case BLK_LED_OFF:
			turn_off(LED_RED);
			break;

		// on
		case BLK_LED_ON:
			turn_on(LED_RED);
			break;

		// toggle = default
		case BLK_LED_TOGGLE:
		default:
			digitalWrite(LED_RED, !digitalRead(LED_RED));
			break;

		}
	}
}
