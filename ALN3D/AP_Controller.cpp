/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

DutyCycle_t MotorsThrottle[4] = {0, 0, 0, 0};

DutyCycle_t MotorsLowerLimit[4] = {0, 0, 0, 0};

DutyCycle_t MotorsHigherLimit[4] = {100, 100, 100, 100};

float KpPitch = 	KP, 	KiPitch = 		KI, 	KdPitch = 		KD;
float KpRoll = 		KP, 	KiRoll = 		KI, 	KdRoll = 		KD;
float KpYaw = 		0.1, 	KiYaw = 		0.2, 	KdYaw = 		0.0;
float KpAltitude = 	0.2, 	KiAltitude = 	0.2, 	KdAltitude = 	0.0;

int PitchLimits[2] = {-100, 100}, RollLimits[2] = {-100, 100}, YawLimits[2] = {-10, 10}, AltitudeLimits[2] = {0, 50};

float phi_in, 				theta_in, 				psi_in, 				altitude_in;
float phi_setpoint = 0, 	theta_setpoint = 0, 	psi_setpoint = 0, 		altitude_setpoint = 0;
float phi_control = 0, 		theta_control = 0, 		psi_control = 0, 		altitude_control = 0;

QuadPID PitchController		(KpPitch, 	KiPitch, 	KdPitch, 		&phi_in, 	&phi_control, 		&phi_setpoint);
QuadPID RollController		(KpRoll, 	KiRoll, 	KdRoll, 		&theta_in, 	&theta_control, 	&theta_setpoint);
QuadPID YawController		(KpYaw, 	KiYaw, 		KdYaw, 			&psi_in, 	&psi_control, 		&psi_setpoint);
QuadPID AltitudeController(KpAltitude, 	KiAltitude, KdAltitude, 	&altitude_in, &altitude_control, &altitude_setpoint);

// intialisation du PID
void PID_Init(void)
{
	// direct : pitch + le nez pointe le ciel, - quand il pique
	// moteur A devant, contrôleur +
	// moteur B derière, contrôleur -
	PitchController.SetSamplePeriod(FREQUENCY_PID_PITCH);
	PitchController.SetDirection(QUADPID_DIRECT);
	PitchController.SetOutputLimits(PitchLimits[PID_IDX_LIMIT_MIN], PitchLimits[PID_IDX_LIMIT_MAX]);

	// direct : roll + à gauche
	// moteur C à droite, contrôleur +
	// moteur D à gauche, contrôleur -
	RollController.SetSamplePeriod(FREQUENCY_PID_ROLL);
	RollController.SetDirection(QUADPID_DIRECT);
	RollController.SetOutputLimits(RollLimits[PID_IDX_LIMIT_MIN], RollLimits[PID_IDX_LIMIT_MAX]);

	// yaw, A, B sens trigo
	// C, D sens horraire
	YawController.SetSamplePeriod(FREQUENCY_PID_YAW);
	YawController.SetDirection(QUADPID_DIRECT);
	YawController.SetOutputLimits(YawLimits[PID_IDX_LIMIT_MIN], YawLimits[PID_IDX_LIMIT_MAX]);

	// altitude
	AltitudeController.SetDirection(QUADPID_DIRECT);
	YawController.SetOutputLimits(AltitudeLimits[PID_IDX_LIMIT_MIN], AltitudeLimits[PID_IDX_LIMIT_MAX]);
	AltitudeController.SetSamplePeriod(FREQUENCY_PID_ALTITUDE);
}

/**
 * PID en mode manuel
 */
void PID_Manual(void)
{
	PitchController.SetMode(QUADPID_MANUAL);
	RollController.SetMode(QUADPID_MANUAL);
	YawController.SetMode(QUADPID_MANUAL);
	AltitudeController.SetMode(QUADPID_MANUAL);
}

/**
 * PID en mode automatique
 */
void PID_Automatic(void)
{
	PitchController.SetMode(QUADPID_AUTOMATIC);
	RollController.SetMode(QUADPID_AUTOMATIC);
	YawController.SetMode(QUADPID_AUTOMATIC);
	AltitudeController.SetMode(QUADPID_AUTOMATIC);
}

// application aux moteurs
void PIDCompute(void)
{
	PitchController.Compute();
	RollController.Compute();
	YawController.Compute();
	AltitudeController.Compute();

	MotorsThrottle[MA] = altitude_control + phi_control + psi_control;
	MotorsThrottle[MB] = altitude_control - phi_control + psi_control;

	MotorsThrottle[MC] = altitude_control + theta_control - psi_control;
	MotorsThrottle[MD] = altitude_control - theta_control - psi_control;
}

// on applique contraintes de DC
void MotorsConstrains(void)
{
	for(uint8_t motor = 0; motor < 4; motor++)
		MotorsThrottle[motor] = constrain(MotorsThrottle[motor], MotorsLowerLimit[motor], MotorsHigherLimit[motor]);
}

// sécurité
void CheckAngles(void)
{
	// état d'urgence
	if (abs(phi_in) > SAFETY_MAX_ANGLE || abs(theta_in) > SAFETY_MAX_ANGLE) {

		// on met le système en état d'urgence => on coupe les moteurs
		_proc_system(SYS_EMERGENCY);

	} else {
		// AP_write(APL_REG_BLK, 0);
	}
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
