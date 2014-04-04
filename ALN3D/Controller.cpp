/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

byte system_status = SYS_PAUSE; // on / off

void system_setup(bool author, bool synchronization)
{
	// on mesure la durée d'initialisation
	setup_start();

	// mise en place des entrées/sorties
	IO_init();

	digitalWrite(EMBEDED_LED_RED, HIGH);

	SPIMaster Master = SPIMaster();
	Serial.begin(SERIAL_BAUDRATE); // debug 115200, flight: 9600
	AP_init(&Master);

	MPU6000_Init(&Master);	// accel, gyro
	HMC5883L_Init();		// magn
	initialize_hc_sr04(PWM0, FREQUENCY_SAMPLE_HC_SR04, EVENT_PID_ALTITUDE);	// altitude

	PID_Init();
	PID_Manual();	// default

	phi_setpoint = theta_setpoint = psi_setpoint = 0;	// default setpoint
	altitude_control = 50;

	set_CPU_analyser(FREQUENCY_CPU_ANALYSER);	// system nalyser

	// serial observer
	set_serial_observer(FREQUENCY_SERIAL_OBSERVER, EVENT_SERIAL_DATA_IN);

	// events
	register_event(EVENT_DYNAMIC, 			_proc_dynamic_calculation);
	register_event(EVENT_PID_ROLL_PITCH, 	_proc_dynamic_angles_PID);
	register_event(EVENT_PID_ALTITUDE, 		_proc_altitude);
	register_event(EVENT_SERIAL_DATA_IN, 	_proc_com_in);
	register_event(EVENT_SERIAL_DATA_OUT, 	_proc_com_out);
	register_event(EVENT_LED_POSITION, 		update_position_leds);

	// timers
	add_timer(EVENT_DYNAMIC, FREQUENCY_DYNAMIC);
	add_timer(EVENT_PID_ROLL_PITCH, FREQUENCY_PID_ROLL_PITCH);
	add_timer(EVENT_SERIAL_DATA_OUT, FREQUENCY_SERIAL_DATA_OUT);
	add_timer(EVENT_LED_POSITION, FREQUENCY_LED_POSITION);

	// calibration des gyroscopes, accéléromètres
	IMU_Init();

	// auteur
	if (author)
		ALN3D_Author();

	// synchronisation SPI
	if (synchronization)
		AP_synchronization();

	// APL : blk off
	AP_write(APL_REG_BLK, 0);

	// état initial des moteurs
	AP_ApplyMotorsThrottle();

	// red led
	digitalWrite(EMBEDED_LED_RED, LOW);

	initialize_timers(FREQUENCY_SEQUENCER_TIMER);	// MSTimer 2 : 1000Hz (last function)

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

		// analyser counter
		loop_counter++;
	}
}

void SerialDisplayData(void)
{
	char buf[150];
	sprintf(buf, "phi: %d  \ttheta: %d\talt: %d cm\tCPU : %lu\tev_ex: %lu\ttimers_ex: %lu\toverflow: %d", int(phi * RAD_TO_DEG), int(theta * RAD_TO_DEG), int(distance / 10.0), system_frequency, events_thrown, timers_expired, analyser_events_overflow);
	Serial.println(buf);
}
