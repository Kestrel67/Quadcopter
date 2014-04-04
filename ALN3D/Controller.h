/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef Controller_h
#define Controller_h

/**
 * status du système
 */
extern byte system_status;

/**
 * Fonction de setup
 * author, synchro, serial_obs = EVENT_NULL
 */
void system_setup(bool author = true, bool synchronization = true);

/**
 *	Fonction de boucle
 */
void system_loop();


// on affiche les données de vol
void SerialDisplayData(void);


#endif
