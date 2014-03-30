#include <Arduino.h>

#ifndef HCSR04_h
#define HCSR04_h

#define HC_MAX_TIMEOUT 37

/**
 *	Small Library for HCSR04 altimeter
 */
class HCSR04
{
	public:
		/**
		 *	Constructor
		 *	@param unsigned char echo : echo pin
		 *	@param unsigned char trig : trigger pin
		 *	@param unsigned char timeout : max pulse (ms)
		 */
		HCSR04(unsigned char echo, unsigned char trig, unsigned char timeout = HC_MAX_TIMEOUT);
		
		/**
		 *	Get the pulse length in the time
		 *	@return int µs
		 */
		unsigned int getDuration(void);
		
		/**
		 *	Calculate the distance from the Pulse in Millimeter
		 *	@return unsigned float (mm)
		 */
		unsigned long getDistanceMM(void);
		
		/**
		 *	Calculate the distance from the Pulse in Meter
		 *	@return unsigned float (cm)
		 */
		float getDistance(void);
		
	private:
		/**
		 *	Echo (Pulse) Pin
		 */
		unsigned char _echo;
		
		/**
		 *	Trigger pin
		 */
		unsigned char _trig;
		
		/**
		 *	Max pulse duration
		 */
		unsigned char _timeout;
};

#endif
