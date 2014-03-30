/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/**
 * Timer1 counter(16bits), interrupt en pin 8
 * Capture on rising edge
 */

#ifndef Timer1Counter_h
#define Timer1Counter_h

#define TIMER1_PIN_CAPTURE 8

#define TIMER1_NO_PRESCALE 0b1
#define TIMER1_PRESCALE_8 0b10
#define TIMER1_PRESCALE_64 0b11
#define TIMER1_PRESCALE_256 0b100
#define TIMER1_PRESCALE_1024 0b101

/**
 * type de la callback à appelée à la fin de la capture
 * @param counter : valeur du compteur du timer1
 * @param uint8_t : nombre de fois que le timer est passé en overflow
 */
typedef void (*EndCaptureCallback_t)(unsigned int counter, uint8_t overflows);

/**
 * prescaler couramment utilisé
 */
extern byte timer1_prescale_bits;

/**
 * précision de la capture
 */
extern unsigned long timer1_precision;

/**
 * nombre de fois que le timer est passé en overflow
 */
extern byte timer1_overflows;

/**
 * valeur du compteur du timer1 quand le signal tombe
 */
extern unsigned int timer1_counter;

/**
 * fonction à appeler à la fin de la capture
 */
extern EndCaptureCallback_t timer1_callback;


/**
 * on initialise le timer1
 * @param byte : prescale
 * @param EndCaptureCallback_t : callback function (called at the end of the capture)
 */
void set_timer1_counter(byte prescale = TIMER1_PRESCALE_8, EndCaptureCallback_t callback = false);

/**
 *	on démarre la capture
 */
void timer1_start_capture(void);

/**
 * interruption appelée à la fin de la capture
 */
void timer1_capture_interrupt(void);

/**
 * on calcul la durée du signal en microsecondes
 * @param unsigned int counter
 * @param byte overflow
 * @return LongMicroSec_t (in microseconds µs)
 */
LongMicroSec_t timer1_calculate_duration(unsigned int counter, byte overflow);


#endif
