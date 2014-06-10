/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef Types_h
#define Types_h

/**
 *	Pins arduinos (input, output)
 */
typedef uint8_t Pin_t;

/**
 *	Rapport cyclique
 *	0 > 255
 */
typedef uint8_t DutyCycle_t;

/**
 * Rapport cyclique étendus pour éviter les overflow
 */
typedef int iDutyCycle_t;

/**
 * Fréquence basse ~~ 65kHz
 */
typedef unsigned int LowFrequency;

/**
 *	Fréquence haute ~~4GHz
 */
typedef unsigned long HighFrequency;

/**
 *	Durée en millisecondes ms (int : 65535) ~~ +1,1 minutes
 */
typedef unsigned int MilliSec_t;

/**
 * Durée en millisecondes (ms mais relatif +/- 25 jours) : Pour le remains dans les timers
 */
typedef long RelativeMilliSec_t;

/**
 * 	Durée en millisecondes (long) ~~ 50 days
 */
typedef unsigned long LongMilliSec_t;

/**
 *	Durée en microsecondes ~~ 65 ms
 */
typedef unsigned int MicroSec_t;

/**
 *	Durée en microseconds (long) ~~ 71 minutes
 */
typedef unsigned long LongMicroSec_t;

/**
 * Durée en secondes (unsigned int)
 */
typedef unsigned int Sec_t;

/**
 *	fonction callback (sans argument, retourn void)
 */
typedef void (*callback_t)(void);

/**
 *	Petit nombre positif (1 octet)
 */
typedef uint8_t Tiny_t;

/**
 *	Petit nombre relatif (-128; +127)
 */
typedef int8_t SSigned_t;

/**
 *	Evènement
 */
typedef SSigned_t Event_t;

/**
 * Commande (8bits = 1 octet).
 */
typedef byte Command_t;

/**
 * Paramètre (8bits = 1 octet)
 */
typedef byte Parameter_t;

/**
 *	Adresse
 */
typedef uint8_t Address_t;

/**
 * Pourcentage : 0% à 100%
 */
typedef uint8_t Percentage_t;

/**
 * Pourcentage en float : 0% à 100%
 */
typedef float fPercentage_t;

/**
 * registre
 */
typedef uint8_t Reg_t;

/**
 * Vecteur de nombres à virgule
 */
typedef float fVector_t[3];

/**
 * Vecteur de nombres entiers
 */
typedef int Vector_t[3];

/**
 * Matrice de nombres à virgul
 */
typedef float fMatrix_t[3][3];

/**
 * Matrice de nombres à entiers
 */
typedef int Matrix_t[3][3];

/**
 * Repère géométrique orthonormé
 */
struct CoordinateSystem_s {
	fVector_t x ;
	fVector_t y; // x * y = 0
	fVector_t z; // z = (k) * (x /\ y)
};

/**
 * Type d'un repère géométrique
 */
typedef CoordinateSystem_s CoordinateSystem_t;

/**
 * Compteur max : 2**32 (4,2 milliards)
 */
typedef unsigned long Counter_t;

/**
 * Distance en mm
 */
typedef unsigned int Distance_mm_t;

/**
 * Distance en mètre
 */
typedef float Distance_t;

/**
 * Angle mathématique
 */
typedef float Angle_t;


/**
 *	Extern timer1Ccounter
 */
/** typedef void (*EndCaptureCallback_t)(unsigned int, uint8_t); **/

#endif