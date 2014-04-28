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

void Euler_Angles_Format(char *buffer)
{
	sprintf(buffer, "phi:%d\ttheta:%d  \tpsi:%d", int(phi * RAD_TO_DEG), int(theta * RAD_TO_DEG), int(psi * RAD_TO_DEG));
}
