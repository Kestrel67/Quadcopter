/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

// Documentation / PID_Optimisations.doc

QuadPID::QuadPID(float kp, float ki, float kd, float *input, float *output, float *setpoint, MilliSec_t sample_period)
{
	// pointeurs, entrées, sorties consignes
	Input = input;
	Output = output;
	Setpoint = setpoint;

	// période de calcule par défaut 50Hz : 20ms
	DefaultSamplePeriod = SamplePeriod = sample_period;

	// mode automatique (par défaut)
	Mode = QUADPID_AUTOMATIC;

	// mise en place des paramètres
	SetTunings(kp, ki, kd);
	SetDirection(QUADPID_DIRECT);
	SetOutputLimits(0, 255);
}

// parmètres
void QuadPID::SetTunings(float kp, float ki, float kd)
{
	// > 0
	if (kp < 0 || ki < 0 || kd < 0) return;

	// en fonction de la période de calcul
	float ratio = ((float) DefaultSamplePeriod / (float) SamplePeriod);

	Kp = kp;
	Ki = ki * ratio;
	Kd = kd / ratio;

	// si le sens est inversé on inverse Kp, Ki, Kd
	if(Direction == QUADPID_REVERSE)
	{
		Kp = -Kp;
		Ki = -Ki;
		Kd = -Kd;
	}
}

// mode automatique ou manuel
void QuadPID::SetMode(bool mode)
{
	if (mode == QUADPID_AUTOMATIC && Mode == QUADPID_MANUAL)
	{
		Iterm = constrain(*Output, OutMin, OutMax);
		LastInput = *Input;
	}
	Mode = mode;
}

// direction : direct ou inversé
void QuadPID::SetDirection(bool direction)
{
	if (Mode == QUADPID_AUTOMATIC && direction != Direction)
	{
		Kp = -Kp;
		Ki = -Ki;
		Kd = -Kd;
	}

	Direction = direction;
}

// limites 0 à 255 pour un PWM
void QuadPID::SetOutputLimits(float min, float max)
{
	if (min >= max) return;

	OutMin = min;
	OutMax = max;

	if (Mode == QUADPID_AUTOMATIC)
	{
		*Output = constrain(*Output, OutMin, OutMax);
		Iterm = constrain(Iterm, OutMin, OutMax);
	}
}

// on change la période de calcule
void QuadPID::SetSamplePeriod(MilliSec_t new_sample_period)
{
	if (new_sample_period == SamplePeriod) return;

	// calcul ratio
	float ratio = ((float) new_sample_period / (float) SamplePeriod);

	// coeffs
	Ki *= ratio;
	Kd /= ratio;

	SamplePeriod = new_sample_period;
}

// calcule de la commande
bool QuadPID::Compute(void)
{
	if (Mode == QUADPID_MANUAL) return false;

	float input = *Input;

	float dt = SamplePeriod / 1000.0; // en secondes

	float epsilon = *Setpoint - input; // erreur

	// terme intégral
	Iterm += (epsilon * dt * Ki);
	Iterm = constrain(Iterm, OutMin, OutMax);

	// terme dérivé
	float deltaInput = (input - LastInput) / dt;

	// commande
	*Output = Kp * epsilon + Iterm - deltaInput * Kd; // c(t) = Kp * err(t) + Ki * integ[0, t) (err(t) * DT) + Kd * Derr(t) / DT
	*Output = constrain(*Output, OutMin, OutMax);

	LastInput = input;

	return true;
}

// on redémarre le PID
void QuadPID::Reset(void)
{
	Iterm = LastInput = 0;
}

// méthodes d'accès
float QuadPID::GetKp(void) const { return Kp; }
float QuadPID::GetKi(void) const { return Ki; }
float QuadPID::GetKd(void) const { return Kd; }
bool QuadPID::GetMode(void) const { return Mode; }
bool QuadPID::GetDirection(void) const { return Direction; }

// info sur le PID
void QuadPID::info(HardwareSerial *ser)
{
	ser->print("PID : Kp, Ki, Kd : ");
	ser->print(Kp);
	ser->print(", ");
	ser->print(Ki);
	ser->print(", ");
	ser->print(Kd);
	ser->print("\t sample rate : ");
	ser->print(SamplePeriod);
	ser->print("\t Limits : ");
	ser->print(OutMin);
	ser->print(", ");
	ser->print(OutMax);
	ser->print("\t Direction : ");
	ser->println(Direction);
}
