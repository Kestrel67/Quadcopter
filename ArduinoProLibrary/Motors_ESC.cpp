/*
 * Motors.cpp
 *
 *  Created on: 27 janv. 2014
 *      Author: Lucas
 */
#include <ArduinoProLibrary.h>

void esc_init(bool fast_init)
{
	stop_motors();

	APL_delay(ESC_INIT_DELAY);

	if (!fast_init)
	{
		// programmation et marche
		for(uint8_t pwm = 50; pwm < 100; pwm++)
		{
			DUTY(MA, pwm);
			DUTY(MB, pwm);
			DUTY(MC, pwm);
			DUTY(MD, pwm);

			// delai
			APL_delay(ESC_INC_DELAY);
		}

		APL_delay(ESC_INIT_DELAY);
	}



	// rapport cyclique avant démarrage
	DUTY(MA, MA_READY_STAGE);
	DUTY(MB, MB_READY_STAGE);
	DUTY(MC, MC_READY_STAGE);
	DUTY(MD, MD_READY_STAGE);
}

void stop_motors(void)
{
	// rapport cyclique de sécurité
	DUTY(MA, MA_STOP_STAGE);
	DUTY(MB, MB_STOP_STAGE);
	DUTY(MC, MC_STOP_STAGE);
	DUTY(MD, MD_STOP_STAGE);
}

void gradual_stop_motors(void)
{
	// à revoir

	stop_motors();
}

void DUTY(Pin_t motor, byte duty_cycle)
{
	// modification rapport cyclique
	analogWrite(motor, duty_cycle);
}

#if ESC_THROTTLE_RANGE_MODE == ESC_THROTTLE_RANGE_STATIC_MODE
void THRUST(Pin_t motor, byte thrust) // see excel document
{
	int tmp_duty_cycle;
	float a, b, c;

	switch(motor)
	{
	case MA:
		a = 59.0 / 255;
		b = 161;
		c = 0;
		break;
	case MB:
		a = 23.0 / 85;
		b = 149;
		c = 0;
		break;
	case MC:
		a = 23.0 / 85;
		b = 148;
		c = 0;
		break;
	case MD:
		a = 23.0 / 85;
		b = 149;
		c = 0;
		break;

	default:
		return;
	}

	tmp_duty_cycle = a * thrust + b; // round ?

	DUTY(motor, tmp_duty_cycle);
}
#else
void THRUST(Pin_t motor, byte thrust) // see excel document
{
	int tmp_duty_cycle;

	switch(motor)
	{
	case MA:
		tmp_duty_cycle = (ESC_A_MAX - ESC_A_MIN) * ((float) thrust) + ESC_A_MIN;
		break;
	case MB:
		tmp_duty_cycle = (ESC_B_MAX - ESC_B_MIN) * ((float) thrust) + ESC_BMIN;
		break;
	case MC:
		tmp_duty_cycle = (ESC_C_MAX - ESC_C_MIN) * ((float) thrust) + ESC_C_MIN;
		break;
	case MD:
		tmp_duty_cycle = (ESC_D_MAX - ESC_D_MIN) * ((float) thrust) + ESC_D_MIN;
		break;

	default:
		return;
	}

	DUTY(motor, tmp_duty_cycle);
}
#endif
