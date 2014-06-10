/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

iDutyCycle_t MotorsThrottle[4] = {0, 0, 0, 0};

DutyCycle_t MotorsLowerLimit[4] = {MOTORS_LOWER_LIMIT, MOTORS_LOWER_LIMIT, MOTORS_LOWER_LIMIT, MOTORS_LOWER_LIMIT};

DutyCycle_t MotorsHigherLimit[4] = {MOTORS_UPPER_LIMIT, MOTORS_UPPER_LIMIT, MOTORS_UPPER_LIMIT, MOTORS_UPPER_LIMIT};

// calculate, constrain, apply
void UpdateMotorsThrottle(void)
{
	CalculateMotorsThrottle();
	MotorsConstrains();
	ApplyMotorsThrottle();
}

// calculation
void CalculateMotorsThrottle(void)
{
	MotorsThrottle[MA] = altitude_control + phi_control + psi_control;	// (eq.9a)
	MotorsThrottle[MB] = altitude_control - phi_control + psi_control; // (eq.9b)

	MotorsThrottle[MC] = altitude_control + theta_control - psi_control; // (eq.9c)
	MotorsThrottle[MD] = altitude_control - theta_control - psi_control; // (eq.9d)
}

// on applique contraintes de DC
void MotorsConstrains(void)
{
	for(uint8_t motor = 0; motor < 4; motor++)
		MotorsThrottle[motor] = constrain(MotorsThrottle[motor], MotorsLowerLimit[motor], MotorsHigherLimit[motor]);
}

// dc
void ApplyMotorsThrottle(void)
{
	// APL_REG_MOTORA, APL_REG_MOTORB, APL_REG_MOTORC, APL_REG_MOTORD
	for(uint8_t motor = 0; motor < 4; motor++)
		AP_write(motor, MotorsThrottle[motor]);
}

// on affiche les paramètres throttle
void DisplayMotorsThrottle(HardwareSerial *ser)
{
  for (uint8_t i = 0; i < 4; i++)
  {
     ser->write(65 + i);
     ser->print(" : ");
     ser->print(MotorsThrottle[i]);
     ser->print("\t");
  }
  ser->println();
}
