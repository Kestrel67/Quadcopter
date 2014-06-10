/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */


#include "ALN3D.h"

// status
byte system_status = SYS_CONFIG;

// system status
void ChangeSystemStatus(byte status)
{
	system_status = status;
	
	switch(status)
	{
		// on
		case SYS_ON:
			AP_write(APL_REG_STATUS, SYS_ON);
			AP_write(APL_REG_BLK, 0);
			//PID_Automatic();
			break;

		// pause / config / init
		case SYS_PAUSE:
			AP_write(APL_REG_STATUS, SYS_PAUSE);
			PID_Manual();
			break;

		// error, emergency
		case SYS_EMERGENCY:
			AP_write(APL_REG_STATUS, SYS_EMERGENCY);
			AP_write(APL_REG_BLK, 255);
			PID_Manual();
			break;

		default:
			// error
			system_status = SYS_UNDEFINED;
			break;
	}
}

// sécurité
void CheckAngles(void)
{
	// état d'urgence
	if (abs(phi) > SAFETY_MAX_ANGLE || abs(theta) > SAFETY_MAX_ANGLE) {

		// on met le système en état d'urgence => on coupe les moteurs
		ChangeSystemStatus(SYS_EMERGENCY);

	} else {
		// AP_write(APL_REG_BLK, 0);
	}
}
