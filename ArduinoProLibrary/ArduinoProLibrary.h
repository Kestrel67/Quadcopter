/*
#if !defined(__AVR_ATmega32U4__)

#error Arduino not supported (Arduino Pro only)

#endif
*/

#ifndef OUTPUTCONTROLLER_H_
#define OUTPUTCONTROLLER_H_

#include <Arduino.h>

/**
 * On utiluse l'IR receiver
 */
#define ENABLE_IR_RECEIVER 0
#if ENABLE_IR_RECEIVER
#include <IRremote.h>
#endif

#include "../ALN3D/Types.h"
#include "../ALN3D/Frequencies.h"

#include "functions.h"
#include "IO.h"
#include "hardware_timers.h"
#include "System.h"
#include "Motors_ESC.h"
#include "Constants.h"
#include "Communication.h"
#include "Register.h"
#include "SPISlave.h"

#endif /* OUTPUTCONTROLLER_H_ */
