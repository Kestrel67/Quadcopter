/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.infrarouges.fr
 */

/**
 * Autres capteurs
 * @need : 1EVENT, 1TIMER
 */

#ifndef Sensors_h
#define Sensors_h

/**
 *	indique s'il y a eu une érreur lors de la mise en place des magnétomètres
 */
extern int magnetometer_error;

/**
 *	initialisation du magnétomètre
 */
void HMC5883L_Init(void);

/**
 *	on lit les valeurs à l'echelle des magnétomètres et on place ces valeurs dans le vecteur Magn
 */
void HMC5883L_Read(void);

/**
 *	on lit les valeurs brutes des magnétomètres et on place ces valeurs dans le vecteur Magn_Row
 */
void HMC5883L_Read_notScaled(void);

/**
 *	si une erreur a eu lieu, cette fonction l'affiche via la communication série
 */
void checkError(void);

/**
 * HC-SR04
 */

/**
 * timer1 prescaler
 * PRESCALE_x	Freq		precision	overflow
 * 	1			16MHz		6.25 ns		409 µs
 * 	8			2MHz		500ns		32.7ms (~)
 * 	64			1Mhz		1µs			65.5ms (~)
 * 	256			62.5kHz 	16µs		1 s (~)
 * 	1024		15.625 kHz	64µs		4.2s (~)
 */
#define HC_SR04_PRESCALER TIMER1_PRESCALE_8

/**
 * Durée du signal haut de déclenchement pour le HC-SR04
 */
#define HC_SR04_TRIGGER_PULSE_DURATION 1

/**
 *	Altitude initiale du drone (à l'arrêt au niveau du sol) (en mm)
 */
#define INIT_ALTITUDE 10

/**
 * distance avec l'obstacle (in mm)
 */
extern Distance_mm_t distance;

/**
 * hc-sr04 trigger pin
 */
extern Pin_t hc_trigger_pin;

/**
 * evènement lancé s'il y a une nouvelle valeur d'altitude
 */
extern Event_t altitude_new_data_event;
/**
 * Initialize the HC-SR04
 * @param Pin_t : the trigger pin (digital Output)
 * @param MillisSec_t sample_period : sample periode (default : 2Hz)
 */
void initialize_hc_sr04(Pin_t trigger_pin = HC_SR04_TRIGGER_PIN, MilliSec_t sample_period = FREQUENCY_SAMPLE_HC_SR04, Event_t ev = EVENT_NULL);

/**
 * Callback appelé lors le signal de trigger doit être éteint
 * @param unsigned int counter (counter of the timer1 when the signal falled)
 * @param uint8_t over, number of time that the timer1 overflowed
 */
void hc_sr04_callback(unsigned int counter, uint8_t over);

/**
 * Callback appelée pour le calcul de la durée de l'impulsion et de la distance avec l'obstacle
 */
void hc_sr04_trigger(void);



#endif
