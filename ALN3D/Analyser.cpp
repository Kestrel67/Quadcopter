/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include <ALN3D.h>

Counter_t loop_counter;

MilliSec_t setup_start_stop;

LongMicroSec_t loop_last_measurement;

HighFrequency system_frequency;

unsigned int sended_answers;

unsigned int received_commands;

Tiny_t registered_events;

unsigned long events_thrown;

unsigned long events_processed;

unsigned int analyser_events_overflow;

unsigned long timers_expired;

LongMicroSec_t busy_time = 0;

fPercentage_t CPU_use;

void setup_start(void)
{
	setup_start_stop = millis();
}

void setup_stop(void)
{
	setup_start_stop = millis() - setup_start_stop;
}

void loop_start()
{
	loop_last_measurement = micros();
}

void set_CPU_Analyser(MilliSec_t period)
{
	register_event(EVENT_ANALYSER, CPU_Analyser);

	add_timer(EVENT_ANALYSER, period);
}

void CPU_Analyser(void)
{
	// diff de temps (µs)
	unsigned long period = (micros() - loop_last_measurement);

	loop_last_measurement = micros();

	// freq boucle principale
	system_frequency = 1000000.0 * loop_counter / period;

	loop_counter = 0;

	// temps CPU (%)
	CPU_use = 100.0 * busy_time / period;

	busy_time = 0;
}
