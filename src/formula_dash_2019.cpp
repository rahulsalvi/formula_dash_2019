#include <stdint.h>

#include "WProgram.h"

#include "aemnet_utils.h"
#include "dashboard_shield.h"

#include "colors.h"

#define COOLANT 0
#define STATUS_BARS 1
#define SHIFT_LIGHTS 2
#define TACHOMETER 3

#define BRIGHTNESS 128

using aemnet_utils::fixed_point_t;
using dashboard_shield::dashboard_t;

static dashboard_t dashboard;

// TODO remove this and do real math
inline float fixed_to_float(fixed_point_t a) {
    return a / 65536.0;
}

static uint8_t rpm_lut[14] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};
static uint8_t clt_lut[13] = {8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12};

void setup() {
    for (int i = 0; i < DS_RGB_LEDS; i++) { dashboard.rgb_leds[i] = DS_RGB_OFF; }
    for (int i = 0; i < DS_PIXEL_CHANNELS; i++) {
        for (int j = 0; j < DS_PIXELS_PER_CHANNEL; j++) {
            dashboard.pixel_channels[i].pixels[j].red = 0;
            dashboard.pixel_channels[i].pixels[j].grn = 0;
            dashboard.pixel_channels[i].pixels[j].blu = 0;
            dashboard.pixel_channels[i].pixels[j].wht = 0;
        }
    }
    aemnet_utils::begin();
    aemnet_utils::update();
    dashboard_shield::begin();
    dashboard_shield::update(dashboard);
}

int     counter = 0;
uint8_t blink   = 128;

void loop() {
    aemnet_utils::update();

    // reset all pixels
    for (int i = 0; i < DS_PIXEL_CHANNELS; i++) {
        for (int j = 0; j < DS_PIXELS_PER_CHANNEL; j++) {
            dashboard.pixel_channels[i].pixels[j].red = 0;
            dashboard.pixel_channels[i].pixels[j].grn = 0;
            dashboard.pixel_channels[i].pixels[j].blu = 0;
            dashboard.pixel_channels[i].pixels[j].wht = 0;
        }
    }

    // tachometer
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[10] = WHT(BRIGHTNESS);
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[11] = WHT(BRIGHTNESS);
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[12] = RED(BRIGHTNESS);
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[13] = RED(BRIGHTNESS);

    float   rpm     = fixed_to_float(aemnet_utils::rpm());
    uint8_t rpm_led = rpm / 958;
    if (rpm_led > 13) { rpm_led = 13; }
    *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[rpm_lut[rpm_led]] += GRN(BRIGHTNESS);

    /* for (int i = 0; i < rpm_led; i++) { */
    /*     *(uint32_t*)&dashboard.pixel_channels[TACHOMETER].pixels[rpm_lut[i]] += GRN(BRIGHTNESS);
     */
    /* } */

    // shift lights
    if (rpm > 10800) {
        if (blink >> 7) {
            for (int i = 0; i < 15; i++) {
                *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] = BLU(BRIGHTNESS);
            }
        }
        blink += 8;
    } else if (rpm > 10000) {
        for (int i = 0; i < 15; i++) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[i] = BLU(BRIGHTNESS);
        }
        blink = 128;
    } else {
        if (rpm > 9687.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[7] = RED(BRIGHTNESS);
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[8] = RED(BRIGHTNESS);
        }
        if (rpm > 9375) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[6] = RED(BRIGHTNESS);
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[9] = RED(BRIGHTNESS);
        }
        if (rpm > 9062.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[5] =
                GRN(BRIGHTNESS) + RED(BRIGHTNESS);
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[10] =
                GRN(BRIGHTNESS) + RED(BRIGHTNESS);
        }
        if (rpm > 8750) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[4] =
                GRN(BRIGHTNESS) + RED(BRIGHTNESS);
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[11] =
                GRN(BRIGHTNESS) + RED(BRIGHTNESS);
        }
        if (rpm > 8437.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[3]  = GRN(BRIGHTNESS);
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[12] = GRN(BRIGHTNESS);
        }
        if (rpm > 8125) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[2]  = GRN(BRIGHTNESS);
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[13] = GRN(BRIGHTNESS);
        }
        if (rpm > 7812.5) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[1]  = GRN(BRIGHTNESS);
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[14] = GRN(BRIGHTNESS);
        }
        if (rpm > 7500) {
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[0]  = GRN(BRIGHTNESS);
            *(uint32_t*)&dashboard.pixel_channels[SHIFT_LIGHTS].pixels[15] = GRN(BRIGHTNESS);
        }
    }

    // coolant gauge
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[9]  = WHT(BRIGHTNESS);
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[10] = WHT(BRIGHTNESS);
    *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[11] = WHT(BRIGHTNESS);

    float clt = fixed_to_float(aemnet_utils::coolant_temp_c());
    if (clt < 70) { clt = 70; }
    uint8_t clt_led = ((clt - 70) / 3);
    if (clt_led > 12) { clt_led = 12; }

    if (clt_led < 5) {
        *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[clt_lut[clt_led]] = BLU(BRIGHTNESS);
    } else if (clt_led < 8) {
        *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[clt_lut[clt_led]] = GRN(BRIGHTNESS);
    } else if (clt_led < 10) {
        *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[clt_lut[clt_led]] =
            RED(BRIGHTNESS) + GRN(BRIGHTNESS);
    } else {
        *(uint32_t*)&dashboard.pixel_channels[COOLANT].pixels[clt_lut[clt_led]] = RED(BRIGHTNESS);
    }

    // status bars
    float fpr = fixed_to_float(aemnet_utils::fuel_pressure());
    if (fpr < 40) {
        for (int i = 0; i < 8; i++) {
            *(uint32_t*)&dashboard.pixel_channels[STATUS_BARS].pixels[i] = RED(BRIGHTNESS);
        }
    }
    float bat = fixed_to_float(aemnet_utils::battery_voltage());
    if (bat < 12.4) {
        for (int i = 8; i < 16; i++) {
            *(uint32_t*)&dashboard.pixel_channels[STATUS_BARS].pixels[i] = RED(BRIGHTNESS);
        }
    }

    dashboard_shield::update(dashboard);
    delay(10);

    /* counter = counter + 25; */
    /* if (counter > 13500) { counter = 0; } */
}

int main() {
    setup();
    while (1) { loop(); }
}
