/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef AP_PID_H_
#define AP_PID_H_

/**
 * Mode automatique ou manuel
 */
#define QUADPID_AUTOMATIC 	1
#define QUADPID_MANUAL		0

/**
 * Mode direct ou inversé
 */
#define QUADPID_DIRECT		1
#define QUADPID_REVERSE		0

/**
 * PID - Proportionel Intégral Dérivé
 */
class QuadPID
{
public:
	MilliSec_t SamplePeriod;
	float *Input, *Output, *Setpoint;
	float LastInput, Iterm;
	float Kp, Ki, Kd;
	bool Mode, Direction;
	float OutMin, OutMax;

	/**
	 * On met en place le PID
	 * float kp, ki, kd
	 * float *input, output, setpoint
	 * MilliSec_t sample_period // par défaut de 50Hz, tunings en fonction de cette valeur
	 */
	QuadPID(float kp, float ki, float kd, float *input, float *output, float *setpoint, MilliSec_t sample_period = FREQUENCY_50Hz);

	/**
	 * Changement des coefficients Kp, Ki, Kd
	 */
	void SetTunings(float kp, float ki, float kd);

	/**
	 * Changement de mode, manual < > automatic
	 */
	void SetMode(bool mode = QUADPID_AUTOMATIC);

	/**
	 * Direction du contrôleur
	 */
	void SetDirection(bool direction = QUADPID_DIRECT);

	/**
	 * Limites
	 */
	void SetOutputLimits(float min = 0, float max = 255);

	/**
	 * Changement de la période de calcul
	 */
	void SetSamplePeriod(MilliSec_t new_sample_period);

	/**
	 * Calcule de la nouvelle commande
	 */
	bool Compute(void);

	/**
	 * On redémarre le PID
	 */
	void Reset(void);

	/**
	 * get functions
	 */
	float GetKp(void) const;
	float GetKi(void) const;
	float GetKd(void) const;
	bool GetMode(void) const;
	bool GetDirection(void) const;

};
#endif
