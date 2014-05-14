
/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#include "ALN3D.h"

// go forward
void go_forward(Angle_t angle, Angle_t *phi, Angle_t *theta)
{
	Angle_t tan_angle = tan(angle);

	(*phi) = (*theta) = - atan(sqrt(tan_angle * tan_angle) / 2.0); // (eq.5a)
}

// go backward (@see go_forward)
void go_backward(Angle_t angle, Angle_t *phi, Angle_t *theta)
{
	go_forward(- angle, phi, theta);
}
