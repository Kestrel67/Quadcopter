
/*
 * System.h
 *
 *  Created on: 13 janv. 2014
 *      Author: Lucas
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

/**
 * statut du système
 */
extern uint8_t system_status;

/**
 * Initialisation du système
 */
void system_setup(bool synchronization = true);

/**
 * Boucle d'execution du système
 */
void system_loop(void);

/**
 * Le système est en pause
 */
void system_pause(void);

/**
 * On applique la rapport cyclique aux moteurs
 */
void apply_motors_duty(void);

/**
 * On gère l'état de la led verte
 */
void manage_imu_red_led(void);

#endif /* SYSTEM_H_ */
