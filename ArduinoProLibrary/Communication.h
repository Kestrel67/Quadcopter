/*
 * Communication.h
 *
 *  Created on: 14 janv. 2014
 *      Author: Lucas
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

/**
 * Synchronisation SPI
 */
void SPI_synchronization(void);

/**
 * Valeur de registre temporraire
 */
extern byte tmp_reg;

/**
 * msb de la valeur temporraire
 */
extern bool tmp_msb_val;

/**
 * Savoir s'il faut écrire ou lire
 */
extern bool tmp_write;

/**
 * Fonction appelé lors d'une interruption SPI
 * @param byte spdr : valeur reçu du maitre
 * @return byte : valeur à renvoyer au maitre lors de la pochaine transaction
 */
byte reg_isr_spi_interrupt(byte spdr);

/**
 * Serial com
 */
void serial_display_motors_throttle(HardwareSerial *ser = &Serial);


/**
 * IR com
 */

#if ENABLE_IR_RECEIVER
/**
 * Infrared remote control
 * Remote control : SchaubLorenz
 */

// instance
extern IRrecv irrecv;

// résultats
extern decode_results rm_results;

/**
 * Récupère la commande envoyé par la télécommande ou 0 si aucune commande
 */
unsigned long irrm_get_cmd(void);
#endif /**#if ENABLE_IR_RECEIVER **/

#endif /* COMMUNICATION_H_ */
