/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
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
	for(;;) // no-delay loop (! emergency, special case)
	{
		// system status
		if (reg_updated(APL_REG_STATUS))
			system_status = reg_read(APL_REG_STATUS);

		// IMU mode
		if (system_status == SYS_ON) // ON
		{
			turn_on(LED_GREEN);

			apply_motors_duty();

			manage_imu_red_led();

#if APL_SERIAL_DISPLAY == 1
			// on affiche les valeurs des moteurs
			if (millis() - last_serial_display > APL_SERIAL_DISPLAY_FREQUENCY)
			{
				serial_display_motors_throttle();
				last_serial_display = millis();
			}
#endif
		}
		else if (system_status == SYS_PAUSE) // PAUSE
		{
			system_pause();

			manage_imu_red_led();

#if APL_SERIAL_DISPLAY == 1
			// on affiche un message d'attente
			if (millis() - last_serial_display > APL_SERIAL_DISPLAY_FREQUENCY)
			{
				Serial.print("wait ... : ");
				Serial.println(system_status);
				last_serial_display = millis();
			}
#endif
		}
		else // EMERGENCY
		{
			system_emergency();

#if APL_SERIAL_DISPLAY == 1
			// erreur !
			if (millis() - last_serial_display > APL_SERIAL_DISPLAY_FREQUENCY)
			{
				Serial.println("!!!!!!! emergency !!!!!!!");
				last_serial_display = millis();
			}
#endif
		}
	}
}

void system_pause(void)
{
	turn_off(LED_GREEN);
	turn_off(LED_RED);

	stop_motors();
}

void system_emergency(void)
{
	stop_motors();
	APL_delay(40);
	reverse(LED_RED);
	turn_off(LED_GREEN);
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

		// toggle = default
		case BLK_LED_TOGGLE:
			reverse(LED_RED);
			break;

		// on
		case BLK_LED_ON:
		default:
			turn_on(LED_RED);
		}
	}
}
