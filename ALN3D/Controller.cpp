/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

#include "ALN3D.h"

void system_setup(bool author, bool synchronization, unsigned int serial_obs, Event_t altitude_data_event)
{
	// on mesure la durée d'initialisation
	setup_start();
	// début initialisation

	// mise en place des entrées/sorties
	IO_init();

	// led information
	digitalWrite(EMBEDED_LED_RED, HIGH);

	// SPI master
	SPIMaster Master = SPIMaster();

	// Serial Com
	Serial.begin(SERIAL_BAUDRATE); // SERIAL_BAUDRATE

	// gyro, accel
	MPU6000_Init(&Master);

	// SPI protocol with AP
	AP_init(&Master);

	// I2C com and magn
	HMC5883L_Init();

	// PID init (default : manual mode)
	PID_Init();
	PID_Manual();

	// HC-SR04 init
	initialize_hc_sr04(PWM0, FREQUENCY_SAMPLE_HC_SR04, altitude_data_event);

	// analyser
	set_CPU_analyser(FREQUENCY_CPU_ANALYSER);

	// serial observer
	if (serial_obs != 0)
		set_serial_observer(FREQUENCY_SERIAL_OBSERVER, serial_obs);

	// calibration des gyroscopes, accéléromètres
	//IMU_Init();

	// auteur
	if (author)
		ALN3D_Author();

	// synchronisation SPI
	if (synchronization)
		AP_synchronization();

	// blk off
	AP_write(APL_REG_BLK, 0);

	// effet : on fait clignoter les 2 leds pour indiquer le début du programme
	for(uint8_t blk = 0; blk < 20; blk++)
	{
		digitalWrite(EMBEDED_LED_BLUE, blk & 1);
		digitalWrite(EMBEDED_LED_RED, !(blk & 1));
		delay(50);
	}

	// we stop the 2 leds
	digitalWrite(EMBEDED_LED_BLUE, LOW);
	digitalWrite(EMBEDED_LED_RED, LOW);

	// hardware timer (last function)
	initialize_timers(FREQUENCY_SEQUENCER_TIMER);

	// init end
	setup_stop();
}

void system_loop()
{
	// start
	loop_start();

	// optimized loop
	for(;;)
	{
		// we execute the tasks
		dequeue_loop();

		// counter
		loop_counter++;
	}
}

void SerialDisplayData(void)
{
	char buf[150];
	sprintf(buf, "phi: %d  \ttheta: %d\talt: %d cm\tCPU : %lu\tev_ex: %lu\ttimers_ex: %lu\toverflow: %d", int(phi * RAD_TO_DEG), int(theta * RAD_TO_DEG), int(distance / 10.0), system_frequency, events_thrown, timers_expired, analyser_events_overflow);
	Serial.println(buf);
}
