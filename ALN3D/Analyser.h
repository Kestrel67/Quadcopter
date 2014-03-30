/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/**
 * Surveillance de l'execution du système et de la charge du processeur,
 * identifie les erreurs, autoanalyse
 *
 *  Activation de l'analyser : ANALYSER 1
 *
 *  @need : 1 EVENT, 1 TIMER
 */

#ifndef Analyser_h
#define Analyser_h

/**
 *	Nombres d'itérations de la boucle principale par seconde (à vide)
 *	for(;;)
 *		loop_counter++;
 */
#define ARDUIMU_EMPTY_LOOP_FREQUENCY 717155

/**
 * Nombre d'itérations de boucle principale par seconde (sans évènements : attente)
 * for(;;)
 * 		loop_counter++;
 * 		dequeue_loop();
 */
#define ARDUIMU_NOTASKS_LOOP_FREQUENCY 222102

/**
 * nombre d'itérations de la boucle principale depuis la dernière analyse
 */
extern volatile Counter_t loop_counter;

/**
 * Temps processeur de fin de la fonction d'initialisation
 */
extern MilliSec_t setup_start_stop;

/**
 * Temps processeur du début de la boucle principale
 */
extern LongMicroSec_t loop_last_measurement;

/**
 * Fréquence d'éxécution de la boucle principale
 */
extern volatile HighFrequency system_frequency;

/**
 * Pourcentage d'utilisation CPU
 */
extern fPercentage_t CPU_use;

/**
 * Evènements enregistrés
 */
extern Tiny_t registered_events;

/**
 * Evènements lancés
 */
extern unsigned long events_thrown;

/**
 * Evènements traités
 */
extern unsigned long events_processed;

/**
 * Evènements perdus
 */
extern unsigned int analyser_events_overflow;

/**
 *	Commandes envoyées (par com série)
 */
extern unsigned int sended_answers;

/**
 *	Commandes reçues (par com série)
 */
extern unsigned int received_commands;

/**
 * ID du timer de l'analyse CPU
 */
extern Tiny_t CPU_analyser_timer;

/**
 * Timers expirés
 */
extern unsigned long timers_expired;

/**
 * temps passé à éxécuter des fonctions
 */
extern LongMicroSec_t busy_time;

/**
 * Fonction à appeller lors du démarrage de la fonction setup
 */
void setup_start(void);

/**
 * Fonction à appeler à la fin de la fonction setup
 */
void setup_stop(void);

/**
 * Fonction à appaler lors de la première execution de la boucle principale
 */
void loop_start();

/**
 * mise en place de la fonction d'analyse
 */
void set_CPU_analyser(MilliSec_t period = FREQUENCY_5Hz);

/**
 * Callback de l'analyseur
 */
void CPU_analyser(void);

#endif

