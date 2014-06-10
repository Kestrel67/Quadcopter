/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

fVector_t Omega;	// angular velocity			(rad.s^-1)
fVector_t IOmega;	// angle from last mesure 	(rad)
fVector_t LastOmega; // last angular velocity	(rad.s^-1)
fVector_t FilteredOmega; // filtered angular velocity (rad.s^-1)
float HighPassFilterVal = GYRO_HIGHPASSFILTER_VAL;	// valeur du coeeficient du HPF
float OmegaMagnitude; // magnitude of the current angular velocity (rad.s^-1)

fVector_t Accel;	// acceleration				(m.s^-2)
fVector_t LastAccel;// last acceleration		(m.s^-2)
fVector_t NormalizedAccel;	// acceleration ||a|| = 1	(m.s^-2 / 9.81)
fVector_t SmoothedAccel;	// filtered acceleration	(m.s^-2)
float LowPassFilterVal = ACCEL_LOWPASSFILTER_VAL;	// valeur du coefficient du HPF
float AccelerationMagnitude; // magnitude of the current acceleration (m.s^-2)

fVector_t Magn;		// scaled		(mG)
fVector_t Magn_Row; // notscaled	(mG)

fVector_t Gravity = {0.0, 0.0, -1.0};		// virtual gravity vector
fVector_t LastGravity = {0.0, 0.0, -1.0};	// last gravity

fVector_t VirtualAzimut = {1.0, 0.0, 0.0};	// virtual Azimut vector

Angle_t gyroscopes_integration_error;	// sum(i, t) [ DELTAgyro * dTau ]
LongMicroSec_t LastIMUExecution;		// IMU last calculation

fVector_t AccelAngles;	// angles directs issuent des accéléromètres
fVector_t GyroAngles;	// angles directs issent des gyroscopes

// angles filtrés
Angle_t phi;	// pitch (tanguage) (rad)
Angle_t theta;	// roll (roulis)	(rad)
Angle_t psi;	// yaw (lacet)		(rad)
Angle_t delta;	// angle global de l'assiette (rad)

float qfilter; // filtre d'utilisation des gyroscopes

fMatrix_t GlobalRotMat = {{1.0, 0, 0}, {0, 1.0, 0}, {0, 0, 1.0}};

void IMU_Init(bool calibrate)
{
	// stable
	if (calibrate)	MPU6000_Gyro_Calibration();
	MPU6000_Read();
	MPU6000_Corrections_Scale();

	// apply acceleration
	Apply_Accelerometers_Angles();

	AccelAngles[PHI] = asin(-NormalizedAccel[X]);
	AccelAngles[THETA] = asin(-NormalizedAccel[Y]);

	phi = AccelAngles[PHI];
	theta = AccelAngles[THETA];

	// magnétomèters, azimut, ...

	// !!!! à enlever !!!! ????
	LastIMUExecution = micros();	// last integ time
}

// 50Hz; 100Hz; 200Hz
void IMUExecution(void)
{
	// dt
	LongMicroSec_t now = micros();
	float dt = (now - LastIMUExecution) / 1000000.0;
	LastIMUExecution = now;

	MPU6000_Read();	// data in
	MPU6000_Corrections_Scale(); // scale
	Gyroscopes_Integration(dt);	// integration
	DynamicRotations(); // on calcul les rotations avec les gyroscopes

#if IMU_MODE_BOTH == IMU_MODE
	/***** LISSAGE ACCELEROMETRES *****/
	LowPassFilterVal = FILTER_COEFFICIENT(ACCEL_TIME_CONSTANT, dt); // FILTER_COEFFICIENT(ACCEL_TIME_CONSTANT, dt);

	// eq.11 : low pass filter (vibrations)
	for (uint8_t i = 0; i < 3; i++)
		Accel[i] = SmoothedAccel[i] = LowPassFilter(LowPassFilterVal, Accel[i], SmoothedAccel[i]);

	Vector_Normalize(Accel, NormalizedAccel);
	PhiThetaFromGravity(NormalizedAccel, AccelAngles);
#endif


#if IMU_MODE == IMU_MODE_NORMAL
	// on normalise / corrige
	Normalize(dt);
#else
	// calcul des angles (full-precision mode)
	PhiThetaFromGravity(Gravity, GyroAngles);

	phi = GyroAngles[PHI];
	theta = GyroAngles[THETA];
#endif

	psi = atan2(VirtualAzimut[Y], VirtualAzimut[X]);
}

void Normalize(float dt)
{
	/***** LISSAGE ACCELEROMETRES *****/
	LowPassFilterVal = FILTER_COEFFICIENT(ACCEL_TIME_CONSTANT, dt);

	// eq.11 : low pass filter (vibrations)
	for (uint8_t i = 0; i < 3; i++)
		Accel[i] = SmoothedAccel[i] = LowPassFilter(LowPassFilterVal, Accel[i], SmoothedAccel[i]);

	Vector_Normalize(Accel, NormalizedAccel);

	/**** NORMES *****/
	AccelerationMagnitude = Vector_Magnitude(Accel);
	OmegaMagnitude = Vector_Magnitude(Omega);

	/**** EN MODE FULL GYRO *****/
	if (OmegaMagnitude > MAX_OMEGA_VELOCITY || AccelerationMagnitude > MAX_ACCEL_ACCELERATION)
	{
		PhiThetaFromGravity(Gravity, &phi, &theta);
		return;
	}

	/**** ANGLE ACCEL, GYRO *****/
	PhiThetaFromGravity(NormalizedAccel, AccelAngles);
	PhiThetaFromGravity(Gravity, GyroAngles);

	/**** FILTRE COMPLEMENTAIRE *****/
	// eq.13 : complementary filter
	qfilter = COMPLEMENTARY_FILTER_VAL; // HIGH COEFF

	phi = qfilter * GyroAngles[PHI]+ (1 - qfilter) * AccelAngles[PHI];
	theta = qfilter * GyroAngles[THETA]+ (1 - qfilter) * AccelAngles[THETA];

	// update integ_error
	gyroscopes_integration_error *= qfilter;

	/**** RECONSTRUCTION DU VECTEUR GRAVITE *****/
	RebuildGravity(Gravity, phi, theta); // eq.16

	// on conserve le vecteur gravité
	Vector_Copy(Gravity, LastGravity);
}

void Apply_Accelerometers_Angles(void)
{
	Vector_Normalize(Accel, NormalizedAccel);

	// full accel
	Vector_Copy(NormalizedAccel, Gravity);
}

void Gyroscopes_Integration(float dt)
{
	// on filtre les gyroscopes
	//FilterGyroscopes(dt);

	// eq.1 : intégration
	IOmega[X] += Omega[X] * dt; // dt = integration period
	IOmega[Y] += Omega[Y] * dt;
	IOmega[Z] += Omega[Z] * dt;

	// erreur (eq.6)
	gyroscopes_integration_error += GYRO_INTEGRATION_ERROR / 180.0 * PI * dt;
}

void DynamicRotations(void)
{
	// on met à jour la matrice de rotation
	update_rotation_matrix(IOmega[Y], IOmega[X], IOmega[Z]);

	// variables d'integrations à 0
	IOmega[X] = IOmega[Y] = IOmega[Z] = 0;

	// eq.3 : on applique la matrice de rotation au vecteur virtuel de pesanteur Gravity (et d'azimut)
	apply_rotation_matrix(Gravity);
	apply_rotation_matrix(VirtualAzimut);

// calcul de la matrice de rotation globale
#if IMU_MODE == IMU_MODE_FULL_GYRO
	Matrix_Multiply(GlobalRotMat, RotMat, GlobalRotMat);
#endif

	// on normalize le vecteur de gravité
	Vector_Normalize(Gravity);
}

void FilterGyroscopes(float dt)
{
	// filter val
	HighPassFilterVal = 0.999;	// FILTER_COEFFICIENT(GYRO_TIME_CONSTANT, dt)

	// eq.11 : low pass filter on accelerometer data (to filter vibrations)
	for (uint8_t i = 0; i < 3; i++)
	{
		FilteredOmega[i] = HighPassFilter(HighPassFilterVal, Omega[i], LastOmega[i], FilteredOmega[i]);
		LastOmega[i] = Omega[i];
		Omega[i] = FilteredOmega[i];
	}
}

// on met à jour les leds de position
void update_position_leds(void)
{
	if (abs(phi) < CORRECT_PITCH_ROLL_ANGLES && abs(theta) < CORRECT_PITCH_ROLL_ANGLES)
	{
	  digitalWrite(EMBEDED_LED_BLUE, HIGH);
	  digitalWrite(EMBEDED_LED_RED, LOW);
	}
	else
	{
	  digitalWrite(EMBEDED_LED_RED, HIGH);
	  digitalWrite(EMBEDED_LED_BLUE, LOW);
	}
}
