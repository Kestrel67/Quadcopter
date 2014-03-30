/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

#ifndef Constants_h
#define Constants_h

/**
 * Corrections pour l'IMU N°1
 */

// delay avant la calibration (en ms)
#define MPU6000_CALIBRATION_START_DELAY 100

// nombre d'itérations à effectuer pour calculer la moyenne de calibration
#define MPU6000_CALIBRATION_ITERATIONS 100

// delai à attendre entre les itérarions de calibration(en ms)
#define MPU6000_CALIBRATION_DELAY 10

// default gyroscopes drift correction
#define GYRO_X_GAP 93
#define GYRO_Y_GAP 7
#define GYRO_Z_GAP -8

// temperature correction (°)
#define TEMPERATURE_GAP 0

// accelerometers corrections - IMU 1
#if ARDUIMU == BOARD_1
#define G_ACCEL_X_MIN -8000
#define G_ACCEL_X_MAX 8560
#define G_ACCEL_Y_MIN -8100
#define G_ACCEL_Y_MAX 8230
#define G_ACCEL_Z_MIN -8200
#define G_ACCEL_Z_MAX 8600

#else

#define G_ACCEL_X_MIN -8200
#define G_ACCEL_X_MAX 8500
#define G_ACCEL_Y_MIN -8400
#define G_ACCEL_Y_MAX 8200
#define G_ACCEL_Z_MIN -8177
#define G_ACCEL_Z_MAX 9700

#endif

// gravity on Z - IMU 2
#define GRAVITY 9.81


/**
 * SENSORS
 */

/**
	Not scaled :
	xmin:-647	xmax:641	ymin:-661	ymax:562	zmin:-382	zmax:709

	Scaled :
	each * 0.92 (gauss = 1.3)
**/


/**
 * Déclinaison
 */
#define KOG_MAGNETIC_DECLINATION_DEG 1.460 // Kogenheim

#define KOG_MAGNETIC_DECLINATION 0.05096361415 // Kogenheim

// par défaut
#define MAGNETIC_DECLINATION KOG_MAGNETIC_DECLINATION

// HMC5883L
#define G_COMPASS_X_MIN -590
#define G_COMPASS_X_MAX 620

// circle center (G_COMPASS_X_MIN + G_COMPASS_X_MAX ) / 2 = 30 / 2 = 15
#define X_OFFSET 15

#define G_COMPASS_Y_MIN -620
#define G_COMPASS_Y_MAX 540

// - 80 / 2 : -40
#define Y_OFFSET -40

#define G_COMPASS_Z_MIN -360
#define G_COMPASS_Z_MAX 650

// 290 / 2 : 145
#define Z_OFFSET 145

#define SCALE_MIN -1000
#define SCALE_MAX  1000


#endif /* CONSTANTS_H_ */
