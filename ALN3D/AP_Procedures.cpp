/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include <ALN3D.h>

void _proc_dynamic_calculation(void)
{
	IMUExecution();
	CheckAngles();
}

void _proc_dynamic_angles_PID(void)
{
	// input
	phi_in = phi * RAD_TO_DEG;
	theta_in = theta * RAD_TO_DEG;
	psi_in = psi * RAD_TO_DEG;

	// calculation
	PitchController.Compute();
	RollController.Compute();
	//YawController.Compute();

	// DC
	MotorsThrottle[MA] = altitude_control + phi_control + psi_control;
	MotorsThrottle[MB] = altitude_control - phi_control + psi_control;

	MotorsThrottle[MC] = altitude_control + theta_control - psi_control;
	MotorsThrottle[MD] = altitude_control - theta_control - psi_control;

	// constrains
	MotorsConstrains();

	// apply change
	ApplyMotorsThrottle();
}

void callback_pid_altitude(void)
{
	// Altitude
	// system status

	//AltitudeController.Compute();
	return;
}

#if CMD_IN_MODE == CMD_IN_PROD
void callback_ser_data_in(void)
{
	// current_cmd
	// attached_param

	switch (current_cmd)
	{
		// changement état du système
		case CMD_CHANGE_STATUS:
			ChangeSystemStatus(attached_param);
			break;

		// urgence
		case CMD_STOP:
		case CMD_WARN_EMERGENCY:
			ChangeSystemStatus(SYS_EMERGENCY);
			break;

		// changement altitude
		case CMD_CHANGE_AVG_THROTTLE:
			altitude_control = attached_param;
			break;

		// coeff Kp pour PID (pitch, roll)
		case CMD_CHANGE_PR_KP:
			KpPitch = KpRoll = attached_param / 100.0;
			PitchController.SetTunings(KpPitch, KiPitch, KdPitch);
			PitchController.SetTunings(KpRoll, KiRoll, KdRoll);
			break;

		// coeff Ki pour PID (pitch, roll)
		case CMD_CHANGE_PR_KI:
			KiPitch = KiRoll = attached_param / 100.0;
			PitchController.SetTunings(KpPitch, KiPitch, KdPitch);
			PitchController.SetTunings(KpRoll, KiRoll, KdRoll);
			break;

		// coeff Kd pour PID (pitch, roll)
		case CMD_CHANGE_PR_KD:
			KdPitch = KdRoll = attached_param / 100.0;
			PitchController.SetTunings(KpPitch, KiPitch, KdPitch);
			PitchController.SetTunings(KpRoll, KiRoll, KdRoll);
			break;

		// change pitch setpoint
		case CMD_PITCH_SETPOINT:
			phi_setpoint = attached_param / 255.0 * 40.0 - 20.0;
			break;

		// change roll setpoint
		case CMD_ROLL_SETPOINT:
			theta_setpoint = attached_param / 255.0 * 40.0 - 20.0;
			break;
	}

}
#else

// DEV

void callback_ser_data_in(void)
{
	if (Serial.available() > 0)
	{
		byte o = Serial.read();

		switch (o)
		{
		// start
		case 'a':
			ChangeSystemStatus(SYS_ON);
			Serial.print("[started]");
			break;

		// pause
		case 'z':
			ChangeSystemStatus(SYS_PAUSE);
			Serial.print("[stopped]");
			break;

		// emergency stop
		case 'e':
			ChangeSystemStatus(SYS_EMERGENCY);
			Serial.print("[EMERGENCY!!]");
			break;
		}
	}
}

#endif

void _proc_com_out(void)
{

#if	COM_MODE == COM_VISUAL

		Serial.print("phi : ");
		Serial.print(phi * RAD_TO_DEG, 1);
		Serial.print("\t theta : ");
		Serial.print(theta * RAD_TO_DEG, 1);
		Serial.print("\t psi : ");
		Serial.print(psi * RAD_TO_DEG, 1);
		Serial.print("\tpitch setpoint : ");
		Serial.print(phi_setpoint);
		Serial.print("\troll setpoint : ");
		Serial.print(theta_setpoint);

		/*
		Serial.print("\t altitude :");
		Serial.print(distance);
		Serial.print("\t");
		Serial.print("freq : ");
		Serial.print(system_frequency);
		Serial.print("\t CPU use : ");
		Serial.print(CPU_use);
		*/
		Serial.print("\t");

		DisplayMotorsThrottle();

#elif COM_MODE == COM_PYTHON
	  Serial.print(millis() / 1000.0);
	  Serial.print(";");
	  Serial.print(phi * RAD_TO_DEG);
	  Serial.print(";");
	  Serial.print(theta * RAD_TO_DEG);
	  Serial.print(";");
	  Serial.println(gyroscopes_integration_error * RAD_TO_DEG, 3);

#elif COM_MODE == COM_XBEE
	  send_serial_data_xbee(&Serial);
#endif
}

// sécurité
void CheckAngles(void)
{
	// état d'urgence
	if (abs(phi_in) > SAFETY_MAX_ANGLE || abs(theta_in) > SAFETY_MAX_ANGLE) {

		// on met le système en état d'urgence => on coupe les moteurs
		ChangeSystemStatus(SYS_EMERGENCY);

	} else {
		// AP_write(APL_REG_BLK, 0);
	}
}
