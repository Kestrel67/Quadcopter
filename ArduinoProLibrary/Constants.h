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
 * On affiche les infos, status, moteurs par voie s�rie ou non (0)
 */
#define APL_SERIAL_DISPLAY 1

/**
 * valeur maximale de MAX_REGISTERS (5 bits)
 */
#define APL_MAX_REGISTERS_MAX_VALUE 32

/**
 * Nombre de registres utilis�s
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
 * diff�rents statuts du syst�me
 */
#define SYS_UNDEFINED 	0 // status ind�fini
#define SYS_CONFIG 		1 // syst�me en mode configuration
#define SYS_ON 			4 // syst�me en fonctionnement normal
#define SYS_PAUSE 		5 // syst�me en pause
#define SYS_EMERGENCY 	6 // syst�me en �tat d'urgence

/**
 * �tats de la led
 */
#define BLK_LED_OFF 0 // on �teint al eld
#define BLK_LED_TOGGLE 1// on inverse l'�tat de la led
#define BLK_LED_ON 255// on allume la led




/**
 * r�cup�re le Most Significant Bit d'un octet (8bits)
 */
#define MSB(b) (b >> 7)

/**
 * R�cup�re le reste de l'octet (les LSBs) (8bits)
 */
#define LSBS(b) (b & (~(1<<7)))

/**
 * SPI constants
 */
#define APL_SPI_REG_BYTE_MASK B10000000 // masque d'otect de registre
#define APL_SPI_VAL_BYTE_MASK B00000000 // masque d'octet de valeur

#define APL_SPI_REG_OFFSET 2 // d�calage du registre dans le premier octet
#define APL_SPI_REG_MASK B01111100 // masque pour r�cup�rer le registre

#define APL_SPI_RW_OFFSET 1 // d�calage de bit de lecture/�criture dans le premier octet
#define APL_SPI_RW_MASK B00000010 // masque pour r�cup�rer lecture �criture

#define APL_SPI_WRITE 1 // si bit � 1 : �criture
#define APL_SPI_READ 0 // sinon lecture

#define APL_SPI_VAL_MSB 0 // emplacement du MSB de la valeur
#define APL_SPI_VAL_MSB_MASK 1 // masque pour r�cup�rer le premier bit de la valeur
#define APL_SPI_VAL_LSBS_MASK B01111111// masque pour r�cup�rer le reste de l'octet

#define APL_REGISTER_RECEIVED 1 // pour dire au maitre que le message a bien �t� re�us


#endif /* CONSTANTS_H_ */
