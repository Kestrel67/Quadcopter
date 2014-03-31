/*
 * Communication.cpp
 *
 *  Created on: 14 janv. 2014
 *      Author: Lucas
 */

#include "ArduinoProLibrary.h"

void SPI_synchronization(void)
{
	reg_write(APL_REG_STATUS, SYS_CONFIG);

	// tant que l'IMU n'a pas changé l'état du système
	while(reg_read(APL_REG_STATUS) == SYS_CONFIG)
	{
		// led effects
		digitalWrite(LED_RED, !digitalRead(LED_RED));
		delay(50);
	}
	// led off
	digitalWrite(LED_RED, HIGH);
}

byte tmp_reg;

bool tmp_msb_val;

bool tmp_write;

/**
 * SPI interrupt
 */
ISR (SPI_STC_vect)
{
	SPDR = reg_isr_spi_interrupt(SPDR);
}

byte reg_isr_spi_interrupt(byte spdr)
{
	// premier octet
	if (APL_SPI_REG_BYTE_MASK & spdr)
	{
		// on recupère le registre
		tmp_reg = (APL_SPI_REG_MASK & spdr) >> APL_SPI_REG_OFFSET;

		// on regarde s'il s'agit d'une écriture ou d'une lecture
		tmp_write = (APL_SPI_RW_MASK & spdr); // >> APL_SPI_RW_OFFSET;

		// lecture
		if (!tmp_write)
		{
			return reg_read(tmp_reg);
		}
		// sinon

		// on récupère le msb de la valeur
		tmp_msb_val = (APL_SPI_VAL_MSB_MASK & spdr);
	}
	// deuxième octet et écriture
	else if (tmp_write)
	{
		// on récupère la valeur
		byte val = (tmp_msb_val << 7) | (APL_SPI_VAL_LSBS_MASK & spdr);

		// on écrit dans le registre
		reg_write(tmp_reg, val);

		tmp_write = false;
	}
	// sinon ne rien faire (2 ème octet de lecture)
	return APL_REGISTER_RECEIVED;
}


/**
 * Serial com
 */

// on affiche les status
void serial_display_motors_throttle(HardwareSerial *ser)
{
	char buffer[38];
	sprintf(buffer, "MA : %d\tMB : %d\tMC : %d\tMD : %d",
		reg_read(APL_REG_MOTORA),
		reg_read(APL_REG_MOTORB),
		reg_read(APL_REG_MOTORC),
		reg_read(APL_REG_MOTORD));

	ser->println(buffer);
}


/**
 * IR rom
 */

#if ENABLE_IR_RECEIVER
/**
 * Infrared remote control
 * Remote control : SchaubLorenz
 */

IRrecv irrecv(RM_RECV_PIN);

// résultats
decode_results rm_results;

unsigned long irrm_get_cmd(void)
{
	unsigned long cmd = 0;

	// s'il y a une nouvelle commande
	if (irrecv.decode(&rm_results))
	{
		// s'il est est inférieur à 0 il s'agit d'unne erreur
		cmd = rm_results.value < 0 ? 0 : rm_results.value;

		// resume (attente d'une nouvelle commande)
		irrecv.resume();
	}

	// on retourne la commande
	return cmd;
}
#endif /** #if ENABLE_IR_RECEIVER **/
