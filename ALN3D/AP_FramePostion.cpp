/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

fVector_t IOmega;

Angle_t gyroscopes_integration_error;

// acceleration
fVector_t Accel;
fVector_t NormalizedAccel;
float acceleration_magnitude;
fVector_t LastAcceleration;
fVector_t AccelSuppressed;
float AccelFilter;

// angular velocity
fVector_t Omega;

fVector_t Magn;		// scaled
fVector_t Magn_Row; // notscaled

LongMicroSec_t gyro_integ_last_sample;

fVector_t Gravity = {0.0, 0.0, -1.0};
fVector_t LastGravity = {0.0, 0.0, -1.0};

float average_gravity_magnitude;

fVector_t VirtualNorth = {1.0, 0.0, 0.0};

CoordinateSystem_t Quadcopter_Frame = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};

Angle_t accel_delta_angle;
Angle_t gyro_delta_angle;

Angle_t phi;
Angle_t theta;
Angle_t psi;
Angle_t Azimut;

Angle_t GlobalGapAngle;

Distance_t Altitude;

void IMU_Init(void)
{
	// the drone is supposed to be stable

	// calibration gyroscopes, accelerometers
	MPU6000_Gyro_Calibration();
	MPU6000_Corrections_Scale();

	// apply acceleration
	Apply_Accelerometers_Angles();

	// magnetomèters, azimut
	// ...

	// last integ time
	gyro_integ_last_sample = micros();
}

void Apply_Accelerometers_Angles(void)
{
	Vector_Normalize(Accel, NormalizedAccel);

	// on suppose : le drone subit un mouvement rectiligne uniforme ou est immobile
	Gravity[X] = NormalizedAccel[X];
	Gravity[Y] = NormalizedAccel[Y];
	Gravity[Z] = NormalizedAccel[Z];
}

void Gyroscopes_Integration(void)
{
	// période de sample
	unsigned long now = micros();
	float gyro_integration_period = (now - gyro_integ_last_sample) / 1000000.0;
	gyro_integ_last_sample = now;

	// intégration
	IOmega[X] += Omega[X] * gyro_integration_period;
	IOmega[Y] += Omega[Y] * gyro_integration_period;
	IOmega[Z] += Omega[Z] * gyro_integration_period;

	// erreur
	gyroscopes_integration_error += GYRO_INTEGRATION_ERROR / 180.0 * PI * gyro_integration_period;
}

void Normalize(void)
{
	// on met à jour la matrice de rotation
	update_rotation_matrix(IOmega[Y], IOmega[X], IOmega[Z]);

	// on applique la matrice de rotation au vecteur virtuel de pesanteur Gravity
	apply_rotation_matrix(Gravity);

	// variables d'integrations à 0
	IOmega[X] = IOmega[Y] = IOmega[Z] = 0;

	// on normalize le vecteur accélération
	Vector_Normalize(Accel, NormalizedAccel);

	// accélération subise par le drone
	/*
	AccelSuppressed[X] = Accel[X] - Gravity[X] * 9.81;
	AccelSuppressed[Y] = Accel[Y] - Gravity[Y] * 9.81;
	AccelSuppressed[Z] = Accel[Z] - Gravity[Z] * 9.81;
	*/

	// angles globaux (accel, gyros)
	accel_delta_angle = Vectors_Angle(Accel, LastAcceleration); // norme variable
	gyro_delta_angle = Vectors1_Angle(Gravity, LastGravity); // ||Gravity|| = ||LastGravity|| = 1

	// filtre
	AccelFilter = constrain(
			1 	- 1.0 * abs(gyro_delta_angle * RAD_TO_DEG) 			// coeff 1.0
				- 2.0 * abs(accel_delta_angle * RAD_TO_DEG)			// coeff 2.0
				- 2.0 * Vector_Error_Sum(Accel, LastAcceleration)	// coeff 2.0
		, 0.0, 1.0);

	// vérification du filtre
	if(isnan(AccelFilter))
		AccelFilter = 1.0;

	// on applique le filtre
	Gravity[X] = AccelFilter * NormalizedAccel[X] + (1.0 - AccelFilter) * Gravity[X];
	Gravity[Y] = AccelFilter * NormalizedAccel[Y] + (1.0 - AccelFilter) * Gravity[Y];
	Gravity[Z] = AccelFilter * NormalizedAccel[Z] + (1.0 - AccelFilter) * Gravity[Z];

	// on normalize le vecteur
	Vector_Normalize(Gravity, Gravity);

	// on corrige l'erreur d'intégration
	gyroscopes_integration_error *= (1.0 - AccelFilter);

	// on conserve les vecteurs
	Vector_Copy(Gravity, LastGravity);
	Vector_Copy(Accel, LastAcceleration);

	// on calcule les angles
	phi = atan2(-Gravity[X], -Gravity[Z]);
	theta = atan2(-Gravity[Y], -Gravity[Z]);
}

// on calcul l'angle global
void calculate_global_gap_angle(void)
{
	float phi1d2 = sqrt(phi);
	float theta1d2 = sqrt(theta);

	GlobalGapAngle = atan(phi1d2 * phi1d2 + theta1d2 * theta1d2);
}

// on met à jour les leds de position
void update_position_leds(void)
{
	if (abs(phi * RAD_TO_DEG) < 10 && abs(theta * RAD_TO_DEG) < 10)
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
