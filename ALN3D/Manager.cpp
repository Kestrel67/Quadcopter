/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

/**
 * mise en place de la fonction de management
 */
void set_CPU_Manager(MilliSec_t period)
{
	register_event(EVENT_MANAGER, CPU_Manager);

	add_timer(EVENT_MANAGER, period);
}

/**
 * fonction de management
 */
void CPU_Manager(void)
{
	return; // tmp

	Manager_Debug();

	// si le processeur est quasiment ou totalement occupé

	if (CPU_use > 98.0)
	{
		// on baisse la fréquence des calculs dynamiques
		TIMERS[0].timeout += 1;
	}
}

void Manager_Debug(void)
{
	sLn();
	Serial.print("CPU_use : ");
	Serial.println(CPU_use);
	Serial.println("Ev\ttimeout\tenable");

	for (uint8_t i = 0; i < timer_pointer; i++)
	{
		Serial.print(TIMERS[i].e);
		sTab();
		Serial.print(TIMERS[i].timeout);
		sTab();
		Serial.print(TIMERS[i].enable);
		sLn();
	}
}
