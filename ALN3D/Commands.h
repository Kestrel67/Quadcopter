/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/**
 * Commandes utilisées lors de la transmission drone < > sol
 */
#ifndef Commands_h
#define Commands_h

/**

 * Mask : si cmd & MASK_CMD_PARAMETER == 1 alors envoyer un paramètre à la suite
 */
#define MASK_CMD_PARAMETER B00100000

// refresh
#define MASK_CMD_REFRESH B00000000

// commandes réservées
#define CMD_RESERVED_1 B00000000
#define CMD_RESERVED_2 B00000001

// position manuelles
#define CMD_MANUAL_LEFT			B001111
#define CMD_MANUAL_RIGHT		B010000
#define CMD_MANUAL_FORWARD		B010001
#define CMD_MANUAL_BACKWARD		B010010

#define CMD_MANUAL_UP			B010011
#define CMD_MANUAL_DOWN			B010100
#define CMD_MANUAL_TURN_LEFT	B010101
#define CMD_MANUAL_TURN_RIGHT	B010110


// position configurées
#define CMD_CFG_ABOUT_TURN		B010111


// azimut avec les différents cadrans
#define CMD_CFG_AZIMUT			B100000
#define PARAM_NORTH				0
#define PARAM_NORTHWEST			32
#define PARAM_WEST				64
#define PARAM_SOUTHWEST			96
#define PARAM_SOUTH				128
#define PARAM_SOUTHEST			160
#define PARAM_EAST				192
#define PARAM_NORTHEAST			224

// altitude (unité ???)
#define CMD_CFG_ALTITUDE		B100001

// forcer l'angle sur pitch
#define CMD_CFG_PITCH			B100010

// roll
#define CMD_CFG_ROLL			B100011

// procédures
#define CMD_PROC_EMERGENCY		B000111
#define CMD_PROC_LANDING		B001000
#define CMD_PROC_TAKEOF			B001001
#define CMD_PROC_BATTERY		B001010

// état de communication
#define CMD_COM_OK				B000010
#define CMD_COM_ERROR			B000011
#define CMD_COM_BUSY			B000100
#define CMD_COM_DECREASE_FREQ	CMD_COM_BUSY
#define CMD_COM_READY			B000101
#define CMD_COM_INCREASE_FREQ	B000110

// erreurs, arret d'urgence
#define CMD_STOP				B011110
#define CMD_WARN_EMERGENCY		B011111

// modification des coefficients
#define CMD_CHANGE_PR_KP		B100110
#define CMD_CHANGE_PR_KI		B100111
#define CMD_CHANGE_PR_KD		B101000

// modifition du setpoint
#define CMD_PITCH_SETPOINT		B101100
#define CMD_ROLL_SETPOINT 		B101101
#define CMD_YAW_SETPOINT		B101110
#define CMD_ALTITUDE_SETPOINT	B101111

// on change le throttle moyen
#define CMD_CHANGE_AVG_THROTTLE B101001

// on change le status
#define CMD_CHANGE_STATUS		B101010

// ...
#define CMD_PARAM_SYS_UNDEFINED 	0 // status indéfini
#define CMD_PARAM_SYS_CONFIG 		1 // système en mode configuration
#define CMD_PARAM_SYS_ON 			2 // système en fonctionnement normal
#define CMD_PARAM_SYS_PAUSE 		3 // système en pause
#define CMD_PARAM_SYS_EMERGENCY 	4 // système en état d'urgence

#endif /* Commands_h */
