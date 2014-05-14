/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef MOVEFUNCTIONS_H_
#define MOVEFUNCTIONS_H_

/**
 * Go forward (eq.5a)
 * Angle_t angle : angle global (in)
 * Angle_t *phi : angle phi (out)
 * Angle_t *theta : angme theta (out)
 */
void go_forward(Angle_t angle, Angle_t *phi, Angle_t *theta);

/**
 * Go backward
 * @see go_forward
 */
void go_backward(Angle_t angle, Angle_t *phi, Angle_t *theta);

#endif
