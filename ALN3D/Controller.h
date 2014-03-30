/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

#ifndef Controller_h
#define Controller_h

/**
 * Fonction de setup
 * author, synchro, serial_obs = EVENT_NULL
 */
void system_setup(bool author = true, bool synchronization = true, unsigned int serial_obs = EVENT_NULL, Event_t altitude_data_event = EVENT_NULL);

/**
 *	Fonction de boucle
 */
void system_loop();

// on affiche les données de vol
void SerialDisplayData(void);


#endif
