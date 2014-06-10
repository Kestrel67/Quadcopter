/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef AP_IMU_H_
#define AP_IMU_H_

#define GYRO_INTEGRATION_ERROR 0.1

// [0.85 -> 0.94] a = tau / (tau + dt) <=> Tau = a * dt / (1 - a)
#define ACCEL_TIME_CONSTANT				0.072
#define GYRO_TIME_CONSTANT				0.036
#define ACCEL_LOWPASSFILTER_VAL 		0.878 //FILTER_COEFFICIENT(ACCEL_TIME_CONSTANT, FREQUENCY_DYNAMIC / 1000.0)
#define GYRO_HIGHPASSFILTER_VAL 		0.995 		// [->] a = tau / (tau + dt) <=> rc = tau = dt * a / (1 - a)

#define FILTER_COEFFICIENT(TIME_CONSTANT, DT) (TIME_CONSTANT / (TIME_CONSTANT + float(DT)))

#define COMPLEMENTARY_FILTER_VAL 		0.990		// 0.990

#define PROBABILISTIC_FILTER_MIN_VAL	0.010		// 0.010

#define MAX_OMEGA_VELOCITY				0.5				// rad.s^-1
#define MAX_ACCEL_ACCELERATION			2.0 * GRAVITY	// m.s^-2

#define SAFETY_MAX_ANGLE 80 / RAD_TO_DEG 				// angle maximale avant arrêt d'urgence
#define CORRECT_PITCH_ROLL_ANGLES	10 / RAD_TO_DEG 	// angles stable

extern fVector_t Omega;					// angular velocity			(rad.s^-1)
extern fVector_t IOmega;				// angle from last mesure 	(rad)
extern fVector_t LastOmega;				// last angular velocity	(rad.s^-1)
extern fVector_t FilteredOmega;			// filtered angular velocity (rad.s^-1)
extern float HighPassFilterVal;			// valeur du coeeficient du HPF
extern float OmegaMagnitude; 			// magnitude of the current angular velocity (rad.s^-1)

extern fVector_t Accel;					// acceleration				(m.s^-2)
extern fVector_t LastAccel;				// last acceleration		(m.s^-2)
extern fVector_t NormalizedAccel;		// acceleration ||a|| = 1	(m.s^-2 / 9.81)
extern fVector_t SmoothedAccel;			// filtered acceleration	(m.s^-2)
extern float LowPassFilterVal;			// valeur du coeeficient du HPF
extern float AccelerationMagnitude;		// magnitude of the current acceleration (m.s^-2)

extern fVector_t Magn;					// scaled		(mG)
extern fVector_t Magn_Row; 				// notscaled	(mG)

extern fVector_t Gravity;				// virtual gravity vector
extern fVector_t LastGravity;			// last gravity

extern fVector_t VirtualAzimut;			// virtual Azimut vector

extern Angle_t gyroscopes_integration_error;	// sum(i, t) [ DELTAgyro * dTau ]
extern LongMicroSec_t LastIMUExecution;			// IMU last calculation

extern fVector_t AccelAngles;			// angles directs issuent des accéléromètres
extern fVector_t GyroAngles;			// angles directs issent des gyroscopes

// angles filtrés
extern Angle_t phi;						// pitch (tanguage) (rad)
extern Angle_t theta;					// roll (roulis)	(rad)
extern Angle_t psi;						// yaw (lacet)		(rad)
extern Angle_t delta;					// angle global de l'assiette (rad)

extern float qfilter; // filtre d'utilisation des gyroscopes

extern fMatrix_t GlobalRotMat; // matrice de rotation globale
/**
 * Mise en place des fonctions de mesure dynamique
 * @param bool calibrate : on calibre ou non
 */
void IMU_Init(bool calibrate = true);

/**
 * Calcul des angles
 */
void IMUExecution(void);

/**
 * On calcul et on corrige les angles pour être les plus proches possibles de la réalité
 * Différence de temps en s
 */
void Normalize(float dt);

/**
 * On prend exclusivement les valeurs des accéléromètres pour calculer les angles
 */
void Apply_Accelerometers_Angles(void);

/**
 * Intégration les gyroscopes
 * Différence de temps en s
 */
void Gyroscopes_Integration(float dt);

/**
 * On applique les matrices de rotation
 */
void DynamicRotations(void);

/**
 * On filtre les gyroscopes
 */
void FilterGyroscopes(float dt);

/**
 * display leds positions
 * led bleu ou rouge en fonction de la stabilité de l'appareil
 */
void update_position_leds(void);

#endif
