/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

#ifndef MOTORS_H_
#define MOTORS_H_

/**
 * indice de PWM dans le tableau motors_dc[4] correspondant à chaque moteur.
 */
#define MA_DC 0
#define MB_DC 1
#define MC_DC 2
#define MD_DC 3

/**
 * Ecart de sécurité et d'arret
 */
#define DC_SAFE_GAP 2
#define DC_STOP_GAP 10

/**
 *	Durée entre chaque incrémentation des ESC
 */
#define ESC_INIT_DELAY 	100
#define ESC_INC_DELAY	10

/**
 * Initialisation des ESC
 */
#define ESC_FAST_INIT 1
#define ESC_GRADUAL_INIT 0

/**
 * Durée entre chaque décrémentation des moteurs pour un arret progressif (ms)
 */
#define GRADUAL_MOTORS_STOP_DELAY 50

/**
 * Valeur de sécurité avant le démarrage des moteurs
 * valeur temporraire
 */
#define MA_START_STAGE 160
#define MB_START_STAGE 148
#define MC_START_STAGE 147
#define MD_START_STAGE 148

/**
 * Valeur de fin d'armement et de sécurité avant démarrage
 */
#define MA_READY_STAGE MA_START_STAGE - DC_SAFE_GAP
#define MB_READY_STAGE MB_START_STAGE - DC_SAFE_GAP
#define MC_READY_STAGE MC_START_STAGE - DC_SAFE_GAP
#define MD_READY_STAGE MD_START_STAGE - DC_SAFE_GAP

/**
 * Valeur d'arret des moteurs
 */
#define MA_STOP_STAGE MA_START_STAGE - DC_STOP_GAP
#define MB_STOP_STAGE MB_START_STAGE - DC_STOP_GAP
#define MC_STOP_STAGE MC_START_STAGE - DC_STOP_GAP
#define MD_STOP_STAGE MD_START_STAGE - DC_STOP_GAP

/**
 * Valeur d'arret global des moteurs
 */
#define M_GLOBAL_STOP 147 - DC_STOP_GAP

/**
 * valeur de décrémentation lors de l'arret progressif des moteurs
 */
#define DECREMENT_GAP 1


/**
 * Retourne les paramètres a et b, f(x) = ax + b tel que f(0) Mx_Min et f(255) Mx_Max
 */
#define throttle_a_coeff(min, max) ((max - min) / 255.0)
#define throttle_b_coeff(min, max) (min)

/**
 * Paramètre min et max des PWM des moteurs
 */
#define ESC_A_MIN 161
#define ESC_A_MAX 216

#define ESC_B_MIN 149
#define ESC_B_MAX 215

#define ESC_C_MIN 148
#define ESC_C_MAX 213

#define ESC_D_MIN 149
#define ESC_D_MAX 214

/**
 * Mise en place des ESC, initialisation et mise en place pour démarrage
 */
void esc_init(bool fast_init = ESC_FAST_INIT);

/**
 * On arrete les moteurs immédiatement (sécurité)
 */
void stop_motors(void);

/**
 * On arrete progressivement les moteurs
 */
void gradual_stop_motors(void);

/**
 * on change directement le rapport cyclique aux pins 3, 5, 6 et 9
 * @param Pin_t motor : moteur MA, MB, MC ou MD
 * @param byre duty_cycle, entre 0 et 255
 */
void DUTY(Pin_t motor, byte duty_cycle);

/**
 *	on change la poussé du moteur qui sera cnvertit en rapport cyclique
 * @param Pin_t motor : moteur MA, MB, MC ou MD
 * @param byre thrust, entre 0 et 255
 */
void THRUST(Pin_t motor, byte thrust);


#endif /* MOTORS_H_ */
