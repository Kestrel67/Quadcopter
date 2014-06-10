/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

/**
 *	Pointeur d'écriture et de lecture
 */
int w_pointer = 0, r_pointer = 0;

/**
 *	Nombre dévènements dans la file
 */
Tiny_t events_count = 0;

/**
 *	Indique s'il y a eu un overflow (file pleine)
 */
bool events_overflow = false;

/**
 *	Cache du buffer pour accélérer le déclenchement d'un évènement
 */
Event_t event_cach = EVENT_NULL;

/**
 *	@var callback_t array, table d'associations [event => callback]
 */
callback_t TCB[MAX_EVENTS];

/**
 *	@var Event_t array, file des évènements
 */
Event_t Queue[QUEUE_SIZE];

/**
 *	On retourne le n ème élément du tableau
 */
int displayQueueN(Tiny_t n)
{
	if (n < QUEUE_SIZE)
		return Queue[n];
	return -1;
}

/**
 *	Indique s'il y a eu overflow ou non
 */
bool getEventsError(void)
{
	return events_overflow;
}

/** 
 *	Place l'évènement e en cache
 */
void cach(Event_t e)
{
	event_cach = e;
}

/**
 *	Déclenche l'évènement en cache
 *	@param bool keep, indique s'il faut vider le cache si l'évènement a été envoyé
 */
void trigger(bool keep = true)
{
	if (event_cach != EVENT_NULL)
	{
		event_queue(event_cach);
		
		if (!keep) event_cach = EVENT_NULL;
	}
}

/**
 *	Enregistre une association [Event_t => callback_t]
 *
 *	Si l'évènement est le EVENT 4, il sera stocké dans le tableau TCB à la clé 4 - 1 = 3
 *	@param Event_t e
 *	@param callback_t cb
 */
void register_event(Event_t e, callback_t cb)
{
	if (e > EVENT_NULL)
	{
		TCB[e] = cb;

#if enabled_backapp(ANALYSER)

		registered_events++;

#endif
	}

}

/**
 *	Exécute une callback associé à l'evènement e
 *	@param Event_t e
 */
void execute_callback(Event_t e)
{
	if (TCB[e])
		TCB[e]();
}

/**
 *	Appel de la fonction en boucle dans la boucle principale
 */
void dequeue_loop(void)
{
// analyse des évènements
#if enabled_backapp(ANALYSER)

	unsigned long last_process_time = micros();

#endif

	Event_t e = event_dequeue();

	if (e != EVENT_NULL)
	{
		execute_callback(e);
	}


// analyse des évènements
#if enabled_backapp(ANALYSER)

	busy_time += micros() - last_process_time;

#endif
}

/**
 *	éxécute la callback de l'évènement à traiter
 */
Event_t event_dequeue(void)
{
	Event_t e;
	
	// on masque les interruptions
	noInterrupts();
	
	// si la file possède au moins un élément et qu'il existe un évènement à l'emplacement du pointeur de lecture
	if (events_count-- && Queue[r_pointer] != EVENT_NULL)
	{
		// on le récupère
		e = Queue[r_pointer];

		// on suprime l'emplacement
		Queue[r_pointer++] = EVENT_NULL;

		// on met à jour le pointeur pour l'itération suivante
		r_pointer %= QUEUE_SIZE;

// analyse des évènements
#if enabled_backapp(ANALYSER)

		events_processed++;

#endif
	}
	else
	{
		// si events_count == 0 ou si le pointeur est positionné sur un élément null
		e = EVENT_NULL;
		
		// on reset les pointeurs
		r_pointer = w_pointer = events_count = 0;
	}
	
	// s'il y a eu un overflow, on signal qu'une nouvelle place est disponible dans la file
	events_overflow = false;

	// on démasque les interruptions
	interrupts();
		
	return e;
}

/**
 *	Ajoute un évènement dans la file
 *	Inutile de masquer les interruptions car seul la fonction dequeue_loop() modifie ces variables
 *	Cette fonction n'est executé que toute seuls (les autres interruptions sont indépendantes de ces variables)
 *	@param Event_t e
 */
void event_queue(Event_t e)
{
	if (events_overflow)
		return;
	
	// si il reste 1 emplacement libre dans la file
	if (events_count++ < QUEUE_SIZE)
	{
		// on ajoute l'évènements
		Queue[w_pointer++] = e;
		
		// mise à jour du pointeur
		w_pointer %= QUEUE_SIZE;

// analyse des évènements
#if enabled_backapp(ANALYSER)

		events_thrown++;

#endif

	}
	else
	{
		// sinon il y a une erreur de pointeur
		events_overflow = true;

#if enabled_backapp(ERRORS_MANAGER)

			new_error();

#endif

// analyse des évènements
#if enabled_backapp(ANALYSER)

	analyser_events_overflow++;

#endif
	}
}

/**
 *	On vide la file
 */
void dump(void)
{
	noInterrupts();
	
	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		Queue[i] = EVENT_NULL;
	}
	
	w_pointer = r_pointer = events_count = 0;
	
	interrupts();
}

/**
 * On remplis la file
 */
void fill(void)
{
	// ... //
}

/**************************
 *	Manager of procedures *
 **************************/

// à revoir !

Procedure **PROC_TAB;

Tiny_t proc_count;

Procedure *current_proc;

Tiny_t proc_timer_pos;

void initialize_procedures()
{
	// on enregistre l'évènement attaché aux procédures
	register_event(EVENT_PROCEDURE, procedure_callback);

	// on récupère la position du timer utilisé pour les procédures
	// on le désactive pour le moment
	proc_timer_pos = add_timer(EVENT_PROCEDURE, 0, false);
}

void register_procedure(Procedure *procedure)
{
	// on stocke sa référence à l'emplacement de l'id
	PROC_TAB[procedure->id()] = procedure;

	proc_count++;
}
 

/** OLD **/
void register_procedures(Procedure *procedures[], Tiny_t length)
{
	// on enregistre l'évènement attaché aux procédures
	register_event(EVENT_PROCEDURE, procedure_callback);
	
	// on récupère la position du timer utilisé pour les procédures
	// on le désactive pour le moment
	proc_timer_pos = add_timer(EVENT_PROCEDURE, 0, false);
	
	// on enregistre le nombre de procédures
	proc_count = length;
	
	// pour chaque procédure, on la place dans la table en fonction de son id
	for (Tiny_t i = 0; i < length; i++)
	{
		// on stocke sa référence à l'emplacement de l'id
		PROC_TAB[procedures[i]->id()] = procedures[i];
	}
}

// callback appelée par le timer pour exécuter la procédure
void procedure_callback(void)
{
	// si la procédure courante est activé
	if (current_proc->enabled())
	{
		// on éxécute la tâche
		if (current_proc->execute()) // s'il y a changement de tâche
		{
			// si la période est != de 0
			if (current_proc->getPeriod())
			{

				// on met à jour le timeout
				set_timeout(proc_timer_pos, current_proc->getPeriod(), false);

				// on met le remains à 0 (appel de la callback immédiat)
				end_timeout(proc_timer_pos);

				// on force l'activation du timer ou il a été désactivé pour un appel unique
				enable_timer(proc_timer_pos);
			}
			else
			{
				// si la période est nulle, appel immédiat et unique
				disable_timer(proc_timer_pos);
				
				// on rappel la même fonction pour éxécuter cette fonction dans l'immédiat
				procedure_callback();
			}
		}
	}
	else
	{
		// si la dernière tâche à été appelée et que maintenant la procédure est désactivée, on désactive le timer
		disable_timer(proc_timer_pos);
	}
}

// on utilise une nouvelle procédure
void use_procedure(Procedure *proc, bool start, bool reset)
{
	// si la procédure est la même on ne fait rien
	if (current_proc == proc)
		return;

	// si il y a une ancienne procédure
	if (current_proc)
	
		// on la stop
		stop_procedure();
	
	// on la remplace (sans la perdre car pointeur)
	current_proc = proc;

	// on reset la procédure sans la remettre à 0
	if (reset)
		reset_procedure(false);

	// on lance la procédure
	if (start)
		start_procedure();
}

// mise en suspension d'un timer (automatique)
void stop_procedure(void)
{	
	// on désactive la procédure
	current_proc->disable();
}

// on relance la procédure
void start_procedure(void)
{
	// on active la procédure
	current_proc->enable();

	// on force l'activation du timer ou il a été désactivé pour un appel unique
	enable_timer(proc_timer_pos);
}

// on remet à zero la procédure courante (reset)
void reset_procedure(bool start)
{
	// on reset
	current_proc->reset();

	// on met à jour le timeout
	set_timeout(proc_timer_pos, current_proc->getPeriod(), false);

	// on met le remains à 0 (appel de la callback immédiat)
	end_timeout(proc_timer_pos);

	// on redémarre la procédure dans l'immédiat si elle a été arrêtée
	if (start)
		start_procedure();
}
