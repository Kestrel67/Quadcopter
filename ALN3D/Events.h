/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef EVENTS_H_
#define EVENTS_H_

// Procédures (dernier évènement)
#define EVENT_PROCEDURE MAX_EVENTS - 1

//	Observer (avant dernier évènement)
#define EVENT_SERIAL_OBSERVER MAX_EVENTS - 2

//	Analyseur
#define EVENT_ANALYSER MAX_EVENTS - 3

// HC-SR04 Pulse generating
#define EVENT_PULSE_GENERATING MAX_EVENTS - 4

// HC-SR04 trigger/sample du HC-SR04
#define EVENT_HC_SR04_SAMPLE MAX_EVENTS - 5

// Accel, Gyro
#define EVENT_GET_MPU6000		0

// Magn
#define EVENT_GET_HMC5883L		1

// normalize, angles
#define EVENT_COMPUTE_ANGLES	2

// serial display
#define EVENT_SERIAL_DISPLAY_DATA	3

// sustentation, asservissement du drone
#define EVENT_STABILISATION			4

#endif /* EVENTS_H_ */
