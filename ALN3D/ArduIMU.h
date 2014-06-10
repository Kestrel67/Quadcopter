/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/**
 * Fichier de définitions des constantes liées à l'arduIMU V3
 * in, out, leds, etc...
 */
#ifndef ArduIMU_h
#define ArduIMU_h

/**
 * LEDS
 */
#define EMBEDED_LED_RED 5
#define EMBEDED_LED_BLUE 6
#define EMBEDED_LED_YELLOW 13 // doesn't work on V3

/**
 * timer1 : interrupt pin
 */
#define D8 8

/**
 * pin PWM
 */
#define PWM0 9 // trigger pin (HC-SR04)
#define PWM1 10 // SS pin (SPI)

/**
 * Pins definition
 */
#define HC_SR04_TRIGGER_PIN 	PWM0
#define SPI_SS 					PWM1
#define HC_SR04_PULSE_PIN 		D8

/**
 * virtual AP motor pin
 */
#define MA 0
#define MB 1
#define MC 2
#define MD 3

// SPI
/*
#define MOSI
#define MISO
#define SS // PWM1
#define SCK
*/

#endif
