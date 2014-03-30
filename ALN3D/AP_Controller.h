/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef AP_CONTROLLER_H_
#define AP_CONTROLLER_H_

#define DEFAULT_ROLL_PITCH_P	1.1 // maybe more 1.3
#define DEFAULT_ROLL_PITCH_I	1.0
#define DEFAULT_ROLL_PITCH_D	0.6

#define LIMIT_MIN 0
#define LIMIT_MAX 1

#define SAFETY_MAX_ANGLE 25

/**
 * rapports cycliques des moteurs MA, MB, MC, MD
 */
extern DutyCycle_t MotorsThrottle[4];

// limites maximales et minimales des moteurs
extern DutyCycle_t MotorsLowerLimit[4];
extern DutyCycle_t MotorsHigherLimit[4];

// PID pitch
extern float KpPitch, KiPitch, KdPitch;

// PID roll
extern float KpRoll, KiRoll, KdRoll;

// PID yaw
extern float KpYaw, KiYaw, KdYaw;

// PID altitude
extern float KpAltitude, KiAltitude, KdAltitude;

// bornes des commandes PID
extern int PitchLimits[2], RollLimits[2], YawLimits[2], AltitudeLimits[2];

// PID in
extern float phi_in, theta_in, psi_in, altitude_in;

// PID setpoint
extern float phi_setpoint, theta_setpoint, psi_setpoint, altitude_setpoint;

// commandes PID (contrôle)
extern float phi_control, theta_control, psi_control, altitude_control;

// contrôleurs PID
extern QuadPID PitchController;
extern QuadPID RollController;
extern QuadPID YawController;
extern QuadPID AltitudeController;

/**
 * Mise en place des contrôleurs PID
 */
void PID_Init(void);

/**
 * On calcul les nouvelles commandes PID
 */
void PIDCompute(void);

/**
 * Mode manuel
 */
void PID_Manual(void);

/**
 * Mode automatique
 */
void PID_Automatic(void);

/**
 * On applique les contraintes de DC
 */
void MotorsConstrains(void);

/**
 * Contrôle de sécurité (angles)
 */
void SafetyAnglesControl(void);

/**
 * on affiche les paramètres throttle des moteurs (DEBUG)
 */
void DisplayMotorsThrottle(HardwareSerial *ser = &Serial);

#endif
