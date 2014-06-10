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
#define FREQUENCY_NONE			0		// disabled

#define FREQUENCY_166microHz 	60000 	// 1 call / 1 min
#define FREQUENCY_1call_1min 	60000 	// 1 call / 1 min

#define FREQUENCY_100mHz 		10000 	// 1 call / 10 sec
#define FREQUENCY_200mHz 		5000 	// 1 call / 5 sec
#define FREQUENCY_500mHz 		2000 	// 1 call / 2 sec

#define FREQUENCY_1MIN 		60000 		// 1 call / 1 min
#define FREQUENCY_10SEC 	10000 		// 1 call / 10 sec
#define FREQUENCY_5SEC 		5000 		// 1 call / 5 sec
#define FREQUENCY_2SEC 		2000 		// 1 call / 2 sec

#define FREQUENCY_1Hz 		1000 		// 1 call / 1 sec
#define FREQUENCY_2Hz 		500 		// 2 calls / 1 sec
#define FREQUENCY_4Hz 		250 		// 4 calls / 1sec
#define FREQUENCY_5Hz 		200 		// 5 calls / 1 sec

#define FREQUENCY_10Hz 		100 		// 10 calls / 1 sec
#define FREQUENCY_20Hz 		50 			// 20 calls / 1 sec
#define FREQUENCY_25Hz 		40 			// 25 calls / 1 sec
#define FREQUENCY_40Hz 		25 			// 40 calls / 1 sec
#define FREQUENCY_50Hz 		20 			// 50 calls / 1 sec

#define FREQUENCY_100Hz 	10 			// 100 calls / 1 sec
#define FREQUENCY_125Hz		8			// 125 calls / 1 sec
#define FREQUENCY_142Hz		7			// 142 calls / 1 sec
#define FREQUENCY_167Hz		6			// 167 calls / 1 sec
#define FREQUENCY_200Hz 	5 			// 200 calls / 1 sec
#define FREQUENCY_250Hz 	4 			// 250 calls / 1sec
#define FREQUENCY_333Hz 	3 			// 333.33 calls / 1sec
#define FREQUENCY_500Hz 	2 			// 500 calls / 1 sec
#define FREQUENCY_1000Hz 	1 			// 1000 calls / 1sec


#define PERIOD_1MS			1
#define PERIOD_2MS			2
#define PERIOD_3MS			3
#define PERIOD_4MS			4
#define PERIOD_5MS			5
#define PERIOD_6MS			6
#define PERIOD_7MS			7
#define PERIOD_8MS			8
#define PERIOD_9MS			9

#define PERIOD_10MS			10
#define PERIOD_15MS			15
#define PERIOD_20MS			20
#define PERIOD_25MS			25
#define PERIOD_30MS			30
#define PERIOD_40MS			40
#define PERIOD_50MS			50
#define PERIOD_60MS			60
#define PERIOD_70MS			70
#define PERIOD_75MS			75
#define PERIOD_80MS			80
#define PERIOD_85MS			85
#define PERIOD_90MS			90

#define PERIOD_100MS		100
#define PERIOD_150MS		150
#define PERIOD_200MS		200
#define PERIOD_250MS		250
#define PERIOD_300MS		300
#define PERIOD_400MS		400
#define PERIOD_500MS		500
#define PERIOD_600MS		600
#define PERIOD_700MS		700
#define PERIOD_750MS		750
#define PERIOD_800MS		800
#define PERIOD_850MS		850
#define PERIOD_900MS		900


/**
 * Fréquences utiles :
 */
#if SYSTEM_FREQUENCIES_MODE == SYSTEM_NORMAL_FREQUENCIES // NORMAL <--------------------------------------------

#define FREQUENCY_SEQUENCER_TIMER		FREQUENCY_1000Hz	// Timer principale

#define FREQUENCY_DYNAMIC				FREQUENCY_50Hz		// acquisition, intégration, matrice de rotation, angles, etc...

#define FREQUENCY_GET_HMC5883L			FREQUENCY_10Hz		// Acquisition valeurs HMC-5883L
#define FREQUENCY_SAMPLE_HC_SR04		FREQUENCY_2Hz		// Acquisition de l'altitude

#define FREQUENCY_SERIAL_OBSERVER		FREQUENCY_40Hz 		// serial données entrantes
#define FREQUENCY_SERIAL_DATA_OUT		FREQUENCY_5Hz		// serial : données sortantes // FREQUENCY_5Hz

#define FREQUENCY_ANALYSER				FREQUENCY_10Hz		// Analyse système
#define FREQUENCY_MANAGER				FREQUENCY_1Hz		// Manager système

#define FREQUENCY_PID_ROLL_PITCH		FREQUENCY_25Hz		// 50Hz --> 25Hz
#define FREQUENCY_PID_PITCH				FREQUENCY_PID_ROLL_PITCH	// pitch
#define FREQUENCY_PID_ROLL				FREQUENCY_PID_ROLL_PITCH	// roll
#define FREQUENCY_PID_YAW				FREQUENCY_25Hz		// 25Hz --> 10Hz

#define FREQUENCY_PID_ALTITUDE			FREQUENCY_2Hz		// max 2Hz

#define FREQUENCY_LED_POSITION			FREQUENCY_25Hz		// 24 Hz min

#elif SYSTEM_FREQUENCIES_MODE == SYSTEM_DEV_FREQUENCIES		// DEV <--------------------------------------------

#define FREQUENCY_SEQUENCER_TIMER		FREQUENCY_1000Hz	// Timer principale

#define FREQUENCY_DYNAMIC				FREQUENCY_100Hz		// acquisition, intégration, matrice de rotation, angles, etc...

#define FREQUENCY_GET_HMC5883L			FREQUENCY_NONE		// Acquisition valeurs HMC-5883L
#define FREQUENCY_SAMPLE_HC_SR04		FREQUENCY_NONE		// Acquisition de l'altitude

#define FREQUENCY_SERIAL_OBSERVER		FREQUENCY_20Hz 		// serial données entrantes commande : FREQ / 2
#define FREQUENCY_SERIAL_DATA_OUT		150					// serial : données sortantes // FREQUENCY_5Hz

#define FREQUENCY_ANALYSER				FREQUENCY_10Hz		// Analyse système
#define FREQUENCY_MANAGER				FREQUENCY_NONE		// Manager système

#define FREQUENCY_PID_ROLL_PITCH		FREQUENCY_25Hz		// 50Hz --> 25Hz
#define FREQUENCY_PID_PITCH				FREQUENCY_PID_ROLL_PITCH	// pitch
#define FREQUENCY_PID_ROLL				FREQUENCY_PID_ROLL_PITCH	// roll
#define FREQUENCY_PID_YAW				FREQUENCY_NONE		// 25Hz --> 10Hz

#define FREQUENCY_PID_ALTITUDE			FREQUENCY_NONE		// max 2Hz

#define FREQUENCY_LED_POSITION			FREQUENCY_25Hz		// 24 Hz min

#elif SYSTEM_FREQUENCIES_MODE == SYSTEM_FAST_FREQUENCIES // FAST <--------------------------------------------

#define FREQUENCY_SEQUENCER_TIMER		FREQUENCY_1000Hz	// Timer principale

#define FREQUENCY_DYNAMIC				FREQUENCY_250Hz		// acquisition, intégration, matrice de rotation, angles, etc...

#define FREQUENCY_GET_HMC5883L			FREQUENCY_200Hz		// Acquisition valeurs HMC-5883L
#define FREQUENCY_SAMPLE_HC_SR04		FREQUENCY_2Hz		// Acquisition de l'altitude

#define FREQUENCY_SERIAL_OBSERVER		FREQUENCY_100Hz 		// serial données entrantes
#define FREQUENCY_SERIAL_DATA_OUT		FREQUENCY_5Hz		// serial : données sortantes // FREQUENCY_5Hz

#define FREQUENCY_ANALYSER				FREQUENCY_20Hz		// Analyse système
#define FREQUENCY_MANAGER				FREQUENCY_1Hz		// Manager système

#define FREQUENCY_PID_ROLL_PITCH		FREQUENCY_200Hz		// 50Hz --> 25Hz
#define FREQUENCY_PID_PITCH				FREQUENCY_PID_ROLL_PITCH	// pitch
#define FREQUENCY_PID_ROLL				FREQUENCY_PID_ROLL_PITCH	// roll
#define FREQUENCY_PID_YAW				FREQUENCY_50Hz		// 25Hz --> 10Hz

#define FREQUENCY_PID_ALTITUDE			FREQUENCY_50Hz		// max 2Hz

#define FREQUENCY_LED_POSITION			FREQUENCY_100Hz		// 24 Hz min

#endif 


#endif // header
