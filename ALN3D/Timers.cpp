/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

#include "ALN3D.h"

// erreur d'overflow
bool timers_overflow = false;

// pointeur
int timer_pointer = 0;

// ms timer period
MilliSec_t timer_period;

// timers register
Timer_t TIMERS[MAX_TIMERS];

// retourne l'erreur courante
bool getTimersError(void)
{
	return timers_overflow;
}

// ajoute un timer
SSigned_t add_timer(Event_t e, MilliSec_t timeout, bool enable, bool one_time)
{
	if (timers_overflow)
		return -1;
		
	if (timer_pointer < MAX_TIMERS && !timers_overflow)
	{
		Timer_t timer = {e, timeout, timeout, enable, one_time};
		TIMERS[timer_pointer] = timer;
		return timer_pointer++;
	}
	else
	{
		timers_overflow = true;
		return -1;
	}
}

// déphase le timer, avant initialisation
void timer_offset(Tiny_t i, MilliSec_t offset)
{
	TIMERS[i].remains -= offset % TIMERS[i].timeout;
}

// met en place le timer principale
void initialize_timers(MilliSec_t period)
{
	MsTimer2::set(period, /* void *callback(void) */ iter_timers);
	MsTimer2::start();

	timer_period = period;
}

// modifie le timeout
void set_timeout(Tiny_t i, MilliSec_t timeout, bool update_remains)
{
	if (update_remains)
		TIMERS[i].remains += timeout - TIMERS[i].timeout;

	TIMERS[i].timeout = timeout;
}

// on change le paramètre one_time
void call_once(Tiny_t i)
{
	TIMERS[i].one_time = true;
}

// vide le remains
void end_timeout(Tiny_t i)
{
	TIMERS[i].remains = 0;
}

// reset le timer
void reset_timer(Tiny_t i)
{
	TIMERS[i].remains = TIMERS[i].timeout;
}

// active le timer
void enable_timer(Tiny_t i)
{
	TIMERS[i].enable = true;
}

// désactive le timer
void disable_timer(Tiny_t i)
{
	TIMERS[i].enable = false;
}

// iteration sur la liste des timers
void iter_timers(void)
{
	// bloque les interruptions
	noInterrupts();

	// pour chaque timer
	for (int i = 0; i < timer_pointer; i++)
	{
		if (!TIMERS[i].enable)
			continue;
		
		TIMERS[i].remains -= timer_period;

		// on regarde si le remain est à zero
		if (TIMERS[i].remains <= 0)
		{

#if enabled_backapp(ANALYSER)

			timers_expired++;

#endif

			// dans ce cas on lance/déclenche l'évènement
			event_queue(TIMERS[i].e);

			// on remet le timer à sa position initiale
			TIMERS[i].remains = TIMERS[i].timeout ; // + GAP = TIMERS[i].remains; // qui correspond au temps perdu dans la boucle

			// si le timer ne doit être exécuté qu'une fois, on le désactive
			if (TIMERS[i].one_time)
				TIMERS[i].enable = false;
		}
	}

	// on réactive les interruptions
	interrupts();
}

void stop()
{
	MsTimer2::stop();
}

void start()
{
	MsTimer2::start();
}


void debug_timers(HardwareSerial *ser)
{
	for (int i = 0; i < timer_pointer; i++)
	{
		ser->print("Event : ");
		ser->print(int(TIMERS[i].e));
		ser->print("\ttimout");
		ser->print(TIMERS[i].timeout);
		ser->print("\tremains:");
		ser->print(TIMERS[i].remains);
		ser->print("\tenabled:");
		ser->print(TIMERS[i].enable);
		ser->print("\teonetime:");
		ser->println(TIMERS[i].one_time);
	}
}

/*******************************/
/** TIMERS ATTACHED FUNCTIONS **/
/*******************************/


Pin_t pulse_pin;

Tiny_t pulse_timer;

bool pulse_function_available = true;

bool generate_pulse(Pin_t pin, MilliSec_t duration)
{
	// si la fonction est disponible
	if (pulse_function_available)
	{
		// fonction indisponible
		pulse_function_available = false;

		// si la fonction n'a jamais été appelée
		if (!pulse_pin)
		{
			// nouvel évènemement
			register_event(EVENT_PULSE_GENERATING, pulse_callback);

			// désactivé, one time timer
			pulse_timer = add_timer(EVENT_PULSE_GENERATING, duration, false, true);
		}
		else
		{
			// on modifie la durée
			set_timeout(pulse_timer, duration);
		}

		// pin
		pulse_pin = pin;

		// état haut
		digitalWrite(pin, HIGH);

		// on active
		enable_timer(pulse_timer);

		return true;
	}

	return false;
}

void pulse_callback(void)
{
	// état bas
	digitalWrite(pulse_pin, LOW);

	// disponible
	pulse_function_available = true;
}


/*******************************/
/** TIMER1, TIMER3, ETC... *****/
/*******************************/


// timer 1
#if defined(TIMSK1) and defined(Timer1)
Event_t timer1_event;

void setTimer1(LongMicroSec_t timeout, Event_t e)
{
	timer1_event = e;
	Timer1.initialize(timeout);
	Timer1.attachInterrupt(trigger_timer1_event);
}

void trigger_timer1_event()
{
	event_queue(timer1_event);
}
#endif


// Arduino Mega Only : Timer3
#if defined(TIMSK3) and defined(Timer3)

// event rataché au timer3 (ArduinoMega)
Event_t timer3_event = EVENT_NULL;

// met en place le timer 3
void setTimer3(unsigned long timeout, Event_t e)
{
	timer3_event = e;
	Timer3.initialize(timeout);
	Timer3.attachInterrupt(trigger_timer3_event);
}

// event trigger du timer 3
void trigger_timer3_event(void)
{
	event_queue(timer3_event);
}

#endif
