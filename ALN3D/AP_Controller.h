/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef AP_CONTROLLER_H_
#define AP_CONTROLLER_H_

// à 25HZ !!!
// 1.1, 	1.0, 	0.6 		(1.3), X,  X
// 1.75 	0.5 	0.45
#define KP 0.5
#define KI 0.5 // 0.5
#define KD 0.5

#define PID_IDX_LIMIT_MIN 0
#define PID_IDX_LIMIT_MAX 1

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
 * Information PID
 */
void PIDinformation(void);

/**
 * On affiche les ocmmandes PID
 */
void DisplayPIDControl(HardwareSerial *ser = &Serial);

#endif
