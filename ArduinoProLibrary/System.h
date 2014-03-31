
/*
 * System.h
 *
 *  Created on: 13 janv. 2014
 *      Author: Lucas
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
 * On applique la rapport cyclique aux moteurs
 */
void apply_motors_duty(void);

/**
 * On g�re l'�tat de la led verte
 */
void manage_imu_red_led(void);

#endif /* SYSTEM_H_ */
