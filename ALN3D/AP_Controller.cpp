/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

float KpPitch = 	KP, 	KiPitch = 		KI, 	KdPitch = 		KD;
float KpRoll = 		KP, 	KiRoll = 		KI, 	KdRoll = 		KD;
float KpYaw = 		0.1, 	KiYaw = 		0.2, 	KdYaw = 		0.0;
float KpAltitude = 	0.2, 	KiAltitude = 	0.2, 	KdAltitude = 	0.0;

int PitchLimits[2] = {-50, 50}, RollLimits[2] = {-50, 50}, YawLimits[2] = {-10, 10}, AltitudeLimits[2] = {0, 50};

float phi_in, 				theta_in, 				psi_in, 				altitude_in;
float phi_setpoint = 0, 	theta_setpoint = 0, 	psi_setpoint = 0, 		altitude_setpoint = 0;
float phi_control = 0, 		theta_control = 0, 		psi_control = 0, 		altitude_control = 0;

QuadPID PitchController		(KpPitch, 	KiPitch, 	KdPitch, 		&phi_in, 	&phi_control, 		&phi_setpoint);
QuadPID RollController		(KpRoll, 	KiRoll, 	KdRoll, 		&theta_in, 	&theta_control, 	&theta_setpoint);
QuadPID YawController		(KpYaw, 	KiYaw, 		KdYaw, 			&psi_in, 	&psi_control, 		&psi_setpoint);
QuadPID AltitudeController(KpAltitude, 	KiAltitude, KdAltitude, 	&altitude_in, &altitude_control, &altitude_setpoint);

// initialisation du PID
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
	AltitudeController.SetSamplePeriod(FREQUENCY_PID_ALTITUDE);
	AltitudeController.SetDirection(QUADPID_DIRECT);
	AltitudeController.SetOutputLimits(AltitudeLimits[PID_IDX_LIMIT_MIN], AltitudeLimits[PID_IDX_LIMIT_MAX]);

	/** setpoints **/
	phi_setpoint = theta_setpoint = psi_setpoint = 0.0;

	// default control
	psi_control = 0.0;
	altitude_control = 50;
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

// information PID
void PIDinformation(void)
{
	PitchController.info();
	RollController.info();
	YawController.info();
	AltitudeController.info();
}

// on affiche les commandes PID
void DisplayPIDControl(HardwareSerial *ser)
{
	ser->print("phi : ");
	ser->print(phi_control);
	ser->print("\t theta : ");
	ser->print(theta_control);
	ser->print("\t psi : ");
	ser->print(psi_control);
	ser->print("\t altitude : ");
	ser->print(altitude_control);
}
