/*
 * IO.h
 *
 *  Created on: 13 janv. 2014
 *      Author: Lucas
 */

#ifndef IO_H_
#define IO_H_

/**
 * Physical IN/OUT
 */

/**
 * Sorties PWM
 */
#define PWM3 3 // 490 Hz
#define PWM5 5 // 980 Hz
#define PWM6 6 // 980 HZ
#define PWM9 9 // 490 Hz
#define PWM10 10 // 490 Hz
#define PWM11 11 // 490 Hz

/*
 * Entrées analogiques
 */
#define ANALOGIN0 0
#define ANALOGIN1 1
#define ANALOGIN2 2
#define ANALOGIN3 3
#define ANALOGIN4 4
#define ANALOGIN5 5
#define ANALOGIN6 6
#define ANALOGIN7 7


/**
 * Sorties digitales
 */
#define DOUT2 2
#define DOUT3 3
#define DOUT4 4
#define DOUT5 5
#define DOUT6 6
#define DOUT7 7
#define DOUT8 8
#define DOUT9 9
#define DOUT10 10
#define DOUT11 11
#define DOUT12 12
#define DOUT13 13

/**
 * Entrées digitales
 */
#define DIN2 2
#define DIN3 3
#define DIN4 4
#define DIN5 5
#define DIN6 6
#define DIN7 7
#define DIN8 8
#define DIN9 9
#define DIN10 10
#define DIN11 11
#define DIN12 12
#define DIN13 13

/**
 * emplacement des pins moteurs
 */
const Pin_t MA = PWM3; // Frequency 500Hz
const Pin_t MB = PWM5; // Frequency 500Hz
const Pin_t MC = PWM6; // Frequency 500Hz
const Pin_t MD = PWM9; // Frequency 500Hz

// potentiomètre
const Pin_t POTENCIOMETER = ANALOGIN0;

/**
 * led rouge
 */
const Pin_t LED_RED = DOUT4;

/**
 * led verte
 */
const Pin_t LED_GREEN = DOUT2;

/**
 * Remote control receiver pin
 */
#define RM_RECV_PIN 8

/**
 * YELLOW LEd
 */
#define YELLOW_LED DOUT13

/**
 * initialisation des pins, etc ...
 */
void IO_init(void);

/**
 * Lecture de la valeur du potentimètre
 */
uint8_t read_potenciometer_value(void);

#endif /* IO_H_ */
