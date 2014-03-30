/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/**
 * Gère les timers logiciels pour éxécuter périodiquement certaines tâches
 * agis sur les évènements
 */
 
#ifndef Timers_h
#define Timers_h

/**
 * Nombre maximum de timers
 */
#define MAX_TIMERS 15

/**
 * Période du timer principale
 */
#define MAIN_TIMER_MIN_PERIOD 1 // ms = 1000Hz

/**
 * Période efficace du timer principale
 */
#define MAIN_TIMER_EFFICENT_PERIOD 2 // ms = 500Hz

/**
 * Max subtimer frequency = MAIN_TIMER_FREQUENCY / 2
 */

/**
 *	Structure d'un timer
 *	@var Event_t e //  évènement rataché au timer
 *	@var MilliSec_t timeout (ms) // période du timer
 *	@var MilliSec_t remains (ms) // temps restant avant d'éxécuter la fonction associée
 *	@var bool enable // si le timer est activé ou non
 *	@var bool one_time // si le timer est à expiration unique
 */
struct Timer_t {
	// évènement
	Event_t e;
	
	// temps du timeout
	MilliSec_t timeout;
	
	// remains
	RelativeMilliSec_t remains;
	
	// si le timer est enable ou non
	bool enable;

	// si le timer doit être arreté après ou non
	bool one_time;
};

/**
 *	Type de la structure
 */
typedef Timer_t Timer_t;

/**
 *	Indique si il y a eu une erreur d'overflow sur le timer principale (MsTimer2)
 */
extern bool timers_overflow;

/**
 *	Période du timer (en ms)
 */
extern MilliSec_t timer_period;

/**
 *	evènement rataché au timer3 sur l'ArduinoMega
 */
extern Event_t timer3_event;

/**
 *	table des timers enregistrés
 *	itération sur cette tablea
 */
extern Timer_t TIMERS[MAX_TIMERS];

/**
 *	Pointeur des timers, indique à quel emplacement ajouter le timer
 */
extern int timer_pointer;

/**
 *	Retourne true si une erreur d'overflow à eu lieu
 *	@return bool timers_overflow
 */
bool getTimersError(void);

/**
 *	Ajoute une timer à la liste d'exécution, associe un évènement
 *	@param Event_t e
 *	@param MilliSec_t timer (ms)
 *	@param bool enabled : indique si le timer est activé ou non
 *	@param bool one_time_timer : indique si le tier doit être désactivé ou non après
 *	@return retourne l'indice du timer ajouté
 */
SSigned_t add_timer(Event_t e, MilliSec_t timeout, bool enable = true, bool one_time = false);

/**
 * Déphase un timer
 * @param Tiny_t i : id du timer
 * @param MilliSec_t offset : décalage (en ms)
 *
 * !!! : à utiliser avant l'initialisation, quand les remains sont à timeout
 */
void timer_offset(Tiny_t i, MilliSec_t offset);

/**
 *	Met en place le timer princiaple
 *	@param MilliSec_t period (ms), conseillé MAIN_TIMER_MIN_PERIOD (1ms = 1000Hz)
 */
void initialize_timers(MilliSec_t period = MAIN_TIMER_MIN_PERIOD);

/**
 *	Change le timeout du timer à l'indice i
 *	@param Tiny_t i, emplacement du timer
 *	@param MilliSec_t timeout, nouveau timeout
 *	@param bool update_remains : si TRUE met à jour le remains
 */
void set_timeout(Tiny_t i, MilliSec_t timeout, bool update_remains = false);

/**
 * On change le paramètre one_time du timer, ce qui fait qu'il ne sera exécuté qu'une seule fois
 */
void call_once(Tiny_t i);

/**
 * reset le remains à 0 à l'emplacement i (appel de la callback immédiat)
 * @param Tiny_t i
 */
void end_timeout(Tiny_t i);

/**
 * 	On reset le timer, remains = timeout
 * 	@param Tiny_t i : indice du timer
 */
void reset_timer(Tiny_t i);

/**
 *	Active le timer à l'indice i
 *	@param Tiny_t i : indice du Timer
 */
void enable_timer(Tiny_t i);

/**
 *	Désactive le timer à l'indice i
 *	@param Tiny_t i : indice du Timer
 */
void disable_timer(Tiny_t i);

/**
 *	Supprime un timer à la liste d'éxécution
 *	@param Event_t e
 */
void remove_timer(Event_t e);

/**
 *	Fonction callback du timer princiaple
 *	pour chaque timer vérifie s'il doit y avoir déclenchement dévènement ou non
 *	@param void
 */
void iter_timers(void);

/**
 *	Stop temporairement les itérations du timer
 */
void stop(void);

/**
 *	Redémarre les itérations du timer
 */
void start(void);

/**
 *	Fonction de debug
 */
void debug_timers(HardwareSerial *ser = &Serial);


/*******************************/
/** TIMERS ATTACHED FUNCTIONS **/
/*******************************/

/**
 * Pin to which one the pulse will be applied
 */
extern Pin_t pulse_pin;

/**
 * Timer used for the pulse generating
 */
extern Tiny_t pulse_timer;

/**
 * If the pulse generating function is available or not
 */
extern bool pulse_function_available;
/**
 * Generate a pulse on a pin
 * @param duration : length of the pulse
 * @param pin : pin to pulse
 */
bool generate_pulse(Pin_t pin, MilliSec_t duration = 50);

/**
 * Callback function which will end the pulse
 */
void pulse_callback(void);


/*******************************/
/** TIMER1, TIMER3, ETC... *****/
/*******************************/

#if defined(TIMSK1) and defined(Timer1)
/**
 *	Evènement attaché au timer 1
 */
extern Event_t timer1_event;

/**
 *	Mise en place du timer 1
 *	@param MicroSec_t timeout
 *	@param Event_t e
 *	déclenche un évènement régulièrement toutes les timeout µs
 */
void setTimer1(LongMicroSec_t timeout, Event_t e);

/**
 *	Fonction de déclenchement de l"évènement attaché au timer 1
 */
void trigger_timer1_event();

#endif


#if defined(TIMSK3) and defined(Timer3)
// Arduino Mega Only

/**
 *	Mise en place du timer 3
 *	@param unsigned long timeout
 *	@param Event_t e
 *	déclenche un évènement régulièrement toutes les timeout µs
 */
void setTimer3(unsigned long timeout, Event_t e);

/**
 *	Fonction de déclenchement de l"évènement attaché au timer 3
 */
void trigger_timer3_event(void);

#endif


#endif
