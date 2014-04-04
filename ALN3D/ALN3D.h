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


// analyser
#define ANALYSER 1

// errors manager
#define ERRORS_MANAGER 0

// debug
#define DEBUG_MODE 0

// school, home
#define BOARD1 1
#define BOARD2 2

#define ARDUIMU BOARD2

// on vérifie qu'une application est active (analyser ou gestion des erreurs)
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
#include "CPU.h"
#include "ArduIMU.h"
#include "Warning.h"
#include "Dev.h"

#include "Events.h"
#include "Frequencies.h"

// system
#include "Procedure.h"
#include "System.h"
#include "Timers.h"

// com
#include "IO.h"
#include "SPIClasses.h"
#include "Commands.h"
#include "Communication.h"

// maths / physic
#include "AP_Math.h"
#include "AP_Vector.h"
#include "AP_Matrix.h"
#include "AP_RotationMatrix.h"
#include "AP_PID.h"
#include "AP_FramePosition.h"
#include "AP_Procedures.h"
#include "AP_Controller.h"
#include "AP_Python.h"

// accel, gyron, magn
#include <HMC5883L.h>
#include "MPU6000.h"

// timers
#include "MsTimer2.h"
#include "Timer1Counter.h"

// sensors
#include "Sensors.h"

// controller, analyseur
#include "Controller.h"
#include "Analyser.h"


/**
 * informations
 */
void ALN3D_Author(HardwareSerial *ser = &Serial);

#endif
