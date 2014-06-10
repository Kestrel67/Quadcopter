/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef MOTORS_H_
#define MOTORS_H_

#define MOTORS_LOWER_LIMIT	0
#define MOTORS_UPPER_LIMIT	100

/**
 * rapports cycliques des moteurs MA, MB, MC, MD
 */
extern iDutyCycle_t MotorsThrottle[4];

/**
 * commande minimale pour chaque moteur
 */
extern DutyCycle_t MotorsLowerLimit[4];

/**
 * commande maximale pour chaque moteur
 */
extern DutyCycle_t MotorsHigherLimit[4];

/**
 * On met à jour la commande des moteurs, on contraint et on applique
 */
void UpdateMotorsThrottle(void);

/**
 * On calcul la commande aux moteurs
 */
void CalculateMotorsThrottle(void);

/**
 * On applique les contraintes de DC
 */
void MotorsConstrains(void);

/**
 * On envoie les rapports cycliques de chaque moteur au slave
 */
void ApplyMotorsThrottle(void);

/**
 * on affiche les paramètres throttle des moteurs (DEBUG)
 */
void DisplayMotorsThrottle(HardwareSerial *ser = &Serial);

#endif


