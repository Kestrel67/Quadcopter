/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef AP_FLIGHTPROCEDURES_H_
#define AP_FLIGHTPROCEDURES_H_


/**
 * Lecture accéléromètres gyroscopes, magnétomètres
 * calcul matrice de rotation
 * angles
 */
void _proc_dynamic_calculation(void);

/**
 *	Calcul de l'angle d'azimut
 */
void _proc_azimut_calculation(void);

/**
 * gap (angles) => motors corrections
 */
void _proc_dynamic_angles_PID(void);

/**
 * On applique les changements moteurs
 */
void _proc_apply_motors_change(void);

/**
 * Altitude
 */
void _proc_altitude(void);

/**
 * gap (altitude) => motors corrections
 */
void _proc_altitude_PID(void);

/**
 * Communication Serie In
 */
void _proc_com_in(void);

/**
 * Communication série Out
 */
void _proc_com_out(void);

/**
 * on change l'état du système
 */
void _proc_system(byte status = SYS_PAUSE);

#endif
