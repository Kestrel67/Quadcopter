
#ifndef HARDWARE_TIMERS_H_
#define HARDWARE_TIMERS_H_

/**
 * TIMER0
 * TCCR0A, TCCR0B
 */

/** mode Fast PWM **/
// 1 	frequency 16Mhz / 256 = 62,5 kHz
// 2	frequency 16MHz / (256 * 8) = 7,8 kHz
// 3	frequency 16MHz / (256 * 64) = 976Hz
// 4	frequency 16MHz / (256 * 256) = 244Hz
// 5	frequency 16MHz / (256 * 1024) = 61HZ


/** mode PWM Phase Correct **/
// 1 	frequency 16Mhz / 510 = 31,4 kHz
// 2	frequency 16MHz / (510 * 8) = 3,9 kHz
// 3	frequency 16MHz / (510 * 64) = 490Hz
// 4	frequency 16MHz / (510 * 256) = 122Hz
// 5	frequency 16MHz / (510 * 1024) = 30,6HZ


#define TIMER0_NO_PRESCALER 	B001
#define TIMER0_PRESCALER8 		B010
#define TIMER0_PRESCALER64 		B011
#define TIMER0_PRESCALER256 	B100
#define TIMER0_PRESCALER1024 	B101


/**
 * On change le mode du timer0 en PWM phase correct
 */
void timer0_set_phase_correct_mode(void);


/**
 * Initialise le timer0 à  une certaine fréquence, in 5 et 6
 */
void timer0_set_prescaler(byte prescaler = TIMER0_PRESCALER8);


#endif /* HARDWARE_TIMERS_H_ */
