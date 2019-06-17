#include <stdint.h>

#include "EEPROM.h"
#include "WProgram.h"

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

uint8_t state = STATE_IDLE;

bool                ecu_on;
condition_tracker_t ecu_on_cond;

bool                debug_on;
condition_tracker_t debug_on_cond;

bool                debug_pressed;
condition_tracker_t debug_pressed_cond;

bool                debug_short_held;
condition_tracker_t debug_short_held_cond;

bool                debug_long_held;
condition_tracker_t debug_long_held_cond;

uint8_t color_offset = 8;

void state_idle();
void state_init();
void state_normal();
void state_debug();

void draw_tachometer();
void draw_shift_lights();
void draw_coolant_gauge();
void draw_status_bars();
void draw_cel_codes();
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

    init_condition_tracker(ecu_on_cond, ECU_ON_F_CYCLES, ECU_ON_T_CYCLES);
    init_condition_tracker(debug_on_cond, DEBUG_ON_F_CYCLES, DEBUG_ON_T_CYCLES);
    init_condition_tracker(debug_pressed_cond, 1, PRESSED_CYCLES);
    init_condition_tracker(debug_short_held_cond, 1, SHORT_HELD_CYCLES);
    init_condition_tracker(debug_long_held_cond, 1, LONG_HELD_CYCLES);
}

void loop() {
    reset_dashboard();

    // determine ecu_on
    ecu_on_cond.value = (aemnet_utils::update() != 0);
    ecu_on            = track_condition(ecu_on_cond);

    // determine debug_on
    debug_on_cond.value = get_button(DEBUG_ACTIVE, button_state);
    debug_on            = track_condition(debug_on_cond);

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
    delay(1);
}

void state_idle() {
    if (debug_on) {
        state = STATE_DEBUG;
    } else if (ecu_on) {
        state = STATE_INIT;
    }
}

uint8_t init_step = 0;

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
    delay(30);
    init_step += 1;
    if (init_step == INIT_STEPS) { state = STATE_NORMAL; }
}

void state_normal() {
    draw_tachometer();
    draw_shift_lights();
    draw_coolant_gauge();
    draw_status_bars();
    draw_starter_button();

    track_errors();

    if (debug_on) {
        state = STATE_DEBUG;
    } else if (!ecu_on) {
        state = STATE_IDLE;
    }
}

int track_debug_button() {
    bool btn = get_button(DEBUG_CONTROL, button_state);

    debug_pressed_cond.value = btn || debug_pressed;
    debug_pressed            = track_condition(debug_pressed_cond);

    debug_short_held_cond.value = btn || debug_short_held;
    debug_short_held            = track_condition(debug_short_held_cond);

    debug_long_held_cond.value = btn || debug_long_held;
    debug_long_held            = track_condition(debug_long_held_cond);

    int ret = DEBUG_NONE;
    if (!btn) {
        if (debug_long_held) {
            ret = DEBUG_LONG_HELD;
        } else if (debug_short_held) {
            ret = DEBUG_SHORT_HELD;
        } else if (debug_pressed) {
            ret = DEBUG_PRESSED;
        }
        if (ret) {
            debug_pressed    = false;
            debug_short_held = false;
            debug_long_held  = false;
        }
    }
    return ret;
}

void clear_cel(){};
void inc_brightness() {
    color_offset += 8;
};
void dec_brightness() {
    color_offset -= 8;
};

int  debug_control_function = DEBUG_INC_BRIGHTNESS;
void state_debug() {
    draw_tachometer();
    /* draw_cel_codes(); */
    /* draw_coolant_gauge(); */
    /* draw_status_bars(); */
    /* draw_starter_button(); */
    draw_debug_button();

    track_errors();

    int debug_control = track_debug_button();
    if (debug_control == DEBUG_LONG_HELD) {
        switch (debug_control_function) {
            case DEBUG_CLEAR_CEL:
                clear_cel();
                break;
            case DEBUG_INC_BRIGHTNESS:
                debug_control_function = DEBUG_DEC_BRIGHTNESS;
                break;
            case DEBUG_DEC_BRIGHTNESS:
                debug_control_function = DEBUG_CLEAR_CEL;
                break;
            default:
                debug_control_function = DEBUG_INC_BRIGHTNESS;
                break;
        }
    } else if (debug_control == DEBUG_SHORT_HELD) {
        switch (debug_control_function) {
            case DEBUG_CLEAR_CEL:
                debug_control_function = DEBUG_INC_BRIGHTNESS;
                break;
            case DEBUG_INC_BRIGHTNESS:
                debug_control_function = DEBUG_DEC_BRIGHTNESS;
                break;
            case DEBUG_DEC_BRIGHTNESS:
                debug_control_function = DEBUG_CLEAR_CEL;
                break;
            default:
                debug_control_function = DEBUG_INC_BRIGHTNESS;
                break;
        }
    } else if (debug_control == DEBUG_PRESSED) {
        switch (debug_control_function) {
            case DEBUG_CLEAR_CEL:
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

    if (!debug_on) { state = ecu_on ? STATE_NORMAL : STATE_IDLE; }
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
    uint8_t fpr_color = (fpr < 20) ? RED : (fpr < 40) ? YLW : OFF;
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

void draw_cel_codes() {
    /* for (int i = 0; i < 16; i++) { */
    /*     if (EEPROM.read(CEL_OFFSET + (1 * i))) { */
    /*         *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] += colors[color_offset
     * + GRN]; */
    /*     } */
    /*     if (EEPROM.read(CEL_OFFSET + (2 * i))) { */
    /*         *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] += colors[color_offset
     * + RED]; */
    /*     } */
    /*     if (EEPROM.read(CEL_OFFSET + (3 * i))) { */
    /*         *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] += colors[color_offset
     * + BLU]; */
    /*     } */
    /* } */
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
        case DEBUG_CLEAR_CEL:
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
    /* float rpm = fixed_to_float(aemnet_utils::rpm()); */
    /* float fpr = fixed_to_float(aemnet_utils::fuel_pressure()); */

    /* if (!EEPROM.read(CEL_FPR_BELOW_20)) { */
    /*     if (rpm > 1000 && fpr < 20) { */
    /*         cel_fpr_below_20_ct -= 1; */
    /*     } else { */
    /*         cel_fpr_below_20_ct = CEL_FPR_BELOW_20_CYCLES; */
    /*     } */
    /*     if (!cel_fpr_below_20_ct) { EEPROM.update(CEL_FPR_BELOW_20, 1); } */
    /* } */
    /* if (!EEPROM.read(CEL_FPR_BELOW_40)) { */
    /*     if (rpm > 1000 && fpr < 40) { */
    /*         cel_fpr_below_40_ct -= 1; */
    /*     } else { */
    /*         cel_fpr_below_40_ct = CEL_FPR_BELOW_40_CYCLES; */
    /*     } */
    /*     if (!cel_fpr_below_40_ct) { EEPROM.update(CEL_FPR_BELOW_40, 1); } */
    /* } */
}

int main() {
    setup();
    while (1) { loop(); }
}
