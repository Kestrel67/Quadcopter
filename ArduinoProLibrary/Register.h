/*
 * Register.h
 *
 *  Created on: 14 janv. 2014
 *      Author: Lucas
 */

#ifndef REGISTER_H_
#define REGISTER_H_

/**
 * Nombre de données dans le registre
 */
#define APL_MAX_REGISTERS 16

/**
 * Max register validation
 */
#if APL_MAX_REGISTERS > APL_MAX_REGISTERS_MAX_VALUE
#error APL_MAX_REGISTERS must be smaller or equal to 32
#endif

/**
 *	table des registres
 */
extern byte REG[APL_MAX_REGISTERS];

/**
 * table des registres mis à jour
 */
extern bool REG_UPDATED[APL_MAX_REGISTERS];

/**
 * écriture dans un registre
 */
void reg_write(Reg_t reg, byte value);

/**
 * Lecture d'un registre
 */
byte reg_read(Reg_t reg);

/**
 * Le registre a été prit en compte
 */
bool reg_updated(Reg_t reg);

/**
 * Deboggage
 */
void reg_debug(HardwareSerial *ser = &Serial);

#endif /* REGISTER_H_ */
