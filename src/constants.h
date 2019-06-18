#ifndef CONSTANTS_H
#define CONSTANTS_H

#define LOOP_PERIOD 2000 // us

#define COOLANT 0
#define STATUS_BARS 1
#define SHIFT_LIGHTS 2
#define TACHOMETER 3

#define STARTER 1
#define DEBUG_ACTIVE 1
#define DEBUG_CONTROL 0

#define STATE_IDLE 0
#define STATE_INIT 1
#define STATE_NORMAL 2
#define STATE_DEBUG 3

#define ECU_ON_F_CYCLES 500
#define ECU_ON_T_CYCLES 1

#define DEBUG_ON_F_CYCLES 100
#define DEBUG_ON_T_CYCLES 100

#define PRESSED_CYCLES 5
#define SHORT_HELD_CYCLES 250
#define LONG_HELD_CYCLES 2500

#define CEL_CODES 48
#define CEL_OFFSET 0

#define FPR_CRITICAL_PSI 20
#define FPR_CRITICAL_F_CYCLES 99999999
#define FPR_CRITICAL_T_CYCLES 5000
#define FPR_CRITICAL_CODE 0

#define FPR_LOW_PSI 40
#define FPR_LOW_F_CYCLES 99999999
#define FPR_LOW_T_CYCLES 5000
#define FPR_LOW_CODE 1

#define DEBUG_CLEAR_ERRORS 0
#define DEBUG_INC_BRIGHTNESS 1
#define DEBUG_DEC_BRIGHTNESS 2

#define DEBUG_NONE 0
#define DEBUG_PRESSED 1
#define DEBUG_SHORT_HELD 2
#define DEBUG_LONG_HELD 3

#define BRIGHTNESS_ADDR 97

#endif // CONSTANTS_H
