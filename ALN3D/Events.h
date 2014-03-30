/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

#ifndef EVENTS_H_
#define EVENTS_H_

/**
 *	Evènement réservé aux procédures (le dernier évènement)
 */
#define EVENT_PROCEDURE MAX_EVENTS - 1

/**
 *	Evènement réservé aux procédures (l'avant dernier évènement)
 */
#define EVENT_SERIAL_OBSERVER MAX_EVENTS - 2

/**
 * Evènement reservé à l'analyseur
 */
#define EVENT_ANALYSER MAX_EVENTS - 3

/**
 * Evènement réservé à la fonction de pulse generating
 */
#define EVENT_PULSE_GENERATING MAX_EVENTS - 4

/**
 * Evènement réservé à la fonction de trigger/sample du HC-SR04
 */
#define EVENT_HC_SR04_SAMPLE MAX_EVENTS - 5

/**
 * On récupère les valeurs Accel, Gyros
 */
#define EVENT_GET_MPU6000		0

/**
 * On récupère les valeurs Magn
 */
#define EVENT_GET_HMC5883L		1

/**
 * On récupère les angles
 */
#define EVENT_COMPUTE_ANGLES	2

/**
 * On affiche les données
 */
#define EVENT_SERIAL_DISPLAY_DATA	3

/**
 * Sustentation, asservissement du drone
 */
#define EVENT_STABILISATION			4

#endif /* EVENTS_H_ */
