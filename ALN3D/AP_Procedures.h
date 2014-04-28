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
 * gap (angles) => motors corrections
 */
void _proc_dynamic_angles_PID(void);

/**
 * gap (altitude) => motors corrections
 */
void callback_pid_altitude(void);

/**
 * Communication Serie In
 */
void callback_ser_data_in(void);

/**
 * Communication série Out
 */
void _proc_com_out(void);

/**
 * Contrôle de sécurité (angles)
 */
void CheckAngles(void);

#endif
