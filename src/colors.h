#ifndef COLORS_H
#define COLORS_H

#include <stdint.h>

#include "constants.h"

inline uint32_t red(uint8_t x) {
    return (((uint32_t)x) << 8);
}

inline uint32_t grn(uint8_t x) {
    return (((uint32_t)x) << 0);
}

inline uint32_t blu(uint8_t x) {
    return (((uint32_t)x) << 16);
}

inline uint32_t wht(uint8_t x) {
    return (((uint32_t)x) << 24);
}

#define OFF 0
#define RED 1
#define GRN 2
#define BLU 3
#define WHT 4
#define YLW 5
#define PRP 6
#define CYN 7

static const uint32_t colors[256] = {
    0,                   // off
    red(0),              // red
    grn(0),              // green
    blu(0),              // blue
    wht(0),              // white
    red(0) + grn(0),     // yellow
    red(0) + blu(0),     // purple
    grn(0) + blu(0),     // cyan
    0,                   // off
    red(7),              // red
    grn(7),              // green
    blu(7),              // blue
    wht(7),              // white
    red(7) + grn(7),     // yellow
    red(7) + blu(7),     // purple
    grn(7) + blu(7),     // cyan
    0,                   // off
    red(15),             // red
    grn(15),             // green
    blu(15),             // blue
    wht(15),             // white
    red(15) + grn(15),   // yellow
    red(15) + blu(15),   // purple
    grn(15) + blu(15),   // cyan
    0,                   // off
    red(23),             // red
    grn(23),             // green
    blu(23),             // blue
    wht(23),             // white
    red(23) + grn(23),   // yellow
    red(23) + blu(23),   // purple
    grn(23) + blu(23),   // cyan
    0,                   // off
    red(31),             // red
    grn(31),             // green
    blu(31),             // blue
    wht(31),             // white
    red(31) + grn(31),   // yellow
    red(31) + blu(31),   // purple
    grn(31) + blu(31),   // cyan
    0,                   // off
    red(39),             // red
    grn(39),             // green
    blu(39),             // blue
    wht(39),             // white
    red(39) + grn(39),   // yellow
    red(39) + blu(39),   // purple
    grn(39) + blu(39),   // cyan
    0,                   // off
    red(47),             // red
    grn(47),             // green
    blu(47),             // blue
    wht(47),             // white
    red(47) + grn(47),   // yellow
    red(47) + blu(47),   // purple
    grn(47) + blu(47),   // cyan
    0,                   // off
    red(55),             // red
    grn(55),             // green
    blu(55),             // blue
    wht(55),             // white
    red(55) + grn(55),   // yellow
    red(55) + blu(55),   // purple
    grn(55) + blu(55),   // cyan
    0,                   // off
    red(63),             // red
    grn(63),             // green
    blu(63),             // blue
    wht(63),             // white
    red(63) + grn(63),   // yellow
    red(63) + blu(63),   // purple
    grn(63) + blu(63),   // cyan
    0,                   // off
    red(71),             // red
    grn(71),             // green
    blu(71),             // blue
    wht(71),             // white
    red(71) + grn(71),   // yellow
    red(71) + blu(71),   // purple
    grn(71) + blu(71),   // cyan
    0,                   // off
    red(79),             // red
    grn(79),             // green
    blu(79),             // blue
    wht(79),             // white
    red(79) + grn(79),   // yellow
    red(79) + blu(79),   // purple
    grn(79) + blu(79),   // cyan
    0,                   // off
    red(87),             // red
    grn(87),             // green
    blu(87),             // blue
    wht(87),             // white
    red(87) + grn(87),   // yellow
    red(87) + blu(87),   // purple
    grn(87) + blu(87),   // cyan
    0,                   // off
    red(95),             // red
    grn(95),             // green
    blu(95),             // blue
    wht(95),             // white
    red(95) + grn(95),   // yellow
    red(95) + blu(95),   // purple
    grn(95) + blu(95),   // cyan
    0,                   // off
    red(111),            // red
    grn(111),            // green
    blu(111),            // blue
    wht(111),            // white
    red(111) + grn(111), // yellow
    red(111) + blu(111), // purple
    grn(111) + blu(111), // cyan
    0,                   // off
    red(119),            // red
    grn(119),            // green
    blu(119),            // blue
    wht(119),            // white
    red(119) + grn(119), // yellow
    red(119) + blu(119), // purple
    grn(119) + blu(119), // cyan
    0,                   // off
    red(127),            // red
    grn(127),            // green
    blu(127),            // blue
    wht(127),            // white
    red(127) + grn(127), // yellow
    red(127) + blu(127), // purple
    grn(127) + blu(127), // cyan
    0,                   // off
    red(135),            // red
    grn(135),            // green
    blu(135),            // blue
    wht(135),            // white
    red(135) + grn(135), // yellow
    red(135) + blu(135), // purple
    grn(135) + blu(135), // cyan
    0,                   // off
    red(143),            // red
    grn(143),            // green
    blu(143),            // blue
    wht(143),            // white
    red(143) + grn(143), // yellow
    red(143) + blu(143), // purple
    grn(143) + blu(143), // cyan
    0,                   // off
    red(151),            // red
    grn(151),            // green
    blu(151),            // blue
    wht(151),            // white
    red(151) + grn(151), // yellow
    red(151) + blu(151), // purple
    grn(151) + blu(151), // cyan
    0,                   // off
    red(159),            // red
    grn(159),            // green
    blu(159),            // blue
    wht(159),            // white
    red(159) + grn(159), // yellow
    red(159) + blu(159), // purple
    grn(159) + blu(159), // cyan
    0,                   // off
    red(167),            // red
    grn(167),            // green
    blu(167),            // blue
    wht(167),            // white
    red(167) + grn(167), // yellow
    red(167) + blu(167), // purple
    grn(167) + blu(167), // cyan
    0,                   // off
    red(175),            // red
    grn(175),            // green
    blu(175),            // blue
    wht(175),            // white
    red(175) + grn(175), // yellow
    red(175) + blu(175), // purple
    grn(175) + blu(175), // cyan
    0,                   // off
    red(183),            // red
    grn(183),            // green
    blu(183),            // blue
    wht(183),            // white
    red(183) + grn(183), // yellow
    red(183) + blu(183), // purple
    grn(183) + blu(183), // cyan
    0,                   // off
    red(191),            // red
    grn(191),            // green
    blu(191),            // blue
    wht(191),            // white
    red(191) + grn(191), // yellow
    red(191) + blu(191), // purple
    grn(191) + blu(191), // cyan
    0,                   // off
    red(199),            // red
    grn(199),            // green
    blu(199),            // blue
    wht(199),            // white
    red(199) + grn(199), // yellow
    red(199) + blu(199), // purple
    grn(199) + blu(199), // cyan
    0,                   // off
    red(207),            // red
    grn(207),            // green
    blu(207),            // blue
    wht(207),            // white
    red(207) + grn(207), // yellow
    red(207) + blu(207), // purple
    grn(207) + blu(207), // cyan
    0,                   // off
    red(215),            // red
    grn(215),            // green
    blu(215),            // blue
    wht(215),            // white
    red(215) + grn(215), // yellow
    red(215) + blu(215), // purple
    grn(215) + blu(215), // cyan
    0,                   // off
    red(223),            // red
    grn(223),            // green
    blu(223),            // blue
    wht(223),            // white
    red(223) + grn(223), // yellow
    red(223) + blu(223), // purple
    grn(223) + blu(223), // cyan
    0,                   // off
    red(231),            // red
    grn(231),            // green
    blu(231),            // blue
    wht(231),            // white
    red(231) + grn(231), // yellow
    red(231) + blu(231), // purple
    grn(231) + blu(231), // cyan
    0,                   // off
    red(239),            // red
    grn(239),            // green
    blu(239),            // blue
    wht(239),            // white
    red(239) + grn(239), // yellow
    red(239) + blu(239), // purple
    grn(239) + blu(239), // cyan
    0,                   // off
    red(247),            // red
    grn(247),            // green
    blu(247),            // blue
    wht(247),            // white
    red(247) + grn(247), // yellow
    red(247) + blu(247), // purple
    grn(247) + blu(247), // cyan
    0,                   // off
    red(255),            // red
    grn(255),            // green
    blu(255),            // blue
    wht(255),            // white
    red(255) + grn(255), // yellow
    red(255) + blu(255), // purple
    grn(255) + blu(255), // cyan
};

#define INIT_STEPS 42
static const uint8_t init_sequence_tach[INIT_STEPS][16] = {
    {WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, GRN, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, GRN, GRN, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, GRN, GRN, GRN, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, GRN, GRN, GRN, GRN, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, CYN, GRN, GRN, GRN, GRN, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, CYN, CYN, GRN, GRN, GRN, GRN, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, CYN, CYN, CYN, GRN, GRN, GRN, GRN, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, CYN, CYN, CYN, CYN, GRN, GRN, GRN, GRN, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, PRP, CYN, CYN, CYN, CYN, GRN, GRN, GRN, GRN, RED, RED},
    {WHT, WHT, WHT, WHT, PRP, PRP, CYN, CYN, CYN, CYN, GRN, GRN, GRN, GRN, RED, RED},
    {WHT, WHT, WHT, PRP, PRP, PRP, CYN, CYN, CYN, CYN, GRN, GRN, GRN, GRN, RED, RED},
    {WHT, WHT, PRP, PRP, PRP, PRP, CYN, CYN, CYN, CYN, GRN, GRN, GRN, GRN, RED, RED},
    {WHT, WHT, PRP, PRP, PRP, PRP, CYN, CYN, CYN, CYN, GRN, GRN, GRN, OFF, RED, RED},
    {WHT, WHT, PRP, PRP, PRP, PRP, CYN, CYN, CYN, CYN, GRN, GRN, OFF, OFF, RED, RED},
    {WHT, WHT, PRP, PRP, PRP, PRP, CYN, CYN, CYN, CYN, GRN, OFF, OFF, OFF, RED, RED},
    {WHT, WHT, PRP, PRP, PRP, PRP, CYN, CYN, CYN, CYN, OFF, OFF, OFF, OFF, RED, RED},
    {WHT, WHT, PRP, PRP, PRP, PRP, CYN, CYN, CYN, OFF, OFF, OFF, OFF, OFF, RED, RED},
    {WHT, WHT, PRP, PRP, PRP, PRP, CYN, CYN, OFF, OFF, OFF, OFF, OFF, OFF, RED, RED},
    {WHT, WHT, PRP, PRP, PRP, PRP, CYN, OFF, OFF, OFF, OFF, OFF, OFF, OFF, RED, RED},
    {WHT, WHT, PRP, PRP, PRP, PRP, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, RED, RED},
    {WHT, WHT, PRP, PRP, PRP, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, RED, RED},
    {WHT, WHT, PRP, PRP, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, RED, RED},
    {WHT, WHT, PRP, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, RED, RED},
    {WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, RED, RED}};

static const uint8_t init_sequence_coolant[INIT_STEPS][16] = {
    {WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, OFF},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, RED, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, YLW, RED, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, YLW, YLW, RED, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, GRN, YLW, YLW, RED, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, GRN, GRN, YLW, YLW, RED, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, WHT, GRN, GRN, GRN, YLW, YLW, RED, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, WHT, BLU, GRN, GRN, GRN, YLW, YLW, RED, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, WHT, BLU, BLU, GRN, GRN, GRN, YLW, YLW, RED, RED, RED},
    {WHT, WHT, WHT, WHT, WHT, BLU, BLU, BLU, GRN, GRN, GRN, YLW, YLW, RED, RED, RED},
    {WHT, WHT, WHT, WHT, BLU, BLU, BLU, BLU, GRN, GRN, GRN, YLW, YLW, RED, RED, RED},
    {WHT, WHT, WHT, BLU, BLU, BLU, BLU, BLU, GRN, GRN, GRN, YLW, YLW, RED, RED, RED},
    {WHT, WHT, WHT, BLU, BLU, BLU, BLU, BLU, GRN, GRN, GRN, YLW, YLW, RED, RED, OFF},
    {WHT, WHT, WHT, BLU, BLU, BLU, BLU, BLU, GRN, GRN, GRN, YLW, YLW, RED, OFF, OFF},
    {WHT, WHT, WHT, BLU, BLU, BLU, BLU, BLU, GRN, GRN, GRN, YLW, YLW, OFF, OFF, OFF},
    {WHT, WHT, WHT, BLU, BLU, BLU, BLU, BLU, GRN, GRN, GRN, YLW, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, BLU, BLU, BLU, BLU, BLU, GRN, GRN, GRN, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, BLU, BLU, BLU, BLU, BLU, GRN, GRN, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, BLU, BLU, BLU, BLU, BLU, GRN, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, BLU, BLU, BLU, BLU, BLU, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, BLU, BLU, BLU, BLU, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, BLU, BLU, BLU, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, BLU, BLU, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, BLU, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {WHT, WHT, WHT, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF}};

static const uint8_t init_sequence_shift_lights[INIT_STEPS][16] = {
    {GRN, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, GRN},
    {GRN, GRN, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, GRN, GRN},
    {GRN, GRN, GRN, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, GRN, GRN, GRN},
    {GRN, GRN, GRN, GRN, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, GRN, GRN, GRN, GRN},
    {GRN, GRN, GRN, GRN, YLW, OFF, OFF, OFF, OFF, OFF, OFF, YLW, GRN, GRN, GRN, GRN},
    {GRN, GRN, GRN, GRN, YLW, YLW, OFF, OFF, OFF, OFF, YLW, YLW, GRN, GRN, GRN, GRN},
    {GRN, GRN, GRN, GRN, YLW, YLW, RED, OFF, OFF, RED, YLW, YLW, GRN, GRN, GRN, GRN},
    {GRN, GRN, GRN, GRN, YLW, YLW, RED, RED, RED, RED, YLW, YLW, GRN, GRN, GRN, GRN},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU},
    {GRN, GRN, GRN, GRN, YLW, YLW, RED, RED, RED, RED, YLW, YLW, GRN, GRN, GRN, GRN},
    {GRN, GRN, GRN, GRN, YLW, YLW, RED, OFF, OFF, RED, YLW, YLW, GRN, GRN, GRN, GRN},
    {GRN, GRN, GRN, GRN, YLW, YLW, OFF, OFF, OFF, OFF, YLW, YLW, GRN, GRN, GRN, GRN},
    {GRN, GRN, GRN, GRN, YLW, OFF, OFF, OFF, OFF, OFF, OFF, YLW, GRN, GRN, GRN, GRN},
    {GRN, GRN, GRN, GRN, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, GRN, GRN, GRN, GRN},
    {GRN, GRN, GRN, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, GRN, GRN, GRN},
    {GRN, GRN, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, GRN, GRN},
    {GRN, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, GRN},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF}};

static const uint8_t init_sequence_status_bars[INIT_STEPS][16] = {
    {RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED, OFF},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW, RED},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN, YLW},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN, GRN},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU, CYN},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP, BLU},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP},
    {OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, OFF, PRP}};

#endif // COLORS_H
