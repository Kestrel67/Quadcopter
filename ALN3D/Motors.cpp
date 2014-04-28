/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

iDutyCycle_t MotorsThrottle[4] = {0, 0, 0, 0};

DutyCycle_t MotorsLowerLimit[4] = {0, 0, 0, 0};

DutyCycle_t MotorsHigherLimit[4] = {150, 150, 150, 150};

// dc
void ApplyMotorsThrottle(void)
{
	// APL_REG_MOTORA, APL_REG_MOTORB, APL_REG_MOTORC, APL_REG_MOTORD
	for(uint8_t motor = 0; motor < 4; motor++)
		AP_write(motor, MotorsThrottle[motor]);
}

// on applique contraintes de DC
void MotorsConstrains(void)
{
	for(uint8_t motor = 0; motor < 4; motor++)
		MotorsThrottle[motor] = constrain(MotorsThrottle[motor], MotorsLowerLimit[motor], MotorsHigherLimit[motor]);
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
