/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

float toScale(float x, float min, float max, float scaleMin, float scaleMax)
{
	return (scaleMax - scaleMin) * (x - min) / (max - min) + scaleMin; // eq.7
}

float toCircleScale(float x, float min, float max)
{
	return 2 * ((x - min) / (max - min)) - 1; // eq.8
}

Angle_t calculate_global_angle(Angle_t phi, Angle_t theta)
{
	float phi1d2 = sqrt(phi);
	float theta1d2 = sqrt(theta);

	return atan(phi1d2 * phi1d2 + theta1d2 * theta1d2);
}

void Euler_Angles(void)
{
	// optimisation
	float x2 = pow(Accel[X], 2);
	float y2 = pow(Accel[Y], 2);
	float z2 = pow(Accel[Z], 2);

	phi = atan(Accel[X] / sqrt(y2 + z2));

	theta = atan(Accel[Y] / sqrt(x2 + z2));

	psi = atan(Accel[Z] / sqrt(x2 + y2));
}

float Trig_Correction(float rad)
{
	if (rad < 0)
		return rad + 2 * M_PI;
	return rad;
}

/**
 * Low Pass Filter : Remove high-frequencies (Smooth)
 * @param alpha : coeff
 * @param In : input value
 * @param *S : Last Smoothed value
 */
float LowPassFilter(float alpha, float In, float S)
{
	return alpha * S + (1 - alpha) * In;
}

/**
 * High Pass Filter : Remove low-frequencies
 * @param alpha : coeff
 * @param In : input value
 * @param LIn : last value
 * @param *S : Last Filtered value
 */
float HighPassFilter(float alpha, float In, float LIn, float S)
{
	return alpha * (S) + alpha * (In - LIn);
}
