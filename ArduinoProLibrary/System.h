/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

/**
 * statut du syst�me
 */
extern uint8_t system_status;

/**
 * Initialisation du syst�me
 */
void system_setup(bool synchronization = true);

/**
 * Boucle d'execution du syst�me
 */
void system_loop(void);

/**
 * Le syst�me est en pause
 */
void system_pause(void);

/**
 * le syst�me est en �tat d'urgence
 */
void system_emergency(void);

/**
 * On applique la rapport cyclique aux moteurs
 */
void apply_motors_duty(void);

/**
 * On g�re l'�tat de la led verte
 */
void manage_imu_red_led(void);

#endif /* SYSTEM_H_ */
