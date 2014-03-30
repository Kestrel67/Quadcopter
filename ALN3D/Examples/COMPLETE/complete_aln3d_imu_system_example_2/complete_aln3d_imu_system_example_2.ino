// 1 : performance maximales | 0 : utilisation minimale
#define MAX 1

// inclusions
#include <Wire.h>
#include <SPI.h>
#include <HMC5883L.h>
#include <ALN3D.h>

// performance max ou non
#if MAX == 0
	#include "constants.h"
#else
	#include "constants_cpulimit.h"
#endif

// SPI master
SPIMaster Master = SPIMaster();

void setup(void)
{
	// ANALYSER
	setup_start_stop = millis();
	
	// SERIAL INIT
	Serial.begin(115200);
	
	// com
	Serial.println("Initialisation started");

  // pour éviter que le SPI branché vers l'AP dérange le fonctionnement des MPU6000
  pinMode(PWM0, OUTPUT);
  digitalWrite(PWM0, HIGH);
  
  // MPU & HMC init
  HMC5883L_Init();
  MPU6000_Init(&Master);
	
	// PINS & LEDS
  pinMode(EMBEDED_LED_RED, OUTPUT);
  pinMode(EMBEDED_LED_BLUE, OUTPUT);
	
	// PROCEDURE BLINKING
	// nouvelle procédure
  register_procedure(&blink);
	
	// on utilise la procédure sans la démarrer
	use_procedure(&blink, false);
  
  // initialisation du gestionnaire des procs
  initialize_procedures();
  
  // initialisation du HC-SR04
  initialize_hc_sr04(PWM1);
	
	// EVENTS
	register_event(EVENT_GET_MPU, MPU6000_Read);
	register_event(EVENT_GET_HMC, HMC5883L_Read);
	
	register_event(EVENT_CALCULATING_EULER_ANGLES, Euler_Angles);
	register_event(EVENT_CALCULATING_HEADING, Heading);
	register_event(EVENT_UPDATE_LED_POSITION, update_led_position);
	
	register_event(EVENT_DISPLAY_EULER_ANGLES, display_euler_angles);
	register_event(EVENT_DISPLAY_SENSORS, display_sensors_values);
	register_event(EVENT_DISPLAY_SYSTEM_INFORMATION, display_system_information);
	
	register_event(EVENT_SERIAL_INPUT_LISTENER, serial_input_listener);
	
	register_event(EVENT_DEBUG, debug);
	
	register_event(EVENT_LEDS_MANAGER, leds_manager);
	
	// ANALYSER
	set_CPU_analyser(FREQUENCY_CPU_ANALYSER);
	
	// TIMERS
	add_timer(EVENT_GET_MPU, FREQUENCY_GETTING_MPU_VALUES);
	add_timer(EVENT_CALCULATING_EULER_ANGLES, FREQUENCY_CALCULATING_EULER_ANGLES);
	
	add_timer(EVENT_GET_HMC, FREQUENCY_GETTING_HMC_VALUES);
	add_timer(EVENT_CALCULATING_HEADING, FREQUENCY_CALCULATING_HEADING);
	
	// default : disabled
	leds_position_timer = add_timer(EVENT_UPDATE_LED_POSITION, FREQUENCY_UPDATE_LED_POSITION, false /* disabled */);
	
	add_timer(EVENT_SERIAL_INPUT_LISTENER, FREQUENCY_SERIAL_INPUT_LISTENER);
	
  add_timer(EVENT_DISPLAY_SENSORS, FREQUENCY_DISPLAY_SENSORS_VALUES);
	add_timer(EVENT_DISPLAY_EULER_ANGLES, FREQUENCY_DISPLAYING_EULER_ANGLES);
	add_timer(EVENT_DISPLAY_SYSTEM_INFORMATION, FREQUENCY_DISPLAYING_SYSTEM_INFORMATION);
	
	leds_manager_timer = add_timer(EVENT_LEDS_MANAGER, 10000, false, true); // 10 secondes, non actif, executable une unique fois
	
	// MsTimer2 initialisation
	initialize_timers(MAIN_TIMER_MIN_PERIOD);
	
	// on force la fonction leds_manager
	event_queue(EVENT_LEDS_MANAGER);
	
	// ANALYSER
	setup_start_stop = millis() - setup_start_stop;
	
	// com
	Serial.print("Initialisation stopped : ");
	Serial.println(setup_start_stop);
}

void loop(void)
{
	loop_last_measurement = micros();
	
	for(;;)
	{
		dequeue_loop();
		
		loop_counter++;
	}
}


// functions definitions
void display_euler_angles(void)
{
	char buf[40];
	Euler_Angles_Format(buf);
	Serial.print(buf);
	Serial.print("\t");
}

void update_led_position(void)
{
	digitalWrite(EMBEDED_LED_BLUE, psi * RAD_TO_DEG >= 80);
	digitalWrite(EMBEDED_LED_RED, psi * RAD_TO_DEG <= 75);
}

void display_system_information(void)
{
	char buf[40];
	sprintf(buf, "Hz:%lu \tevents:%lu\ttimers:%lu", system_frequency, events_thrown, timers_expired);
	Serial.println(buf);
}

// on affiche certaines données des capteurs
void display_sensors_values(void)
{
  Serial.print("altitude : ");
  Serial.print(distance / 10.0);
  Serial.print("cm \t");
  return;
	
	char buf[120];
	sprintf(buf, "acc:\tX:%d\tY:%d\tZ:%d\t\tgyro:\tX:%d\tY:%d\tZ:%d\t\tmagn:\tX:%d\tY:%d\tZ:%d", Accel[X], Accel[Y], Accel[Z], Omega[X], Omega[Y], Omega[Z], Magn[X], Magn[Y], Magn[Z]);
	Serial.println(buf);
}

// receveur série
void serial_input_listener(void)
{
	if (Serial.available() > 0)
	{
		Serial.read();
		event_queue(EVENT_DEBUG);
	}
}

void debug(void)
{
	char buf[80];
	sprintf(buf, "events_count:%d\tevents_overflow:%d\ttimers_count:%d\tregistered_events:%d\toverflow:%d", events_count, events_overflow, timer_pointer, registered_events, analyser_events_overflow);
	Serial.println(buf);
}

// gère les procédures et les leds de stabilisation
void leds_manager(void)
{
	// à la fin de la procédure
	
	// si le timer des leds position n\'est pas actif on le démarre
	if (!TIMERS[leds_position_timer].enable)
	{
		// on arrete la procédure
		stop_procedure();
		
		// pour activer le timer gérant les leds
		enable_timer(leds_position_timer);
		
		// et on programme l'arret 10 secondes plus tard
		enable_timer(leds_manager_timer);
	}
	else // après les 10 secondes
	{
		// on désactive le timer des leds
		disable_timer(leds_position_timer);
		
		// on redémare la procédure
		reset_procedure(true);
	}
}

// procédures
bool blink_red(unsigned int called)
{
	digitalWrite(EMBEDED_LED_RED, called & 1);
	
	return called == 40;
}

bool blink_blue(unsigned int called)
{
	digitalWrite(EMBEDED_LED_BLUE, (called % 3) == 1);
	
	return called == 20;
}

bool blink_both(unsigned int called)
{
	digitalWrite(EMBEDED_LED_BLUE, called & 1);
	digitalWrite(EMBEDED_LED_RED, !(called & 1));
	
	return called == 30;
}

bool turnoff_leds(unsigned int called)
{
	digitalWrite(EMBEDED_LED_BLUE, LOW);
	digitalWrite(EMBEDED_LED_RED, LOW);
	
	return true;
}

bool end_proc(unsigned int called)
{	
	event_queue(EVENT_LEDS_MANAGER);
	
	return true;
}