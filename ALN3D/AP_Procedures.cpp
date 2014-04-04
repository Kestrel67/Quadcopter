/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include <ALN3D.h>

void _proc_dynamic_calculation(void)
{
	MPU6000_Read();
	MPU6000_Corrections_Scale();
	Gyroscopes_Integration();
	Normalize();
	CheckAngles();

	  Serial.print(millis() / 1000.0);
	  Serial.print(";");
	  Serial.print(phi * RAD_TO_DEG);
	  Serial.print(";");
	  Serial.println(theta * RAD_TO_DEG);
}

void _proc_azimut_calculation(void)
{
	HMC5883L_Read();
}

void _proc_dynamic_angles_PID(void)
{
	// input
	phi_in = phi * RAD_TO_DEG;
	theta_in = theta * RAD_TO_DEG;
	psi_in = Azimut * RAD_TO_DEG;

	// calculation
	PitchController.Compute();
	RollController.Compute();

	// motors DC change
	_proc_apply_motors_change();
}

void _proc_altitude(void)
{
	// Altitude
	// system status
}

void _proc_apply_motors_change(void)
{
	// DC
	MotorsThrottle[MA] = altitude_control + phi_control + psi_control;
	MotorsThrottle[MB] = altitude_control - phi_control + psi_control;

	MotorsThrottle[MC] = altitude_control + theta_control - psi_control;
	MotorsThrottle[MD] = altitude_control - theta_control - psi_control;

	// constrains
	MotorsConstrains();

	// apply change
	AP_ApplyMotorsThrottle();
}

void _proc_com_in(void)
{
	// current_cmd
	// attached_param

	switch (current_cmd)
	{
		// changement état du système
		case CMD_CHANGE_STATUS:
			_proc_system(attached_param);
			break;
	}
}

void _proc_com_out(void)
{
	// data out
	//send_serial_data(); // formaté
	return;
	Serial.print("phi : ");
	  Serial.print(phi * RAD_TO_DEG, 3);
	  Serial.print("\t theta : ");
	  Serial.print(theta * RAD_TO_DEG, 3);
	  Serial.print("\t");
	  Serial.print("altitude : ");
	  Serial.print(distance);
	  Serial.print("\t");
	  Serial.print("freq : ");
	  Serial.print(system_frequency);
	  Serial.print("\t");

	  DisplayMotorsThrottle();
}

void _proc_system(byte status)
{
	switch(status)
	{
		// on
		case SYS_ON:
			AP_write(APL_REG_STATUS, SYS_ON);
			PID_Automatic();
			system_status = status;
			break;

		// pause / config / init
		case SYS_PAUSE:
			AP_write(APL_REG_STATUS, SYS_PAUSE);
			PID_Manual();
			system_status = status;
			break;

		// error, emergency
		case SYS_EMERGENCY:
			AP_write(APL_REG_STATUS, SYS_EMERGENCY);
			AP_write(APL_REG_BLK, 255);
			PID_Manual();
			system_status = status;
			break;

		default:
			// error
			break;
	}
}
