/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef FREQUENCIES_H_
#define FREQUENCIES_H_

/**
 *	Datas in MicroSec_t
 */
#define FREQUENCY_166microHz 60000 	// 1 call / 1 min
#define FREQUENCY_1call_1min 60000 	// 1 call / 1 min
#define FREQUENCY_100mHz 10000 		// 1 call / 10 sec
#define FREQUENCY_200mHz 5000 		// 1 call / 5 sec
#define FREQUENCY_500mHz 2000 		// 1 call / 2 sec

#define FREQUENCY_1MIN 60000 		// 1 call / 1 min
#define FREQUENCY_10SEC 10000 		// 1 call / 10 sec
#define FREQUENCY_5SEC 5000 		// 1 call / 5 sec
#define FREQUENCY_2SEC 2000 		// 1 call / 2 sec

#define FREQUENCY_1Hz 1000 			// 1 call / 1 sec
#define FREQUENCY_2Hz 500 			// 2 calls / 1 sec
#define FREQUENCY_4Hz 250 			// 4 calls / 1sec
#define FREQUENCY_5Hz 200 			// 5 calls / 1 sec

#define FREQUENCY_10Hz 100 			// 10 calls / 1 sec
#define FREQUENCY_20Hz 50 			// 20 calls / 1 sec
#define FREQUENCY_25Hz 40 			// 25 calls / 1 sec
#define FREQUENCY_40Hz 25 			// 40 calls / 1 sec
#define FREQUENCY_50Hz 20 			// 50 calls / 1 sec

#define FREQUENCY_100Hz 10 			// 100 calls / 1 sec
#define FREQUENCY_200Hz 5 			// 200 calls / 1 sec
#define FREQUENCY_250Hz 4 			// 250 calls / 1sec
#define FREQUENCY_333Hz 3 			// 333.33 calls / 1sec
#define FREQUENCY_500Hz 2 			// 500 calls / 1 sec
#define FREQUENCY_1000Hz 1 			// 1000 calls / 1sec

/**
 *	Timer principale
 */
#define FREQUENCY_SEQUENCER_TIMER				FREQUENCY_1000Hz

/**
 * Intégration des gyroscopes
 */
#define FREQUENCY_GYRO_INTEGRATION FREQUENCY_50Hz

/**
 * Acquisition de l'altitude
 */
#define FREQUENCY_SAMPLE_HC_SR04	FREQUENCY_2Hz

/**
 *	Acquisition des valeurs des gyroscopes et accéléromètres
 */
#define FREQUENCY_GET_MPU6000					FREQUENCY_50Hz

/**
 *	Acquisition des valeurs de magnétomètres
 */
#define FREQUENCY_GET_HMC5883L					FREQUENCY_50Hz

/**
 * Calcul des matrices de rotation et calcul des angles
 */
#define FREQUENCY_COMPUTE_ANGLES				FREQUENCY_50Hz

/**
 * Affichage des données via le port série
 */
#define FREQUENCY_SERIAL_DISPLAY_DATA			FREQUENCY_25Hz

/**
 * Analyse système
 */
#define FREQUENCY_CPU_ANALYSER					FREQUENCY_10Hz

/**
 * analyse des données séries entrantes
 */
#define FREQUENCY_SERIAL_OBSERVER				FREQUENCY_100Hz

/**
 * stabilisation
 */
#define FREQUENCY_STABILIZATION					FREQUENCY_50Hz


#endif /* FREQUENCIES_H_ */
