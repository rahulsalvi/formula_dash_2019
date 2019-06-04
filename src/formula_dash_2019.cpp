#include <stdint.h>

#include "WProgram.h"

#include "aemnet_utils.h"
#include "dashboard_shield.h"

#include "colors.h"
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

uint8_t state    = STATE_IDLE;
bool    ecu_on   = false;
bool    debug_on = false;

uint32_t enter_idle_ct  = ENTER_IDLE_CYCLES;
uint32_t enter_debug_ct = ENTER_DEBUG_CYCLES;
uint8_t  init_step      = 0;

void state_idle();
void state_init();
void state_normal();
void state_debug();

void draw_tachometer();
void draw_shift_lights();
void draw_coolant_gauge();
void draw_status_bars();
void draw_cel_codes();

inline void reset_dashboard() {
    memset((void*)&dashboard, 0, sizeof(dashboard_t));
}

void setup() {
    reset_dashboard();
    aemnet_utils::begin();
    dashboard_shield::begin();
    button_state = dashboard_shield::update(dashboard);
    state        = STATE_IDLE;
}

void loop() {
    reset_dashboard();
    uint8_t received = aemnet_utils::update();

    // determine ecu_on
    if (received) {
        ecu_on        = true;
        enter_idle_ct = ENTER_IDLE_CYCLES;
    } else if (!enter_idle_ct) {
        ecu_on = false;
    } else {
        enter_idle_ct -= 1;
    }

    // determine debug_on
    if (!get_button(DEBUG_ACTIVE, button_state)) {
        debug_on       = false;
        enter_debug_ct = ENTER_DEBUG_CYCLES;
    } else if (!enter_debug_ct) {
        debug_on = true;
    } else {
        enter_debug_ct -= 1;
    }

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
    delay(10);
}

void state_idle() {
    if (debug_on) {
        state = STATE_DEBUG;
    } else if (ecu_on) {
        state = STATE_INIT;
    }
}

void state_init() {
    static const uint8_t tach_lut[16]    = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};
    static const uint8_t coolant_lut[16] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};
    for (int i = 0; i < 16; i++) {
        *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[tach_lut[i]] =
            colors[init_sequence_tach[init_step][i]];
        *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[coolant_lut[i]] =
            colors[init_sequence_coolant[init_step][i]];
        *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] =
            colors[init_sequence_shift_lights[init_step][i]];
        *(uint32_t*)&dashboard.pixel_channels[STATUS_BARS].pixels[i] =
            colors[init_sequence_status_bars[init_step][i]];
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

    if (debug_on) {
        state = STATE_DEBUG;
    } else if (!ecu_on) {
        state = STATE_IDLE;
    }
}

void state_debug() {
    draw_tachometer();
    draw_cel_codes();
    draw_coolant_gauge();
    draw_status_bars();

    if (!debug_on) { state = ecu_on ? STATE_NORMAL : STATE_IDLE; }
}

void draw_tachometer() {
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[10] = colors[WHT];
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[11] = colors[WHT];
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[12] = colors[RED];
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[13] = colors[RED];

    float   rpm     = fixed_to_float(aemnet_utils::rpm());
    uint8_t rpm_led = rpm / 958;
    if (rpm_led > 13) { rpm_led = 13; }
    static uint8_t rpm_lut[14]       = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};
    static uint8_t rpm_color_lut[14] = {
        PRP, PRP, PRP, PRP, CYN, CYN, CYN, CYN, GRN, GRN, GRN, GRN, YLW, YLW};
    for (int i = 0; i <= rpm_led; i++) {
        *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[rpm_lut[i]] =
            colors[rpm_color_lut[i]];
    }
}

void draw_shift_lights() {
    float rpm = fixed_to_float(aemnet_utils::rpm());
    if (rpm > 10800) {
        for (int i = 0; i < 15; i++) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] = colors[BLU];
        }
    } else {
        if (rpm > 10387.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[7] = colors[RED];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[8] = colors[RED];
        }
        if (rpm > 9975) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[6] = colors[RED];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[9] = colors[RED];
        }
        if (rpm > 9562.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[5]  = colors[YLW];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[10] = colors[YLW];
        }
        if (rpm > 9150) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[4]  = colors[YLW];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[11] = colors[YLW];
        }
        if (rpm > 8737.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[3]  = colors[GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[12] = colors[GRN];
        }
        if (rpm > 8325) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[2]  = colors[GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[13] = colors[GRN];
        }
        if (rpm > 7912.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[1]  = colors[GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[14] = colors[GRN];
        }
        if (rpm > 7500) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[0]  = colors[GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[15] = colors[GRN];
        }
    }
}

void draw_coolant_gauge() {
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[9]  = colors[WHT];
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[10] = colors[WHT];
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[11] = colors[WHT];

    float clt = fixed_to_float(aemnet_utils::coolant_temp_c());
    if (clt < 70) { clt = 70; }
    uint8_t clt_led = ((clt - 70) / 3);
    if (clt_led > 12) { clt_led = 12; }
    static const uint8_t clt_lut[13]       = {8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};
    static const uint8_t clt_color_lut[13] = {
        BLU, BLU, BLU, BLU, BLU, GRN, GRN, GRN, YLW, YLW, RED, RED, RED};
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[clt_lut[clt_led]] =
        colors[clt_color_lut[clt_led]];
}

void draw_status_bars() {
    float   fpr       = fixed_to_float(aemnet_utils::fuel_pressure());
    uint8_t fpr_color = (fpr < 20) ? RED : (fpr < 40) ? YLW : OFF;
    for (int i = 0; i < 8; i++) {
        *(uint32_t*)&dashboard.pixel_channels[STATUS_BARS].pixels[i] = colors[fpr_color];
    }
    float   bat       = fixed_to_float(aemnet_utils::battery_voltage());
    uint8_t bat_color = (bat < 12.2) ? RED : (bat < 13.5) ? YLW : OFF;
    for (int i = 8; i < 16; i++) {
        *(uint32_t*)&dashboard.pixel_channels[STATUS_BARS].pixels[i] = colors[bat_color];
    }
}

void draw_cel_codes() {}

int main() {
    setup();
    while (1) { loop(); }
}
