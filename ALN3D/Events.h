/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#define EVENT_PROCEDURE 		MAX_EVENTS - 1 	// Procédures (dernier évènement)
#define EVENT_SERIAL_OBSERVER 	MAX_EVENTS - 2	// Observer (avant dernier évènement)
#define EVENT_ANALYSER			MAX_EVENTS - 3 	// Analyseur
#define EVENT_PULSE_GENERATING 	MAX_EVENTS - 4	// HC-SR04 Pulse generating
#define EVENT_HC_SR04_SAMPLE 	MAX_EVENTS - 5	// HC-SR04 trigger/sample du HC-SR04

#define EVENT_DYNAMIC				0	// Accel, Gyro, angles, normalize
#define EVENT_AZIMUT				1	// Magn, corrections
#define EVENT_SERIAL_DATA_IN		2	// serial in
#define EVENT_SERIAL_DATA_OUT		3	// serial out
#define EVENT_PID_ROLL_PITCH		4
#define EVENT_PID_ALTITUDE			5
#define EVENT_LED_POSITION			6

#define EVENT_HMC5883L				7
#define EVENT_MPU6000				8


#endif /* EVENTS_H_ */
