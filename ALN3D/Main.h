/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef Main_h
#define Main_h

/**
 * status du système
 */
extern byte system_status;

/**
 * Fonction de setup
 * author, synchro, serial_obs = EVENT_NULL
 */
void system_setup(bool conf = true, bool synchronization = true, bool calibrate = false, bool analyser = true, bool manager = false);

/**
 *	Fonction de boucle
 */
void system_loop();

/**
 * on change l'état du système
 */
void ChangeSystemStatus(byte status = SYS_PAUSE);


#endif
