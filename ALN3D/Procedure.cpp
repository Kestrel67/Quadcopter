/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

Tiny_t procedures_stored = 0;

Procedure::Procedure(Task_t *tasks[], Tiny_t length) 
	: _tasks(tasks), 
	_pos(0), 
	_length(length), 
	_id(++procedures_stored), 
	_called(0), 
	_enabled(false)
{}

void Procedure::enable(void)
{
	_enabled = true;
}

void Procedure::start(void)
{
	_enabled = true;
}

void Procedure::disable(void)
{
	_enabled = false;
}

void Procedure::stop(void)
{
	_enabled = false;
}

bool Procedure::enabled(void) const
{
	return _enabled;
}

Tiny_t Procedure::id(void) const
{
	return _id;
}

void Procedure::reset(void)
{
	_pos = _called = 0;
}

void Procedure::restart(void)
{
	_pos = _called = 0;
	_enabled = true;
}

MilliSec_t Procedure::getPeriod(void) const
{
	return _tasks[_pos]->period;
}

bool Procedure::execute(void)
{
	// si la tache retourne true => la tache est terminé
	// on passe à la suivante
	if (_tasks[_pos]->taskFunction(++_called))
	{
		// on incrémente le pointeur
		_pos++;
		
		// on remet le called à 0
		_called = 0;
		
		// si il n'y a plus de tâche
		if (_pos == _length)
		{
			// on désactive la procédure
			disable();
			
			// et on la reset
			reset();
		}
		
		// on retourne true si la tâche a changée
		return true;
	}
	
	// sinon false
	return false;
}
