/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef AP_FRAMEPOSITION_H_
#define AP_FRAMEPOSITION_H_

/**
 * Erreur d'intégration par seconde (en °)
 */
#define GYRO_INTEGRATION_ERROR 0.5

/**
 * Accélération (scaled, m.s^-2)
 */
extern fVector_t Accel;

/**
 * Accélération (normalized)
 */
extern fVector_t NormalizedAccel;

/**
 * Norme du vecteur accélération
 */
extern float acceleration_magnitude;

/**
 * Accélération subit par le drone
 */
extern fVector_t AccelSuppressed;

/**
 * accélération lors du calcul précédant
 */
extern fVector_t LastAcceleration;

/**
 * Filtre
 */
extern float AccelFilter;

/**
 * norme moyenne du vecteur accélération
 */
extern float average_gravity_magnitude;

/**
 * Vitesse angulaire (scaled, rad.s^-1)
 */
extern fVector_t Omega;

/**
 * Vitesse linéaire estimée
 */
//extern fVector_t Velocity;

/**
 * Position estimée
 */
//extern fVector_t Gamma;

/**
 *	Magnétomètres (scaled values from X, Y, Z)
 */
extern fVector_t Magn;

/**
 * Valeurs des magnétomètres
 */
extern fVector_t Magn_Row;

/**
 * Angles issuent de l'intégration des gyroscopes
 */
extern fVector_t IOmega;

/**
 * Erreur cumulée d'intégration des gyroscopes
 */
extern Angle_t gyroscopes_integration_error;

/**
 * différence d'angle avec la dernière mesure (accélération)
 */
extern Angle_t accel_delta_angle;

/**
 *  différence d'angle avec la dernière mesure (gyroscopes)
 */
extern Angle_t gyro_delta_angle;

/**
 *	Coordonnées du repère mobile (quadcopter)
 */
extern CoordinateSystem_t quadcopter_frame_pos;

/**
 * Vecteur accélération de pesanteur dans le repère RQ
 */
extern fVector_t Gravity;

/**
 * Dernier vecteur d'accélération de pesanteur dans le repère RQ
 */
extern fVector_t LastGravity;

/**
 * Vecteur virtuel du nord
 */
extern fVector_t VirtualNorth;

/**
 * dernière data d'intégration des gyroscopes
 */
extern LongMicroSec_t gyro_integ_last_sample;

/**
 * Angles corrigés
 */
extern Angle_t phi;
extern Angle_t theta;
extern Angle_t psi;

/**
 * Cap (azimut) (rad)
 */
extern Angle_t Azimut;

/**
 * Angle global (phi +. theta)
 */
extern Angle_t GlobalGapAngle;

// erreurs
extern Angle_t delta_global_err;
extern Angle_t delta_pitch_err;
extern Angle_t delta_roll_err;
extern Angle_t delta_psi_err;

/**
 * Altitude avec le sol
 */
extern Distance_t Altitude;

/**
 * Mise en place des fonctions de mesure dynamique
 */
void IMU_Init(void);

/**
 * On prend exclusivement les valeurs des accéléromètres pour calculer les angles
 */
void Apply_Accelerometers_Angles(void);

/**
 * Intégration les gyroscopes
 */
void Gyroscopes_Integration(void);

/**
 * On calcul et on corrige les angles pour être les plus proches possibles de la réalité
 */
void Normalize(void);

/**
 * Calcule l'angle global
 */
void calculate_global_gap_angle(void);

/**
 * display leds positions
 * led bleu ou rouge en fonction de la stabilité de l'appareil
 */
void update_position_leds(void);

#endif
