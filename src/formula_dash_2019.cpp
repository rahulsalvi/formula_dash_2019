#include <stdint.h>

#include "WProgram.h"

#include "aemnet_utils.h"
#include "dashboard_shield.h"

#include "colors.h"
#include "constants.h"

using aemnet_utils::fixed_point_t;
using dashboard_shield::dashboard_t;

static dashboard_t dashboard;

// TODO remove this and do real math
inline float fixed_to_float(fixed_point_t a) {
    return a / 65536.0;
}

static uint8_t rpm_lut[14] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};
static uint8_t clt_lut[13] = {8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};

#define STATE_IDLE 0
#define STATE_INIT 1
#define STATE_NORMAL 2
uint8_t state;

void state_idle();
void state_init();
void state_normal();

uint32_t recv_cycle_count = 300;
uint8_t  received         = 0;
int      init_step        = 0;
uint8_t  blink            = 128;

inline void reset_all_pixels() {
    for (int i = 0; i < DS_PIXEL_CHANNELS; i++) {
        for (int j = 0; j < DS_PIXELS_PER_CHANNEL; j++) {
            dashboard.pixel_channels[i].pixels[j].red = 0;
            dashboard.pixel_channels[i].pixels[j].grn = 0;
            dashboard.pixel_channels[i].pixels[j].blu = 0;
            dashboard.pixel_channels[i].pixels[j].wht = 0;
        }
    }
}

void setup() {
    for (int i = 0; i < DS_RGB_LEDS; i++) { dashboard.rgb_leds[i] = DS_RGB_OFF; }
    reset_all_pixels();
    aemnet_utils::begin();
    dashboard_shield::begin();
    dashboard_shield::update(dashboard);
    state = STATE_IDLE;
}

void loop() {
    reset_all_pixels();
    received = aemnet_utils::update();
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
    }
    dashboard_shield::update(dashboard);
    delay(10);
}

void state_idle() {
    if (received) {
        recv_cycle_count = 300;
        init_step        = 0;
        state            = STATE_INIT;
    }
}

static uint8_t tach_lut[16] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};

void state_init() {
    for (int i = 0; i < 16; i++) {
        *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[tach_lut[i]] =
            colors[init_sequence_tach[init_step][i]];
    }
    init_step += 1;
    if (init_step == INIT_STEPS) { state = STATE_NORMAL; }
}

void state_normal() {
    recv_cycle_count = (received ? 300 : recv_cycle_count - 1);
    if (!recv_cycle_count) { state = STATE_IDLE; }

    // tachometer
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[10] = colors[WHT];
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[11] = colors[WHT];
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[12] = colors[RED];
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[13] = colors[RED];

    float   rpm     = fixed_to_float(aemnet_utils::rpm());
    uint8_t rpm_led = rpm / 958;
    if (rpm_led > 13) { rpm_led = 13; }
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[rpm_lut[rpm_led]] += colors[GRN];

    // shift lights
    if (rpm > 10800) {
        if (blink >> 7) {
            for (int i = 0; i < 15; i++) {
                *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] = colors[BLU];
            }
        }
        blink += 8;
    } else if (rpm > 10000) {
        for (int i = 0; i < 15; i++) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] = colors[BLU];
        }
        blink = 128;
    } else {
        if (rpm > 9687.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[7] = colors[RED];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[8] = colors[RED];
        }
        if (rpm > 9375) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[6] = colors[RED];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[9] = colors[RED];
        }
        if (rpm > 9062.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[5]  = colors[YLW];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[10] = colors[YLW];
        }
        if (rpm > 8750) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[4]  = colors[YLW];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[11] = colors[YLW];
        }
        if (rpm > 8437.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[3]  = colors[GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[12] = colors[GRN];
        }
        if (rpm > 8125) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[2]  = colors[GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[13] = colors[GRN];
        }
        if (rpm > 7812.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[1]  = colors[GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[14] = colors[GRN];
        }
        if (rpm > 7500) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[0]  = colors[GRN];
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[15] = colors[GRN];
        }
    }

    // coolant gauge
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[9]  = colors[WHT];
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[10] = colors[WHT];
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[11] = colors[WHT];

    float clt = fixed_to_float(aemnet_utils::coolant_temp_c());
    if (clt < 70) { clt = 70; }
    uint8_t clt_led = ((clt - 70) / 3);
    if (clt_led > 12) { clt_led = 12; }

    if (clt_led < 5) {
        *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[clt_lut[clt_led]] = colors[BLU];
    } else if (clt_led < 8) {
        *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[clt_lut[clt_led]] = colors[GRN];
    } else if (clt_led < 10) {
        *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[clt_lut[clt_led]] = colors[YLW];
    } else {
        *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[clt_lut[clt_led]] = colors[RED];
    }

    // status bars
    float fpr = fixed_to_float(aemnet_utils::fuel_pressure());
    if (fpr < 40) {
        for (int i = 0; i < 8; i++) {
            *(uint32_t*)&dashboard.pixel_channels[STATUS_BARS].pixels[i] = colors[RED];
        }
    }
    float bat = fixed_to_float(aemnet_utils::battery_voltage());
    if (bat < 12.4) {
        for (int i = 8; i < 16; i++) {
            *(uint32_t*)&dashboard.pixel_channels[STATUS_BARS].pixels[i] = colors[RED];
        }
    }
}

int main() {
    setup();
    while (1) { loop(); }
}
