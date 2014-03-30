/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/**
 *	utilisation des magnétomètres et de l'HC-SR04
 *	@need : 1 EVENT, 1 TIMER
 */

#include "ALN3D.h"

#ifdef HMC5883L_h

// compass

// Store our compass as a variable.
HMC5883L compass;

int magnetometer_error = 0;

void HMC5883L_Init(void)
{
	// start I2C transmission
	Wire.begin();
	
	// Constructor
	compass = HMC5883L();
	
	// set the scale of the compass
	magnetometer_error = compass.SetScale(1.3);
	
	// Set the measurement mode to Continuous
	magnetometer_error = compass.SetMeasurementMode(Measurement_Continuous);
}

void HMC5883L_Read(void)
{
	//scaled values from compass
	MagnetometerScaled scaled = compass.ReadScaledAxis();
	Magn[X] = scaled.XAxis, Magn[Y] = -scaled.YAxis, Magn[Z] = scaled.ZAxis;
}

void HMC5883L_Read_notScaled(void)
{
	// not scaled values
	MagnetometerRaw raw = compass.ReadRawAxis();
	Magn_Row[X] = raw.XAxis, Magn_Row[Y] = -raw.YAxis, Magn_Row[Z] = raw.ZAxis;
}

void checkError(void)
{
	if (magnetometer_error != 0 and Serial)
		Serial.println(compass.GetErrorText(magnetometer_error));
}

#endif

/**
 * HC-SR04
 */
Distance_mm_t distance;

Pin_t hc_trigger_pin;

Event_t altitude_new_data_event = EVENT_NULL;

void initialize_hc_sr04(Pin_t trigger_pin, MilliSec_t sample_period, Event_t ev)
{
	// pin de déclenchement
	hc_trigger_pin = trigger_pin;

	// mise en place du pinmode
	pinMode(hc_trigger_pin, OUTPUT);

	// on enregistre un évènement attaché à la fonction de fin de trigger
	register_event(EVENT_HC_SR04_SAMPLE, hc_sr04_trigger);

	// on met en place le timer1 counter
	set_timer1_counter(HC_SR04_PRESCALER, hc_sr04_callback);

	// on met en place le timer qui déclenchera un signal pour activer l'HC-SR04 et prendre la mesure
	add_timer(EVENT_HC_SR04_SAMPLE, sample_period);

	// evènement appelé lorsque la mesure est effectuée
	altitude_new_data_event = ev;
}

void hc_sr04_callback(unsigned int counter, uint8_t over)
{
	// si le timer passe en overflow, la distance est érroné
	if (over)
		distance = 0;

	// sinon on calcule la distance en mm qui sépare le module du drone
	else
		// distance en mm
		distance = counter * timer1_precision * 0.000170 - INIT_ALTITUDE;

		// altitude en m
		Altitude = distance / 1000.0;

	// si il y a un évènement a appeler
	if (altitude_new_data_event != EVENT_NULL)
		event_queue(altitude_new_data_event);
}

void hc_sr04_trigger(void)
{
	// on génère une pulse (trigger de l'altimètre
	generate_pulse(hc_trigger_pin, HC_SR04_TRIGGER_PULSE_DURATION);

	// on démarrage le capture au niveau du timer1
	timer1_start_capture(); // pulse de 1ms, minimum 10 µs
}
