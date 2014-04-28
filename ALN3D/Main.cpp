/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

byte system_status = SYS_PAUSE; // on / off

void system_setup(bool author, bool synchronization, bool calibrate)
{
	// on mesure la durée d'initialisation
	setup_start();

	// leds
	pinMode(EMBEDED_LED_RED, OUTPUT);
	pinMode(EMBEDED_LED_BLUE, OUTPUT);

	digitalWrite(EMBEDED_LED_RED, HIGH);

	SPIMaster Master = SPIMaster();
	Serial.begin(SERIAL_BAUDRATE); // debug 115200, flight: 9600
	AP_init(&Master);

	MPU6000_Init(&Master);	// accel, gyro
	HMC5883L_Init();		// magn
	initialize_hc_sr04(PWM0, FREQUENCY_SAMPLE_HC_SR04, EVENT_PID_ALTITUDE);	// altitude

	PID_Init();
	PID_Manual();	// default

	set_CPU_analyser(FREQUENCY_CPU_ANALYSER);	// system analyser

	// serial command (com in) observer
	#if CMD_IN_MODE == CMD_IN_PROD
	set_serial_observer(FREQUENCY_SERIAL_OBSERVER, EVENT_SERIAL_DATA_IN);
	#else
	add_timer(EVENT_SERIAL_DATA_IN, FREQUENCY_SERIAL_OBSERVER);
	#endif

	// events
	register_event(EVENT_DYNAMIC, 			_proc_dynamic_calculation);
	register_event(EVENT_PID_ROLL_PITCH, 	_proc_dynamic_angles_PID);
	register_event(EVENT_PID_ALTITUDE, 		callback_pid_altitude);
	register_event(EVENT_SERIAL_DATA_IN, 	callback_ser_data_in);
	register_event(EVENT_SERIAL_DATA_OUT, 	_proc_com_out);
	register_event(EVENT_LED_POSITION, 		update_position_leds);

	// timers
	add_timer(EVENT_DYNAMIC, 			FREQUENCY_DYNAMIC);
	add_timer(EVENT_PID_ROLL_PITCH, 	FREQUENCY_PID_ROLL_PITCH);
	add_timer(EVENT_SERIAL_DATA_OUT, 	FREQUENCY_SERIAL_DATA_OUT);
	add_timer(EVENT_LED_POSITION, 		FREQUENCY_LED_POSITION);

	// calibration des gyroscopes, accéléromètres
	IMU_Init(calibrate);

	// auteur
	if (author)
		ALN3D_Author();

	// synchronisation SPI
	if (synchronization)
		AP_synchronization();

	// APL : blk off (previous reset)
	AP_write(APL_REG_BLK, 0);

	// état initial des moteurs
	ApplyMotorsThrottle();

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

#if enabled_backapp(ANALYSER)

		// analyser counter
		loop_counter++;

#endif

	}
}

void ChangeSystemStatus(byte status)
{
	switch(status)
	{
		// on
		case SYS_ON:
			AP_write(APL_REG_STATUS, SYS_ON);
			AP_write(APL_REG_BLK, 0);
			PID_Automatic();
			system_status = status;
			break;

		// pause / config / init
		case SYS_PAUSE:
			AP_write(APL_REG_STATUS, SYS_PAUSE);
			PID_Manual();
			system_status = status;
			break;

		// error, emergency
		case SYS_EMERGENCY:
			AP_write(APL_REG_STATUS, SYS_EMERGENCY);
			AP_write(APL_REG_BLK, 255);
			PID_Manual();
			system_status = status;
			break;

		default:
			// error
			break;
	}
}
