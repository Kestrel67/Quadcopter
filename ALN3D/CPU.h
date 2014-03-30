/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

#ifndef CPU_h
#define CPU_h

/**
 * Taille des données typés en octets (8bits
 */
void CPU_types_size(void);

/**
 * Fréquence de la clock de la CPU
 */
void CPU_frequency(void);

/**
 * On fait clignoter la led 13 le plus rapidement possible
 *
 * 1,592 MHz, fréquence maximale
 */
void LED13_CPU_frequency(void);

#endif
