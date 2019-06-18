#ifndef CONDITION_TRACKER_H
#define CONDITION_TRACKER_H

#include <stdint.h>

#define CONDITION_F 0
#define CONDITION_F_CT 1
#define CONDITION_T 2
#define CONDITION_T_CT 3

typedef struct condition_tracker_t {
    uint32_t counter;
    uint32_t threshold_t; // must be true for this many cycles
    uint32_t threshold_f; // must be false for this many cycles
    bool     value;       // condition value
    bool     output;      // output value
    uint8_t  state;
} condition_tracker_t;

void init_condition_tracker(condition_tracker_t& condition, uint16_t thresh_f, uint16_t thresh_t) {
    condition.counter     = thresh_t;
    condition.threshold_t = thresh_t;
    condition.threshold_f = thresh_f;
    condition.value       = false;
    condition.output      = false;
    condition.state       = CONDITION_F;
}

void track_condition(condition_tracker_t& condition) {
    switch (condition.state) {
        case CONDITION_F:
            condition.counter = condition.threshold_t;
            condition.state   = condition.value ? CONDITION_F_CT : CONDITION_F;
            break;
        case CONDITION_F_CT:
            condition.counter--;
            if (condition.counter) {
                condition.state = condition.value ? CONDITION_F_CT : CONDITION_F;
            } else {
                condition.state = CONDITION_T;
            }
            break;
        case CONDITION_T:
            condition.counter = condition.threshold_f;
            condition.state   = condition.value ? CONDITION_T : CONDITION_T_CT;
            break;
        case CONDITION_T_CT:
            condition.counter--;
            if (condition.counter) {
                condition.state = (condition.value) ? CONDITION_T : CONDITION_T_CT;
            } else {
                condition.state = CONDITION_F;
            }
            break;
    }
    condition.output = (condition.state == CONDITION_T) || (condition.state == CONDITION_T_CT);
}

#endif // CONDITION_TRACKER_H
