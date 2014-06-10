/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/**
 *	Fonction mathématiques supplémentaires
 */

#ifndef QMath_h
#define QMath_h

/**
 * On récupère le sign d'un nombre
 */
#define sign(n) (n / abs(n))

/**
 * On contrain à [-1, +1]
 */
#define CT(val) constrain(val, -1.0, +1.0)

/**
 *	Convert the value x from range [min, max] to range [scaleMin, scaleMax]
 *	@param float x : Value to convert
 *	@param float min : from range min boundary
 *	@param float max : from range max boundary
 *	@param float scaleMin : to range min boundary
 *	@param float scaleMax : to range max boundary
 *
 *	@return float x' at the new scale
 */
float toScale(float x, float min, float max, float scaleMin, float scaleMax);

/**
 *	Convert the value x from range [min, max] to range [-1, +1] (cosinus, sinus)
 *	@param float x : Value to convert
 *	@param float min : from range min boundary
 *	@param float max : from range max boundary
 *
 *	@return float x' at the new scale [-1, +1]
 */
float toCircleScale(float x, float min, float max);

/**
 * Angle global
 * @param Angle_t phi
 * @param Angle_t theta
 */
Angle_t calculate_global_angle(Angle_t phi, Angle_t theta);

/************************/
/****** FUNCTIONS *******/
/************************/

/**
 *	Calculate Euler angles from accelerometers
 *	save angles in phi, theta, psi
 *
 *	(*phi) : angle between the pitch axis and the plan (orthogonal to gravity vector)
 *	(*theta) : angle between the roll axis and the plan (orthogonal to gravity vector)
 *	(*psi) : angle between the yaw axis and the plan (orthogonal to gravity vector)
 */
void Euler_Angles(float *phi, float *theta, float *psi);

/**
 *	If a value in radians is smaller than zero, it'll just add 2 PI for getting a positive value
 *	@param float rad (radians)
 */
float Trig_Correction(float rad);

/**
 * Low Pass Filter : Remove high-frequencies (Smooth)
 * @param alpha : coeff
 * @param In : input value
 * @param S : Last Smoothed value
 */
float LowPassFilter(float alpha, float In, float S);

/**
 * High Pass Filter : Remove low-frequencies
 * @param alpha : coeff
 * @param In : input value
 * @param LIn : last value
 * @param S : Last Filtered value
 */
float HighPassFilter(float alpha, float In, float LIn, float S);

/**
 * On calcul l'angle phi et theta en fonction de la gravité
 * @param fVector_t g : gravity vector
 * @param fVector_t anglesArray : phi, theta, psi
 */
void PhiThetaFromGravity(fVector_t g, fVector_t anglesArray);
void PhiThetaFromGravity(fVector_t g, float *phi, float *theta);

/**
 * Reconstruction gravité
 * @param fVector_t g : gravity vector
 * @param *phi, *theta : angles
 */
void RebuildGravity(fVector_t g, float phi, float theta);

#endif
