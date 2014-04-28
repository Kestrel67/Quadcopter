/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef AP_IMU_H_
#define AP_IMU_H_

#define GYRO_INTEGRATION_ERROR 0.1

#define LOWPASSFILTER_VAL 				0.750 		// 0.75
#define COMPLEMENTARY_FILTER_VAL 		0.990		// 0.98
#define PROBABILISTIC_FILTER_MIN_VAL	0.010		// 0.02

#define SAFETY_MAX_ANGLE 25 // angle maximale avant arrêt d'urgence
#define CORRECT_PITCH_ROLL_ANGLES	10 // angles pour allumer la led bleu

extern fVector_t Omega;					// angular velocity			(rad.s^-1)
extern fVector_t IOmega;				// angle from last mesure 	(rad)

extern fVector_t Accel;					// acceleration				(m.s^-2)
extern fVector_t LastAccel;				// last acceleration		(m.s^-2)
extern fVector_t NormalizedAccel;		// acceleration ||a|| = 1	(m.s^-2 / 9.81)
extern fVector_t SmoothedAccel;			// filtered acceleration	(m.s^-2)

extern fVector_t Magn;					// scaled		(mG)
extern fVector_t Magn_Row; 				// notscaled	(mG)

extern fVector_t Gravity;				// virtual gravity vector
extern fVector_t LastGravity;			// last gravity

extern fVector_t VirtualAzimut;			// virtual Azimut vector

extern Angle_t gyroscopes_integration_error;	// sum(i, t) [ DELTAgyro * dTau ]
extern LongMicroSec_t LastIMUExecution;			// IMU last calculation

extern Kalman KalmanPhi, KalmanTheta; 			// filtres de Kalman

extern fVector_t AccelAngles;			// angles directs issuent des accéléromètres
extern fVector_t GyroAngles;			// angles directs issent des gyroscopes

// angles filtrés
extern Angle_t phi;						// pitch (tanguage) (rad)
extern Angle_t theta;					// roll (roulis)	(rad)
extern Angle_t psi;						// yaw (lacet)		(rad)

extern Angle_t CDelta; 					// angle de la dernière rotation

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
 * On prend exclusivement les valeurs des accéléromètres pour calculer les angles
 */
void Apply_Accelerometers_Angles(void);

/**
 * Intégration les gyroscopes
 * Différence de temps en s
 */
void Gyroscopes_Integration(float dt);

/**
 * On calcul et on corrige les angles pour être les plus proches possibles de la réalité
 * Différence de temps en s
 */
void Normalize(float dt);

/**
 * display leds positions
 * led bleu ou rouge en fonction de la stabilité de l'appareil
 */
void update_position_leds(void);

#endif
