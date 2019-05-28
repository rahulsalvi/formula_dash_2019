#include "WProgram.h"

#include "aemnet_utils.h"
#include "dashboard_shield.h"

using dashboard_shield::dashboard_t;

static dashboard_t dashboard;

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

void loop() {}

int main() {
    setup();
    while (1) { loop(); }
}
