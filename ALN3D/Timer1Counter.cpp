/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include <ALN3D.h>

byte timer1_prescale_bits;

unsigned long timer1_precision;

uint8_t timer1_overflows;

unsigned int timer1_counter;

EndCaptureCallback_t timer1_callback;

void set_timer1_counter(byte prescale, EndCaptureCallback_t callback)
{
	// prescale or counter frequency
	timer1_prescale_bits = prescale;

	// callback
	timer1_callback = callback;

	// set input pin 8
	pinMode(TIMER1_PIN_CAPTURE, INPUT);

	// prescaler
	unsigned int prescaler;

	// prescale value
	switch (prescale)
	{
	case TIMER1_NO_PRESCALE:
		prescaler = 1;
		break;
	case TIMER1_PRESCALE_8:
		prescaler = 8;
		break;
	case TIMER1_PRESCALE_64:
		prescaler = 64;
		break;
	case TIMER1_PRESCALE_256:
		prescaler = 256;
		break;
	case TIMER1_PRESCALE_1024:
		prescaler = 1024;
		break;
	default:
		prescaler = 0;
	}

	// timer counter precision
	timer1_precision = prescaler * pow(10, 9) / F_CPU;

	// normal counter mode
	TCCR1A = 0;
}

void timer1_start_capture(void)
{
	// interruption flag to 0 (to prevent its execution when masking off)
	TIFR1 &= ~_BV(ICF1);

	// overflow flag to 0 (to prevent its execution)
	TIFR1 &= ~_BV(TOV1);

	// set prescale bits and edge capture
	TCCR1B = timer1_prescale_bits | _BV(ICES1);

	// enable overflow and capture interrupts
	TIMSK1 |= _BV(TOIE1) | _BV(ICIE1);
}

void timer1_capture_interrupt(void)
{
	// on rising edge
	if (TCCR1B & _BV(ICES1))
	{
		// reset counter
		TCNT1 = 0;

	 	// interrupt on the other edge
		TCCR1B &= ~_BV(ICES1);

		// reset overflow value
		timer1_overflows = 0;
	}
	else // falling edge
	{
		// we get the value of the counter
		timer1_counter = ICR1;

	    // mask interrupt capture
	    TIMSK1 &= ~_BV(ICIE1);

	    // stop timer counter
	    TCCR1B = 0;

	    // execute the callback function
	    timer1_callback(timer1_counter, timer1_overflows);
	}
}

LongMicroSec_t timer1_calculate_duration(unsigned int counter, uint8_t overflow)
{
	return ((counter + overflow * 65536) * timer1_precision) / 1000;
}

// Timer 1 interrupt vector
ISR(TIMER1_CAPT_vect)
{
	timer1_capture_interrupt();
}

// overflow interrupt
ISR(TIMER1_OVF_vect)
{
	timer1_overflows++;
};
