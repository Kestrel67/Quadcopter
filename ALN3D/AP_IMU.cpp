/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

fVector_t Omega;	// angular velocity			(rad.s^-1)
fVector_t IOmega;	// angle from last mesure 	(rad)

fVector_t Accel;	// acceleration				(m.s^-2)
fVector_t LastAccel;// last acceleration		(m.s^-2)
fVector_t NormalizedAccel;	// acceleration ||a|| = 1	(m.s^-2 / 9.81)
fVector_t SmoothedAccel;	// filtered acceleration	(m.s^-2)

fVector_t Magn;		// scaled		(mG)
fVector_t Magn_Row; // notscaled	(mG)

fVector_t Gravity = {0.0, 0.0, -1.0};		// virtual gravity vector
fVector_t LastGravity = {0.0, 0.0, -1.0};	// last gravity

fVector_t VirtualAzimut = {1.0, 0.0, 0.0};	// virtual Azimut vector

Angle_t gyroscopes_integration_error;	// sum(i, t) [ DELTAgyro * dTau ]
LongMicroSec_t LastIMUExecution;		// IMU last calculation

Kalman KalmanPhi, KalmanTheta; // filtres de Kalman

fVector_t AccelAngles;	// angles directs issuent des accéléromètres
fVector_t GyroAngles;	// angles directs issent des gyroscopes

// angles filtrés
Angle_t phi;	// pitch (tanguage) (rad)
Angle_t theta;	// roll (roulis)	(rad)
Angle_t psi;	// yaw (lacet)		(rad)

Angle_t CDelta; // angle de la dernière rotation

void IMU_Init(bool calibrate)
{
	// the drone is supposed to be stable

	// calibration gyroscopes, accelerometers
	if (calibrate)	MPU6000_Gyro_Calibration();
	MPU6000_Read();
	MPU6000_Corrections_Scale();

	// apply acceleration
	Apply_Accelerometers_Angles();

	// angles issuent des accéléromètres
	AccelAngles[PHI] = asin(-NormalizedAccel[X]), AccelAngles[THETA] = asin(-NormalizedAccel[Y]);

	phi = AccelAngles[PHI];
	theta = AccelAngles[THETA];

// kalman filter
#if IMU_FILTER == KALMAN_FILTER
	KalmanPhi.setAngle(phi * RAD_TO_DEG);
	KalmanTheta.setAngle(theta * RAD_TO_DEG);
#endif

	// magnétomèters, azimut, ...

	// !!!! à enlever !!!! ????
	LastIMUExecution = micros();	// last integ time
}

void IMUExecution(void)
{
	// dt
	LongMicroSec_t now = micros();
	float dt = (now - LastIMUExecution) / 1000000.0;
	LastIMUExecution = now;

	MPU6000_Read();	// data in
	MPU6000_Corrections_Scale(); // scale
	Gyroscopes_Integration(dt);	// integration
	Normalize(dt); // normalization
}

void Apply_Accelerometers_Angles(void)
{
	Vector_Normalize(Accel, NormalizedAccel);

	// on suppose : le drone subit un mouvement rectiligne uniforme ou est immobile
	Gravity[X] = NormalizedAccel[X];
	Gravity[Y] = NormalizedAccel[Y];
	Gravity[Z] = NormalizedAccel[Z];
}

void Gyroscopes_Integration(float dt)
{
	// eq.1 : intégration
	IOmega[X] += Omega[X] * dt; // dt = integration period
	IOmega[Y] += Omega[Y] * dt;
	IOmega[Z] += Omega[Z] * dt;

	// erreur (eq.6)
	gyroscopes_integration_error += GYRO_INTEGRATION_ERROR / 180.0 * PI * dt;
}

void Normalize(float dt)
{
	// on met à jour la matrice de rotation
	update_rotation_matrix(IOmega[Y], IOmega[X], IOmega[Z]);

	// variables d'integrations à 0
	IOmega[X] = IOmega[Y] = IOmega[Z] = 0;

	// eq.3 : on applique la matrice de rotation au vecteur virtuel de pesanteur Gravity (et d'azimut)
	apply_rotation_matrix(Gravity);
	apply_rotation_matrix(VirtualAzimut);

	// on normalize le vecteur de gravité
	Vector_Normalize(Gravity, Gravity);

#if IMU_MODE == IMU_MODE_NORMAL

	// eq.11 : low pass filter on accelerometer data (to filter vibrations)
	SmoothedAccel[X] = (Accel[X] * (1 - LOWPASSFILTER_VAL)) + (SmoothedAccel[X] * LOWPASSFILTER_VAL);
	SmoothedAccel[Y] = (Accel[Y] * (1 - LOWPASSFILTER_VAL)) + (SmoothedAccel[Y] * LOWPASSFILTER_VAL);
	SmoothedAccel[Z] = (Accel[Z] * (1 - LOWPASSFILTER_VAL)) + (SmoothedAccel[Z] * LOWPASSFILTER_VAL);

	// on sauvegarde la dernière accélération (dt)
	Vector_Copy(SmoothedAccel, Accel);
	Vector_Normalize(SmoothedAccel, NormalizedAccel);

#if IMU_FILTER == COMPLEMENTARY_FILTER || IMU_FILTER == PROBABILISTIC_FILTER // Complementary Filter

	//angles globaux issuent des gyroscopes
	GyroAngles[PHI] = asin(-Gravity[X]), GyroAngles[THETA] = asin(-Gravity[Y]);
#endif


	// angles globaux issuent des accéléromètres
	AccelAngles[PHI] = asin(-NormalizedAccel[X]), AccelAngles[THETA] = asin(-NormalizedAccel[Y]);


#if IMU_FILTER == KALMAN_FILTER // Kalman : (eqsl.12) données en (°)

	float Kalphi = AccelAngles[PHI] * RAD_TO_DEG;
	float Kaltheta = AccelAngles[THETA] * RAD_TO_DEG;

	// dernières valeurs de phi et theta
	float oldtheta = theta, oldphi = phi;

	phi = KalmanPhi.getAngle(Kalphi, Omega[Y] /* * cos(oldtheta) */ * RAD_TO_DEG, dt) / RAD_TO_DEG;
	theta = KalmanTheta.getAngle(Kaltheta, Omega[X] /* * cos(oldphi) */ * RAD_TO_DEG, dt) / RAD_TO_DEG;


#elif IMU_FILTER == COMPLEMENTARY_FILTER
	// eq.13 : complementary filter
	float CF_Filter = COMPLEMENTARY_FILTER_VAL; // HIGH COEFF

	// GravityDeltaAngle[PHI]
	phi = CF_Filter * (GyroAngles[PHI] /*+ Omega[Y] * dt*/) + (1 - CF_Filter) * AccelAngles[PHI];
	theta = CF_Filter * (GyroAngles[THETA] /*+ Omega[X] * dt*/) + (1 - CF_Filter) * AccelAngles[THETA];

#else
	// eq.10 : filtre probabiliste
	float ProbabilisticFilter =
			1 - (	+1.0 * acos(constrain((Matrix_Trace(RotMat) + 1.0) / 2.0, -1.0, 1.0)) * RAD_TO_DEG // angle global
					+1.0 * abs(GRAVITY - Vector_Magnitude(Accel))	// norme du vecteur accélération
					+0.3 * abs(GyroAngles[PHI] - AccelAngles[PHI]) * RAD_TO_DEG	// angle relatif phi
					+0.3 * abs(GyroAngles[THETA] - AccelAngles[THETA]) * RAD_TO_DEG // angle relatif theta
			);

	// constrain + min val
	ProbabilisticFilter = constrain(ProbabilisticFilter, 0.0, 1 - PROBABILISTIC_FILTER_MIN_VAL) + PROBABILISTIC_FILTER_MIN_VAL;

	// application
	phi = ProbabilisticFilter * (AccelAngles[PHI]) + (1 - ProbabilisticFilter) * GyroAngles[PHI];
	theta = ProbabilisticFilter * (AccelAngles[THETA]) + (1 - ProbabilisticFilter) * GyroAngles[THETA];
#endif

	// calcul de l'angle de lacet
	psi = GyroAngles[PSI] = atan2(VirtualAzimut[Y], VirtualAzimut[X]);

	// on met à jour le vecteur de gravité virtuel
	Gravity[X] = -sin(phi);
	Gravity[Y] = -sin(theta);
	Gravity[Z] = -cos(phi) * cos(theta);

	// on garde l'ancien vecteur gravité
	Vector_Copy(Gravity, LastGravity);

#else
	// full GYRO
	phi = asin(-Gravity[X]);
	theta = asin(-Gravity[Y]);
	psi = atan2(VirtualAzimut[Y], VirtualAzimut[X]);
#endif
}

// on met à jour les leds de position
void update_position_leds(void)
{
	if (abs(phi * RAD_TO_DEG) < CORRECT_PITCH_ROLL_ANGLES && abs(theta * RAD_TO_DEG) < CORRECT_PITCH_ROLL_ANGLES)
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
