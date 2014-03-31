/*
 * Constants.h
 *
 *  Created on: 13 janv. 2014
 *      Author: Lucas
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/**
 * Library identification
 */
#define _APL_ID_ 1
#define _ARDUINO_PRO_LIBRARY_ID_CONSTANT 1

/**
 * THROTTLE range mode, dynamique(0) | static(1)
 */
#define ESC_THROTTLE_RANGE_MODE 0

/**
 * On affiche les infos, status, moteurs par voie série ou non (0)
 */
#define APL_SERIAL_DISPLAY 1

/**
 * valeur maximale de MAX_REGISTERS (5 bits)
 */
#define APL_MAX_REGISTERS_MAX_VALUE 32

/**
 * Nombre de registres utilisés
 */
#define APL_REGISTERS_USED 16

/**
 * Serial baud rate
 */
#define APL_DEFAULT_SERIAL_BAUDRATE 115200


/**
 * REG registers
 */
#define APL_REG_MOTORA 0 // moteur A
#define APL_REG_MOTORB 1 // moteur B
#define APL_REG_MOTORC 2 // moteur C
#define APL_REG_MOTORD 3 // moteur D

#define APL_REG_STATUS 4 // status

#define APL_REG_BLK	5 // led blink (verte)

/**
 * différents statuts du système
 */
#define SYS_UNDEFINED 	0 // status indéfini
#define SYS_CONFIG 		1 // système en mode configuration
#define SYS_ON 			4 // système en fonctionnement normal
#define SYS_PAUSE 		5 // système en pause
#define SYS_EMERGENCY 	6 // système en état d'urgence

/**
 * états de la led
 */
#define BLK_LED_OFF 0 // on éteint al eld
#define BLK_LED_TOGGLE 1// on inverse l'état de la led
#define BLK_LED_ON 255// on allume la led




/**
 * récupère le Most Significant Bit d'un octet (8bits)
 */
#define MSB(b) (b >> 7)

/**
 * Récupère le reste de l'octet (les LSBs) (8bits)
 */
#define LSBS(b) (b & (~(1<<7)))

/**
 * SPI constants
 */
#define APL_SPI_REG_BYTE_MASK B10000000 // masque d'otect de registre
#define APL_SPI_VAL_BYTE_MASK B00000000 // masque d'octet de valeur

#define APL_SPI_REG_OFFSET 2 // décalage du registre dans le premier octet
#define APL_SPI_REG_MASK B01111100 // masque pour récupérer le registre

#define APL_SPI_RW_OFFSET 1 // décalage de bit de lecture/écriture dans le premier octet
#define APL_SPI_RW_MASK B00000010 // masque pour récupérer lecture écriture

#define APL_SPI_WRITE 1 // si bit à 1 : écriture
#define APL_SPI_READ 0 // sinon lecture

#define APL_SPI_VAL_MSB 0 // emplacement du MSB de la valeur
#define APL_SPI_VAL_MSB_MASK 1 // masque pour récupérer le premier bit de la valeur
#define APL_SPI_VAL_LSBS_MASK B01111111// masque pour récupérer le reste de l'octet

#define APL_REGISTER_RECEIVED 1 // pour dire au maitre que le message a bien été reçus


#endif /* CONSTANTS_H_ */
