/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef Constants_h
#define Constants_h

/**
 * System
 */
#define SYS_UNDEFINED 	0 // status indéfini
#define SYS_CONFIG 		1 // système en mode configuration
#define SYS_ON 			2 // système en fonctionnement normal
#define SYS_PAUSE 		3 // système en pause
#define SYS_EMERGENCY 	4 // système en état d'urgence



/**
 * MPU6000 Calibration
 */
#define MPU6000_CALIBRATION_START_DELAY 100	// delai avant la calibration (en ms)
#define MPU6000_CALIBRATION_ITERATIONS 100 	// nombre d'échantillons
#define MPU6000_CALIBRATION_DELAY 10		// délai entre chaque

// default gyroscopes drift correction
#if ARDUIMU == BOARD1

#define GYRO_X_GAP 94
#define GYRO_Y_GAP 8
#define GYRO_Z_GAP -9

#else

#define GYRO_X_GAP 13
#define GYRO_Y_GAP 4
#define GYRO_Z_GAP -2

#endif

// temperature correction (°)
#define TEMPERATURE_GAP 0

// accelerometers corrections
#if ARDUIMU == BOARD_1 // IMU 1
#define G_ACCEL_X_MIN -8000
#define G_ACCEL_X_MAX 8560
#define G_ACCEL_Y_MIN -8100
#define G_ACCEL_Y_MAX 8230
#define G_ACCEL_Z_MIN -8200
#define G_ACCEL_Z_MAX 8600
#else // IMU 2
#define G_ACCEL_X_MIN -8200
#define G_ACCEL_X_MAX 8500
#define G_ACCEL_Y_MIN -8400
#define G_ACCEL_Y_MAX 8200
#define G_ACCEL_Z_MIN -8177
#define G_ACCEL_Z_MAX 9700
#endif

/**
 *	Gravity
 */
#define GRAVITY 9.81

/**
 * Magnétomètres
 */
#define KOG_MAGNETIC_DECLINATION_DEG 1.460 // déclinaison Kogenheim (°)
#define KOG_MAGNETIC_DECLINATION 0.05096361415 // déclinaison Kogenheim (rad)

#define MAGNETIC_DECLINATION KOG_MAGNETIC_DECLINATION // déclinaison par défaut


#endif
