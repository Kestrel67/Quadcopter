/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

/**
 * On fait une pause pendant time milliseconds
 */
void APL_delay(unsigned long time);

/**
 * On fait une pause pendant time microsecondes
 */
//void APL_delayMicroseconds(unsigned long time);

/**
 * On allume ou on éteint une led de l'AP
 */
void turn_on(Pin_t led);
void turn_off(Pin_t led);

/**
 * On inverse l'état de la led
 */
void reverse(Pin_t led);

#endif
