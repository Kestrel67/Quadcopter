/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

void system_setup(bool conf, bool synchronization, bool calibrate, bool analyser, bool manager)
{
	// time start
	setup_start();

	/*********** OUTPUTS ***********/
	pinMode(EMBEDED_LED_RED, OUTPUT);
	pinMode(EMBEDED_LED_BLUE, OUTPUT);

	digitalWrite(EMBEDED_LED_RED, HIGH);

	/*********** COM ***********/
	SPIMaster Master = SPIMaster();
	Serial.begin(SERIAL_BAUDRATE); // debug 115200, flight: 9600
	AP_init(&Master);

	/*********** COMPONENTS ***********/
	MPU6000_Init(&Master);	// accel, gyro
	HMC5883L_Init();		// compass

	/*********** EVENTS ***********/
	register_event(EVENT_DYNAMIC, 			_proc_dynamic_calculation);
	register_event(EVENT_HMC5883L, 			HMC5883L_Read);
	register_event(EVENT_PID_ROLL_PITCH, 	_proc_dynamic_angles_PID);
	register_event(EVENT_PID_ALTITUDE, 		callback_pid_altitude);
	register_event(EVENT_SERIAL_DATA_IN, 	callback_ser_data_in);
	register_event(EVENT_SERIAL_DATA_OUT, 	_proc_com_out);
	register_event(EVENT_LED_POSITION, 		update_position_leds);

	/*********** TIMERS ***********/
	add_timer(EVENT_DYNAMIC, 			FREQUENCY_DYNAMIC);
	add_timer(EVENT_PID_ROLL_PITCH, 	FREQUENCY_PID_ROLL_PITCH);
	add_timer(EVENT_SERIAL_DATA_OUT, 	FREQUENCY_SERIAL_DATA_OUT);
	add_timer(EVENT_LED_POSITION, 		FREQUENCY_LED_POSITION);
	add_timer(EVENT_HMC5883L, 			FREQUENCY_GET_HMC5883L);

	/*********** ALTIMETER ***********/
	initialize_hc_sr04(PWM0, FREQUENCY_SAMPLE_HC_SR04, EVENT_PID_ALTITUDE);

	/*********** COM IN ***********/
	#if CMD_IN_MODE == CMD_IN_PROD
	set_serial_observer(FREQUENCY_SERIAL_OBSERVER, EVENT_SERIAL_DATA_IN);
	#else
	add_timer(EVENT_SERIAL_DATA_IN, FREQUENCY_SERIAL_OBSERVER);
	#endif

	/*********** ANALYSER + MANAGER ***********/
	if (analyser)
	{
		set_CPU_Analyser(FREQUENCY_ANALYSER);	// ANALYSER

		if (manager)	set_CPU_Manager(FREQUENCY_MANAGER);		// MANAGER
	}

	/*********** PID ***********/
	PID_Init();
	PID_Manual();	// default

	/*********** IMU ***********/
	IMU_Init(calibrate);

	/*********** SPI ***********/
	if (synchronization)
		AP_synchronization();

	// APL : blk off (previous reset)
	AP_write(APL_REG_BLK, 0);

	// état initial des moteurs
	ApplyMotorsThrottle();

	/*********** AUTHOR ***********/
	if (conf)
		ser_display_IMU_conf();

	digitalWrite(EMBEDED_LED_RED, LOW);

	/*********** SYSTEM ***********/
	// MSTimer 2 : 1000Hz (last function)
	initialize_timers(FREQUENCY_SEQUENCER_TIMER);

	// time end
	setup_stop();
}

void system_loop()
{
	// time start
	loop_start();

	for(;;)
	{
		dequeue_loop();

#if enabled_backapp(ANALYSER)

		// analyser counter
		loop_counter++;

#endif
	}
}
