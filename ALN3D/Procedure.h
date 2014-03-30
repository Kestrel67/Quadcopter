/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

/**
 *	Procédures:
 *	@need : 1EVENT, 1TIMER
 **/

// temp :
/************************************************************** *
 *		DEFINITION DES PROCEDURES (EN) :
 *			- landing
 *				- manual landing (assistance)
 *				- automatic landing
 *			- take-off
 *				- manual take-off (assistance)
 *				- automatic take-offs
 *			- emergency
 *				- battery emergency
 *				- communication emergency
 *				- safety emergency
 *			- autopilot
 *				- communication autopilot
 *				- crash avoiding autopilot
 *				- eve autopilot
 * ************************************************************ */

#ifndef Procedures_h
#define Procedures_h

/**
 *	nombre maximum de tâches par procédures
 */
#define MAX_TASKS_PER_PROC 20

/**
 * nombre maximum de procédures
 */
#define MAX_PROCEDURES 10

// noms des procédures
#define LANDING_PROC
#define TAKEOFF_PROC
#define EMERGENCY_PROC
#define SLEEP_PROC
#define AUTOPILOT_PROC

/**
 * callback
 * @param unsigned unt called : nombre de fois que la tâche a été exécutée
 * @return bool : true si on peut passer à la tâche suivante sinon false
 */
typedef bool (*task_func_t)(unsigned int called);

/**
 *	New Task_t structure
 */
struct Task_t {
	
	/**
	 *	fonction associée à la tâche
	 */
	task_func_t taskFunction;
	
	/**
	 *	définit la période entre 2 appelles de la fonction d'exécution de la tâche
	 */
	MilliSec_t period;
};

/**
 *	Type d'une structure
 */
typedef Task_t Task_t;

/**
 *	nombre de procédures créée (pour attribuer correctement les nouveaux id)
 */
extern Tiny_t procedures_stored;

/**
 *	Classe d'une procédure (voir la documentation)
 */
class Procedure
{
	public:
		/**
		 *	@param Task_t *taks[] : nécéssite le pointeur d'un tableau de pointeurs vers les tâches
		 *	@param Tiny_t length : nombre de tâches à définir dans la procédure
		 */
		Procedure(Task_t *tasks[], Tiny_t length);
		
		/**
		 *	renvoie l'id de la procédure
		 */
		Tiny_t id(void) const;
		
		/**
		 *	active la procédure
		 */
		void enable(void);
		void start(void); // Conventional function

		/**
		 *	désactive la procédure
		 */
		void disable(void);
		void stop(void);  // Conventional function
		
		/**
		 *	indique si la procédure est activée ou non
		 */
		bool enabled(void) const;
		
		/**
		 *	On remet la procedure à 0
		 */
		void reset(void);
		
		/**
		 * On remet la procédure à 0 et on la réactive
		 */
		void restart(void);

		/**
		 *	Execute la tâche courante et passe à la suivante si néscéssaire
		 *	@param return bool
		 *	retourne true si la procédure passe à la tache suivante
		 *	returne false si ce n'est pas le cas
		 */
		bool execute(void);
		
		/**
		 *	On récupère la période d'éxécution de la tâche en cours
		 */
		MilliSec_t getPeriod(void) const;
		
	private:
		/**
		 *	pointeur vers le tableau de pointeur des tâches
		 */
		Task_t **_tasks;
		
		/**
		 *	position du curseur d'exécution
		 */
		Tiny_t _pos;
		
		/**
		 *	nombre de tâches dans la procédure
		 */
		Tiny_t _length;
		
		/**
		 *	id de la procédure
		 */
		Tiny_t _id;
		
		/**
		 *	nombre de fois que la tâche courante a été appelée
		 */
		unsigned int _called;
		
		/**
		 *	activité de la procédure
		 */
		bool _enabled;
};

#endif
