#include <stdint.h>

#include "EEPROM.h"
#include "WProgram.h"
#include "elapsedMillis.h"

#include "aemnet_utils.h"
#include "dashboard_shield.h"

#include "colors.h"
#include "condition_tracker.h"
#include "constants.h"

using aemnet_utils::fixed_point_t;
using dashboard_shield::button_state_t;
using dashboard_shield::dashboard_t;
using dashboard_shield::get_button;

dashboard_t    dashboard;
button_state_t button_state;

// TODO remove this and do real math
inline float fixed_to_float(fixed_point_t a) {
    return a / 65536.0;
}

uint8_t state;

condition_tracker_t ecu_on;
condition_tracker_t debug_on;
condition_tracker_t debug_pressed;
condition_tracker_t debug_short_held;
condition_tracker_t debug_long_held;

condition_tracker_t fpr_critical;
condition_tracker_t fpr_low;

uint8_t init_step    = 0;
int     color_offset = EEPROM.read(BRIGHTNESS_ADDR);

void state_idle();
void state_init();
void state_normal();
void state_debug();

void draw_tachometer();
void draw_shift_lights();
void draw_coolant_gauge();
void draw_status_bars();
void draw_errors();
void draw_starter_button();
void draw_debug_button();

void track_errors();

inline void reset_dashboard() {
    memset((void*)&dashboard, 0, sizeof(dashboard_t));
}

void setup() {
    aemnet_utils::begin();
    dashboard_shield::begin();
    reset_dashboard();
    button_state = dashboard_shield::update(dashboard);
    state        = STATE_IDLE;

    init_condition_tracker(ecu_on, ECU_ON_F_CYCLES, ECU_ON_T_CYCLES);
    init_condition_tracker(debug_on, DEBUG_ON_F_CYCLES, DEBUG_ON_T_CYCLES);
    init_condition_tracker(debug_pressed, 1, PRESSED_CYCLES);
    init_condition_tracker(debug_short_held, 1, SHORT_HELD_CYCLES);
    init_condition_tracker(debug_long_held, 1, LONG_HELD_CYCLES);

    init_condition_tracker(fpr_critical, FPR_CRITICAL_F_CYCLES, FPR_CRITICAL_T_CYCLES);
    init_condition_tracker(fpr_low, FPR_LOW_F_CYCLES, FPR_LOW_T_CYCLES);
}

void loop() {
    reset_dashboard();

    // determine ecu_on
    ecu_on.value = (aemnet_utils::update() != 0);
    track_condition(ecu_on);

    // determine debug_on
    debug_on.value = get_button(DEBUG_ACTIVE, button_state);
    track_condition(debug_on);

    switch (state) {
        case STATE_IDLE:
            state_idle();
            break;
        case STATE_INIT:
            state_init();
            break;
        case STATE_NORMAL:
            state_normal();
            break;
        case STATE_DEBUG:
            state_debug();
            break;
    }

    button_state = dashboard_shield::update(dashboard);
}

void reset_error_trackers();

void state_idle() {
    reset_error_trackers();
    if (debug_on.output) {
        state = STATE_DEBUG;
    } else if (ecu_on.output) {
        state = STATE_INIT;
    }
}

void state_init() {
    static const uint8_t tach_lut[16]    = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};
    static const uint8_t coolant_lut[16] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};
    for (int i = 0; i < 16; i++) {
        *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[tach_lut[i]] =
            colors[color_offset + init_sequence_tach[init_step][i]];
        *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[coolant_lut[i]] =
            colors[color_offset + init_sequence_coolant[init_step][i]];
        *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] =
            colors[color_offset + init_sequence_shift_lights[init_step][i]];
        *(uint32_t*)&dashboard.pixel_channels[STATUS_BARS].pixels[i] =
            colors[color_offset + init_sequence_status_bars[init_step][i]];
    }
    delay(35);
    init_step += 1;
    if (init_step == INIT_STEPS) {
        state     = STATE_NORMAL;
        init_step = 0;
    }
}

void state_normal() {
    draw_tachometer();
    draw_shift_lights();
    draw_coolant_gauge();
    draw_status_bars();
    draw_starter_button();

    track_errors();

    if (debug_on.output) {
        state = STATE_DEBUG;
    } else if (!ecu_on.output) {
        state = STATE_IDLE;
    }
}

int track_debug_button() {
    bool btn = get_button(DEBUG_CONTROL, button_state);

    debug_pressed.value = btn;
    track_condition(debug_pressed);

    debug_short_held.value = btn;
    track_condition(debug_short_held);

    debug_long_held.value = btn;
    track_condition(debug_long_held);

    if (!btn) {
        if (debug_long_held.output) {
            return DEBUG_LONG_HELD;
        } else if (debug_short_held.output) {
            return DEBUG_SHORT_HELD;
        } else if (debug_pressed.output) {
            return DEBUG_PRESSED;
        }
    }
    return DEBUG_NONE;
}

void clear_errors();

inline void inc_brightness() {
    color_offset += 8;
    if (color_offset < 0) { color_offset = 0; }
    if (color_offset > 248) { color_offset = 248; }
    EEPROM.update(BRIGHTNESS_ADDR, color_offset);
};

inline void dec_brightness() {
    color_offset -= 8;
    if (color_offset < 0) { color_offset = 0; }
    if (color_offset > 248) { color_offset = 248; }
    EEPROM.update(BRIGHTNESS_ADDR, color_offset);
};

int debug_control_function = DEBUG_INC_BRIGHTNESS;

void debug_long_held_action() {
    switch (debug_control_function) {
        case DEBUG_CLEAR_ERRORS:
            clear_errors();
            break;
        case DEBUG_INC_BRIGHTNESS:
            debug_control_function = DEBUG_DEC_BRIGHTNESS;
            break;
        case DEBUG_DEC_BRIGHTNESS:
            debug_control_function = DEBUG_CLEAR_ERRORS;
            break;
        default:
            debug_control_function = DEBUG_INC_BRIGHTNESS;
            break;
    }
}

void debug_short_held_action() {
    switch (debug_control_function) {
        case DEBUG_CLEAR_ERRORS:
            debug_control_function = DEBUG_INC_BRIGHTNESS;
            break;
        case DEBUG_INC_BRIGHTNESS:
            debug_control_function = DEBUG_DEC_BRIGHTNESS;
            break;
        case DEBUG_DEC_BRIGHTNESS:
            debug_control_function = DEBUG_CLEAR_ERRORS;
            break;
        default:
            debug_control_function = DEBUG_INC_BRIGHTNESS;
            break;
    }
}

void debug_pressed_action() {
    switch (debug_control_function) {
        case DEBUG_CLEAR_ERRORS:
            break;
        case DEBUG_INC_BRIGHTNESS:
            inc_brightness();
            break;
        case DEBUG_DEC_BRIGHTNESS:
            dec_brightness();
            break;
        default:
            debug_control_function = DEBUG_INC_BRIGHTNESS;
            break;
    }
}

void state_debug() {
    int debug_control = track_debug_button();
    switch (debug_control) {
        case DEBUG_LONG_HELD:
            debug_long_held_action();
            break;
        case DEBUG_SHORT_HELD:
            debug_short_held_action();
            break;
        case DEBUG_PRESSED:
            debug_pressed_action();
            break;
        default:
            break;
    }

    draw_tachometer();
    draw_errors();
    draw_coolant_gauge();
    draw_status_bars();
    draw_starter_button();
    draw_debug_button();

    track_errors();

    if (!debug_on.output) { state = (ecu_on.output ? STATE_NORMAL : STATE_IDLE); }
}

void draw_tachometer() {
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[10] = colors[color_offset + WHT];
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[11] = colors[color_offset + WHT];
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[12] = colors[color_offset + RED];
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[13] = colors[color_offset + RED];

    float   rpm     = fixed_to_float(aemnet_utils::rpm());
    uint8_t rpm_led = rpm / 958;
    if (rpm_led > 13) { rpm_led = 13; }
    static uint8_t rpm_lut[14]       = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};
    static uint8_t rpm_color_lut[14] = {
        PRP, PRP, PRP, PRP, CYN, CYN, CYN, CYN, GRN, GRN, GRN, GRN, YLW, YLW};
    for (int i = 0; i <= rpm_led; i++) {
        *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[rpm_lut[i]] =
            colors[color_offset + rpm_color_lut[i]];
    }
}

void draw_shift_lights() {
    float rpm = fixed_to_float(aemnet_utils::rpm());
    if (rpm > 10800) {
        for (int i = 0; i < 15; i++) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] =
                colors[color_offset + BLU];
        }
    } else {
        if (rpm > 10387.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[7] =
                colors[color_offset + RED];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[8] =
                colors[color_offset + RED];
        }
        if (rpm > 9975) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[6] =
                colors[color_offset + RED];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[9] =
                colors[color_offset + RED];
        }
        if (rpm > 9562.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[5] =
                colors[color_offset + YLW];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[10] =
                colors[color_offset + YLW];
        }
        if (rpm > 9150) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[4] =
                colors[color_offset + YLW];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[11] =
                colors[color_offset + YLW];
        }
        if (rpm > 8737.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[3] =
                colors[color_offset + GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[12] =
                colors[color_offset + GRN];
        }
        if (rpm > 8325) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[2] =
                colors[color_offset + GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[13] =
                colors[color_offset + GRN];
        }
        if (rpm > 7912.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[1] =
                colors[color_offset + GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[14] =
                colors[color_offset + GRN];
        }
        if (rpm > 7500) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[0] =
                colors[color_offset + GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[15] =
                colors[color_offset + GRN];
        }
    }
}

void draw_coolant_gauge() {
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[9]  = colors[color_offset + WHT];
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[10] = colors[color_offset + WHT];
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[11] = colors[color_offset + WHT];

    float clt = fixed_to_float(aemnet_utils::coolant_temp_c());
    if (clt < 70) { clt = 70; }
    uint8_t clt_led = ((clt - 70) / 3);
    if (clt_led > 12) { clt_led = 12; }
    static const uint8_t clt_lut[13]       = {8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};
    static const uint8_t clt_color_lut[13] = {
        BLU, BLU, BLU, BLU, BLU, GRN, GRN, GRN, YLW, YLW, RED, RED, RED};
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[clt_lut[clt_led]] =
        colors[color_offset + clt_color_lut[clt_led]];
}

void draw_status_bars() {
    float   fpr       = fixed_to_float(aemnet_utils::fuel_pressure());
    uint8_t fpr_color = (fpr < FPR_CRITICAL_PSI) ? RED : (fpr < FPR_LOW_PSI) ? YLW : OFF;
    for (int i = 0; i < 8; i++) {
        *(uint32_t*)&dashboard.pixel_channels[STATUS_BARS].pixels[i] =
            colors[color_offset + fpr_color];
    }
    float   bat       = fixed_to_float(aemnet_utils::battery_voltage());
    uint8_t bat_color = (bat < 12.2) ? RED : (bat < 13.5) ? YLW : OFF;
    for (int i = 8; i < 16; i++) {
        *(uint32_t*)&dashboard.pixel_channels[STATUS_BARS].pixels[i] =
            colors[color_offset + bat_color];
    }
}

void draw_errors() {
    for (int i = 0; i < 16; i++) {
        if (EEPROM.read(CEL_OFFSET + (i + 0))) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] +=
                colors[color_offset + RED];
        }
        if (EEPROM.read(CEL_OFFSET + (i + 16))) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] +=
                colors[color_offset + GRN];
        }
        if (EEPROM.read(CEL_OFFSET + (i + 32))) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] +=
                colors[color_offset + BLU];
        }
    }
}

void draw_starter_button() {
    float rpm                   = fixed_to_float(aemnet_utils::rpm());
    dashboard.rgb_leds[STARTER] = (rpm > 1000) ? DS_RGB_OFF : DS_RGB_GRN;
    for (int i = 0; i < CEL_CODES; i++) {
        if (EEPROM.read(CEL_OFFSET + i)) { dashboard.rgb_leds[STARTER] = DS_RGB_RED; }
    }
}

void draw_debug_button() {
    switch (debug_control_function) {
        case DEBUG_CLEAR_ERRORS:
            dashboard.rgb_leds[DEBUG_CONTROL] = DS_RGB_RED;
            break;
        case DEBUG_INC_BRIGHTNESS:
            dashboard.rgb_leds[DEBUG_CONTROL] = DS_RGB_GRN;
            break;
        case DEBUG_DEC_BRIGHTNESS:
            dashboard.rgb_leds[DEBUG_CONTROL] = DS_RGB_BLU;
            break;
        default:
            dashboard.rgb_leds[DEBUG_CONTROL] = DS_RGB_OFF;
            break;
    }
}

void track_errors() {
    float fpr     = fixed_to_float(aemnet_utils::fuel_pressure());
    bool  pump_on = aemnet_utils::fuel_pump_on();

    fpr_critical.value = (pump_on && (fpr < FPR_CRITICAL_PSI)) || fpr_critical.output;
    track_condition(fpr_critical);
    if (fpr_critical.output) { EEPROM.update(CEL_OFFSET + FPR_CRITICAL_CODE, 1); }

    fpr_low.value = (pump_on && (fpr < FPR_LOW_PSI)) || fpr_low.output;
    track_condition(fpr_low);
    if (fpr_low.output) { EEPROM.update(CEL_OFFSET + FPR_LOW_CODE, 1); }
}

void reset_error_trackers() {
    reset_condition_tracker(fpr_critical);
    reset_condition_tracker(fpr_low);
}

void clear_errors() {
    reset_error_trackers();
    for (int i = 0; i < CEL_CODES; i++) { EEPROM.update(CEL_OFFSET + i, 0); }
}

int main() {
    setup();
    elapsedMicros em;
    while (1) {
        if (em >= LOOP_PERIOD) {
            em = 0;
            loop();
        }
    }
}
