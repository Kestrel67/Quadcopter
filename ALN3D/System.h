/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

/**
 *	Gestionnaire des évènements, procédures et tâches
 */

#ifndef System_h
#define System_h

/**
 *	nombre maximum d'évènements dans le registre des évènements
 */
#define MAX_EVENTS 20

/**
 *	Nombre maximum d'évènements dans la file
 */
#define QUEUE_SIZE 20

/**
 *	Evènement null
 */
#define EVENT_NULL -1

/**
 *	Pointeur d'écriture et de lecture
 */
extern int w_pointer, r_pointer;

/**
 *	Le nombre courant d'évènements dans la liste
 */
extern Tiny_t events_count;

/**
 *	Indique si le nombre d'évènement max dans la file a été dépacé, erreur overflow
 */
extern bool events_overflow;

/**
 *	Cache du buffer pour accélérer le traitement d'une callback associée à l'évènement event_cach
 */
extern Event_t event_cach;

/**
 *	@var callback_t array, tables associations [event => callback]
 */
extern callback_t TCB[MAX_EVENTS];

/**
 *	@var Event_t array, file des évènements
 */
extern Event_t Queue[QUEUE_SIZE];

/**
 *	On retourne le n ème élément du tableau
 *	@param unsigned int n
 */
int displayQueueN(Tiny_t n);

/**
 *	Indique s'il y a une erreur ou non
 */
bool getEventsError(void);

/** 
 *	Place l'évènement e en cache
 *	@param Event_t e
 */
void cach(Event_t e);

/**
 *	Déclenche l'évènement en cache
 *	@param bool keep, indique s'il faut vider le cache si l'évènement a été envoyé
 */
void trigger(bool keep);

/**
 *	Enregistre une association [Event_t => callback_t]
 *	@param Event_t e
 *	@param callback_t cb
 */
void register_event(Event_t e, callback_t cb);

/**
 *	Exécute une callback associée à l'evènement e
 *	@param Event_t e
 */
void execute_callback(Event_t e);

/**
 *	Appel de la fonction dequeue et éxécution de la callback si un évènement sort (dans la boucle principale)
 */
void dequeue_loop(void);

/**
 *	Récupère le premier élément non traité de la file et éxécute la callback
 *	@return Event_t
 */
Event_t event_dequeue(void);

/**
 *	Ajoute un évènement dans la file
 *	@param Event_t e
 */
void event_queue(Event_t e);

/**
 *	On vide la file des évènements
 */
void dump(void);

/**
 * On remplis la file
 */
void fill(void);

/*******************************
 *	Advances functionalities   *
 *******************************/



/***************************
 *	Manager of procedures  *
 ***************************/
 
/**
 *	tableau des pointeurs es procédures
 */
extern Procedure **PROC_TAB;
		
/**
 *	nombre de procédures
 */
extern Tiny_t proc_count;

/**
 *	Procédure en cours d'éxécution
 */
extern Procedure *current_proc;

/**
 *	id du timer attaché aux procédures
 */
extern Tiny_t proc_timer_pos;

/**
 * On initialise le gestionnaire des procédures
 */
void initialize_procedures();

/**
 *	On ajoute une procédure au registre
 */
void register_procedure(Procedure *procedure);


/** OLD **/
/**
 *	On enregistre la liste des procédures procédures
 *	@param Procedure *procedures[] : pointeur d'un tableau vers des pointeurs de procédures
 *	@param Tiny_t length, taille du tableau
 */
void register_procedures(Procedure *procedures[], Tiny_t length);

/**
 *	Fonction d'appel pour l'execution de la procédure courante
 *	- si la procédure est désactivé
 *		: on désactive le timer
 *	- sinon on éxécute la tâche courante
 *	- si cette tache est terminé
 *		: - et que la période est nulle (fonction unique)
 *			: on désactive le timer (réactivation pour une autre tache (non unique))
 *			: on rappel la fonction d'éxécution de procédure
 *		: -sinon on met à jour la période et on configure le timer
 *			pour un appel immédiat
 */
void procedure_callback(void);

/**
 *	Utilisation de la procédure proc
 *	- on stop l'ancienne, sans la supprimer
 *	- on remplace l'ancienne procédure
 *	- on lance directement la nouvelle procédure
 *	- on met à jour le timer (appel immédiat de la première tâche)
 *	@param Procedure *proc
 *	@param bool start : si true, démarre la procédure immédiatement
 *	@param bool reset : si true on reset la procédure que l'on souhaite utiliser
 */
void use_procedure(Procedure *proc, bool start = true, bool reset = false);

/**
 *	Arret de la procedure proc
 *	- procédure désactivé
 *	- la fonction procedure_callback() ce chargera de désactiver le timer
 *	@param Procedure *proc
 */
void stop_procedure(void);

/**
 *	On relance la procédure
 *	- procédure active
 *	- on redémarre le timer, remains à 0
 *	@param Procedure *proc
 */
void start_procedure(void);

/**
 *	On reset la procedure courante
 *	@param bool start, on la démarre ou non
 */
void reset_procedure(bool start = false);

#endif
