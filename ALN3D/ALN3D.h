/**
 * @author : Dietrich Lucas (Kestrel)
 * @email : lucas.dietrich.pro@gmail.com
 * @website http://www.kestrel.fr
 */

/**
 *	Author : Dietrich Lucas
 *	Project : PPE
 *	Group members : Dantz Achille, Dietrich Lucas, Dussourd Nicolas
 *	C++ embedded application for ALN Quadcopter
 *	libraries : TimerOne.h, TimerThree.h, MsTimer2.h, SPI.h, Wire.h, HMC5883L.h, HCSR04.h, MPU6000.h, IRremote.h
 *	Maths/Physic Libraries : AP_*
 *
 *	<----------------------------------------->
 *
 *	@version 1.32 *
 *
 *	atmega328 (IMU, Mini, Pro Mini) attached constant __AVR_ATmega328P__
 *
 *	constrain();
 */

#ifndef ALN3D_h
#define ALN3D_h

// https://github.com/TKJElectronics


// IMU
#define IMU_MODE_NORMAL		1
#define IMU_MODE_FULL_GYRO  2

#define IMU_MODE IMU_MODE_NORMAL // <==============================================================================


// filters
#define KALMAN_FILTER 1	// filtre de kalman
#define COMPLEMENTARY_FILTER 2 // complementary filter
#define PROBABILISTIC_FILTER 3 // probabilistic filter

#define IMU_FILTER COMPLEMENTARY_FILTER // filtre // <==============================================================================


// command mode
#define CMD_IN_DEV	1
#define CMD_IN_PROD	2
#define CMD_IN_MODE	CMD_IN_PROD // <==============================================================================

// communication mode
#define COM_NONE 0
#define COM_VISUAL 1 // <:--
#define COM_PYTHON 2
#define COM_XBEE 3
#define COM_DEV	4
#define COM_ANALYSER 5
#define COM_PROCESSING 6
#define COM_DEBUG 7

#define COM_MODE COM_PYTHON // <==============================================================================

// fréquences :
#define SYSTEM_NORMAL_FREQUENCIES 1
#define SYSTEM_FAST_FREQUENCIES 2
#define SYSTEM_DEV_FREQUENCIES 3

#define SYSTEM_FREQUENCIES_MODE SYSTEM_DEV_FREQUENCIES

// analyser
#define ANALYSER 1	// <==============================================================================


// errors manager
#define ERRORS_MANAGER 0


// debug
#define DEBUG_MODE 0	// <==============================================================================


// dev, prod board
#define BOARD1 1
#define BOARD2 2


#define ARDUIMU BOARD2


// on vérifie qu'une application est active (analyseur, gestion des erreurs ou debug)
#define enabled_backapp(app) (app == 1)

// informations sur l'auteur
#define _ALN3D_Author "Dietrich Lucas"
#define _ALN3D_Author_Alias "Kestrel"
#define _ALN3D_Version 1.32

// inclusion des constantes de l'APL (protocole SPI, constantes de com etc...)
#define _INCLUDE_ARDUINO_PRO_LIBRARY_CONSTANTS 1
#if _INCLUDE_ARDUINO_PRO_LIBRARY_CONSTANTS == 1
#include "../ArduinoProLibrary/Constants.h"
#if !defined(_ARDUINO_PRO_LIBRARY_ID_CONSTANT)
#error erreur lors de l inclusion des constantes de la bibliotheque APL
#endif
#endif

// env
#include <Arduino.h>
#include <math.h>

// types, data, constants
#include "Types.h"
#include "Constants.h"
#include "Symbols.h"
#include "CPU.h"
#include "ArduIMU.h"
#include "Warning.h"
#include "SerialMessages.h"

#include "Events.h"
#include "Frequencies.h"

// system
#include "Procedure.h"
#include "System.h"
#include "Timers.h"

// com
#include "SPIClasses.h"
#include "Commands.h"
#include "Communication.h"

// maths / physic
#include "Kalman.h"
#include "AP_Math.h"
#include "AP_Vector.h"
#include "AP_Matrix.h"
#include "AP_RotationMatrix.h"
#include "AP_PID.h"
#include "AP_IMU.h"
#include "AP_Procedures.h"
#include "AP_Controller.h"
#include "AP_Python.h"

// move functions
#include "MoveFunctions.h"

// accel, gyro, magn
#include <HMC5883L.h>
#include "MPU6000.h"

// timers
#include <MsTimer2.h>
#include "Timer1Counter.h"

// sensors
#include "Sensors.h"
#include "Motors.h"

// programme principal
#include "Main.h"

// analyser
#include "Analyser.h"
#include "Manager.h"


#endif
