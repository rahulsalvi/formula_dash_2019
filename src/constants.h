#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BRIGHTNESS 16

#define COOLANT 0
#define STATUS_BARS 1
#define SHIFT_LIGHTS 2
#define TACHOMETER 3

#define STARTER 0
#define DEBUG_ACTIVE 1
#define DEBUG_CONTROL 2

#define STATE_IDLE 0
#define STATE_INIT 1
#define STATE_NORMAL 2
#define STATE_DEBUG 3

#define ECU_ON_F_CYCLES 100
#define ECU_ON_T_CYCLES 1

#define DEBUG_ON_F_CYCLES 100
#define DEBUG_ON_T_CYCLES 100

#define CEL_CODES 48
#define CEL_OFFSET 0

#define CEL_FPR_BELOW_20 0
#define CEL_FPR_BELOW_20_CYCLES 1000
#define CEL_FPR_BELOW_40 1
#define CEL_FPR_BELOW_40_CYCLES 1000

#define DEBUG_CLEAR_CEL 0
#define DEBUG_INC_BRIGHTNESS 1
#define DEBUG_DEC_BRIGHTNESS 2

#endif // CONSTANTS_H
