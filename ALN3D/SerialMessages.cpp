#include <ALN3D.h>

// tabulation
void sTab(HardwareSerial *ser)
{
	ser->print("\t");
}

// retour à la ligne
void sLn(HardwareSerial *ser)
{
	ser->println();
}

// debug
void ser_display_angles_pid_motors(HardwareSerial *ser)
{
	  ser->print("phi : ");
	  ser->print(phi * RAD_TO_DEG, 3);
	  ser->print("\t theta : ");
	  ser->print(theta * RAD_TO_DEG, 3);
	  ser->print("\t");
	  ser->print("altitude : ");
	  ser->print(distance);
	  ser->print("\t");
	  ser->print("freq : ");
	  ser->print(system_frequency);
	  ser->print("\t");

	  DisplayMotorsThrottle(ser);
}

void ser_display_analyser_data(HardwareSerial *ser)
{

	/*
	ser->print("C: ");
	ser->print(loop_counter);
	ser->print("\t");
	*/

	ser->print("Freq: ");
	ser->print(system_frequency);
	ser->print("\tCPU: ");
	ser->print(CPU_use);
	ser->print("\trcvd_cmd: ");
	ser->print(received_commands);
	ser->print("\tsnd_anws: ");
	ser->print(sended_answers);
	ser->print("\tev: ");
	ser->print(events_thrown);

	/*
	ser->print("\tev(R): ");
	ser->print(registered_events);
	ser->print("\tev(Q): ");
	ser->print(events_count);
	ser->print("\tproc: ");
	ser->print(procedures_stored);
	ser->print("\ttimer_p: ");
	ser->print(timer_pointer);
	*/

	ser->print("\ttimers: ");
	ser->print(timers_expired);
	ser->print("\toverf: ");
	ser->print(analyser_events_overflow);

	/*
	ser->print("\tev(T): ");
	ser->print(events_processed);
	*/

	ser->println();
}

void ser_display_IMU_conf(HardwareSerial *ser)
{
	Serial.print("Start");
}

/*
void ser_display_IMU_conf_old(HardwareSerial *ser)
{
	ALN3D_Author();
	PIDinformation();

	ser->print("IMU conf: ");
	ser->print("\t MODE : ");

#if IMU_MODE == IMU_MODE_NORMAL
	ser->print("NORMAL FILTER");

	ser->print("\tLOW-PASS-FILTER : ");
	ser->print(float(LOWPASSFILTER_VAL), 3);

	ser->print("\tFilter : ");


#if IMU_FILTER == KALMAN_FILTER
	ser->print("Kalman Filter");
#elif IMU_FILTER == COMPLEMENTARY_FILTER
	ser->print("Complementary Filter");
	ser->print("\tCF : ");
	ser->print(float(COMPLEMENTARY_FILTER_VAL), 3);
#else
	ser->print("Probabilistic Filter");
	ser->print("\tMPF : ");
	ser->print(float(PROBABILISTIC_FILTER_MIN_VAL), 3);
#endif

#else
	ser->print("FULL GYRO");
#endif

	ser->println();

	ser->print("Calibration : ");
	Vector_Display(Omega_Gap);
}
*/


// visual
void PreConfCOMVisual(void)
{
	Serial.print(system_status);
	Serial.print("  phi : ");
	Serial.print(phi * RAD_TO_DEG, 1);
	Serial.print("\t theta : ");
	Serial.print(theta * RAD_TO_DEG, 1);
	//Serial.print("\t psi : ");
	//Serial.print(psi * RAD_TO_DEG, 1);
	Serial.print("\tSET[");
	Serial.print(phi_setpoint);
	Serial.print(" : ");
	Serial.print(theta_setpoint);
	Serial.print("]  ");

	Serial.print("PID:");
	Serial.print(KpPitch, 2);
	Serial.print(" ");
	Serial.print(KiPitch, 2);
	Serial.print(" ");
	Serial.print(KdPitch, 2);
	Serial.print("\t");

	Serial.print(CPU_use);
	Serial.print("% \t");
	Serial.print(analyser_events_overflow);
	Serial.print("\t");


	DisplayMotorsThrottle();
}

// python
void PreConfCOMPython(void)
{
	Serial.print(millis() / 1000.0);
	Serial.print(";");
	Serial.print(phi * RAD_TO_DEG);
	Serial.print(";");
	Serial.print(theta * RAD_TO_DEG);
	Serial.print(";");
	Serial.println(psi * RAD_TO_DEG);
}

// precessing
void PreConfCOMProcessing(void)
{
	Serial.print(phi, 4);
	Serial.print(";");
	Serial.print(theta, 4);
	Serial.print(";");
	Serial.println(psi, 4);
}

// python setpoing angle
void PreConfCOMPythonPID(void)
{
	Serial.print(millis() / 1000.0);
	Serial.print(";");
	Serial.print(theta * RAD_TO_DEG); // angle
	Serial.print(";");
	Serial.print(theta_setpoint * RAD_TO_DEG); // setpoint
	Serial.print(";");
	Serial.println(90);	// nothing
}

/**
 * informations
 */
void ALN3D_Author(HardwareSerial *ser)
{
	if (ser)
	{
		char buffer[200];
		sprintf(buffer, "*********** ALN 3D Project ***********\n** author:Dietrich Lucas (Kestrel)  **\n** email:kestrel.3rd@gmail.com      **\n** website:http://www.kestrel.fr/   **\n**************************************");
		ser->println(buffer);
	}
}

