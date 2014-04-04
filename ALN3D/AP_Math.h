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
 * vector access constants
 */
#define X 0
#define Y 1
#define Z 2

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
 *	phi : angle between the pitch axis and the plan (orthogonal to gravity vector)
 *	theta : angle between the roll axis and the plan (orthogonal to gravity vector)
 *	psi : angle between the yaw axis and the plan (orthogonal to gravity vector)
 */
void Euler_Angles(void);

/**
 * Euler phi angle
 */
float phi_angle(float x, float y, float z);

/**
 * Euler theta angle
 */
float theta_angle(float x, float y, float z);

/**
 * Euler psi angle
 */
float psi_angle(float x, float y, float z);


/************************/
/******** AZIMUT ********/
/************************/

/**
 *	Calculate Heading with Magnetic north, arround Yaw (Z axis, default)
 *	save in heading
 */
void Heading(void);

/** ... Yaw Z axis  = Heading */
void HeadingYaw(void);

/** ... Pitch Y axis */
void HeadingPitch(void);

/** ... Roll X axis */
void HeadingRoll(void);

/**
 *	Calculate Heading with Magnetic north from Euler Angles
 */
void Heading_Tilt_Correction(void);


/************************/
/***** FORMATING ********/
/************************/

/**
 *	If a value in radians is smaller than zero, it'll just add 2 PI for getting a positive value
 *	@param float rad (radians)
 */
float Trig_Correction(float rad);

/**
 *	format Euler Angles
 */
void Euler_Angles_Format(char *buffer);

#endif
