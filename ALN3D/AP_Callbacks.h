/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef AP_CALLBACKS_H_
#define AP_CALLBACKS_H_

extern byte com_out_mode;

/**
 * Lecture accéléromètres gyroscopes, magnétomètres
 * calcul matrice de rotation
 * angles
 */
void _proc_dynamic_calculation(void);

/**
 * PID (angles) => motors corrections
 */
void _proc_dynamic_angles_PID(void);

/**
 * PID (altitude) => motors corrections
 */
void callback_pid_altitude(void);

/**
 * Communication serie In
 */
void callback_ser_data_in(void);

/**
 * Communication serie Out
 */
void _proc_com_out(void);

#endif
