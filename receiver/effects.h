#pragma once

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <IRremote.hpp>

// Rb = 1.5k
// Rled = 47

#define NEOPIXEL_PIN D7
#define NUMPIXELS 17
#define DELAYVAL 100
const uint16_t IR_RECEIVE_PIN = D10;
int num_base_colors = 67;
int num_tail_codes = 14;
int num_special_effects = 45;

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

uint32_t RED = pixels.Color(75, 0, 0);
uint32_t REDORANGE = pixels.Color(75, 8, 0);
uint32_t ORANGE = pixels.Color(75, 30, 0);
uint32_t YELLOWORANGE = pixels.Color(75, 50, 0);
uint32_t YELLOW = pixels.Color(75, 75, 0);
uint32_t YELLOWGREEN = pixels.Color(45, 75, 0);
uint32_t GREEN = pixels.Color(0, 52, 0);
uint32_t LIGHT_GREEN = pixels.Color(30, 67, 3);
uint32_t TURQUOISE = pixels.Color(0, 75, 60);
uint32_t LIGHT_BLUE = pixels.Color(2, 45, 60);
uint32_t BLUE = pixels.Color(0, 0, 67);
uint32_t BLURPLE = pixels.Color(45, 0, 75);
uint32_t PURPLE = pixels.Color(75, 0, 60);
uint32_t MAGENTA = pixels.Color(75, 12, 22);
uint32_t PINK = pixels.Color(75, 6, 6);
uint32_t ROSE = pixels.Color(45, 6, 6);
uint32_t DIM_RED = pixels.Color(36, 0, 0);
uint32_t DIM_ORANGE = pixels.Color(37, 5, 0);
uint32_t DIM_BLUE = pixels.Color(0, 0, 30);
uint32_t DIM_GREEN = pixels.Color(0, 30, 0);
uint32_t DIM_PURPLE = pixels.Color(37, 12, 30);
uint32_t DIM_TURQUOISE = pixels.Color(0, 37, 30);
uint32_t DIM_PINK = pixels.Color(37, 12, 22);
uint32_t WARM_WHITE = pixels.Color(60, 45, 22);
uint32_t COOL_WHITE = pixels.Color(45, 45, 45);

struct ColorEffect {
  uint64_t cmd;
  uint32_t color;
  String name;
};

struct TailEffect {
  uint64_t cmd;
  uint32_t duration_micros;
  bool fade;
  String name;
};

struct SpecialEffect {
  uint64_t cmd;
  uint32_t color;
  uint32_t duration_micros;
  bool fade;
};

ColorEffect base_colors[] = {
  // base colors used at the eras tour
  (ColorEffect) {365628796241, WARM_WHITE, "WARM_WHITE"},
  (ColorEffect) {370997269849, COOL_WHITE, "COOL_WHITE"},
  (ColorEffect) {353816456289, RED, "RED"},
  (ColorEffect) {358110833761, REDORANGE, "REDORANGE"},
  (ColorEffect) {350594902369, ORANGE, "ORANGE"},
  (ColorEffect) {350594116961, YELLOWORANGE, "YELLOWORANGE"},
  (ColorEffect) {346300984673, YELLOW, "YELLOW"},
  (ColorEffect) {350595950945, YELLOWGREEN, "YELLOWGREEN"},
  (ColorEffect) {358112339297, GREEN, "GREEN"},
  (ColorEffect) {346301421641, LIGHT_GREEN, "LIGHTGREEN"},
  (ColorEffect) {346301420625, LIGHT_GREEN, "CYAN1"},
  (ColorEffect) {346301417561, TURQUOISE, "CYAN2"},
  (ColorEffect) {350594114921, LIGHT_BLUE, "CYAN3"},
  (ColorEffect) {350596208985, BLUE, "BLUE"},
  (ColorEffect) {350595156313, BLURPLE, "BLURPLE"},
  (ColorEffect) {350596213097, PURPLE, "PURPLE1"},
  (ColorEffect) {358112401481, PURPLE, "PURPLE2"},
  (ColorEffect) {346300198217, PINK, "PINK"},
  (ColorEffect) {358112404553, MAGENTA, "MAGENTA"},
  (ColorEffect) {346299405649, ROSE, "ROSE1"},
  (ColorEffect) {370995145801, DIM_ORANGE, "DIM_ORANGE"},
  (ColorEffect) {365626764361, DIM_RED, "DIM_RED"},
  (ColorEffect) {350594115929, DIM_BLUE, "DIM_BLUE"},
  (ColorEffect) {346301424713, DIM_GREEN, "DIM_GREEN"},
  (ColorEffect) {358112340313, DIM_TURQUOISE, "DIM_TURQUOISE"},
  (ColorEffect) {350596213081, DIM_PURPLE, "DIM_PURPLE"},
  (ColorEffect) {346299067481, DIM_PINK, "DIM_PINK"},
  // other colors from pixmob-ir-reverse-engineering
  // which the bracelet responded to
  (ColorEffect) {434347087969, REDORANGE, "RED"},
  (ColorEffect) {434346039393, RED, "RED_4"},
  (ColorEffect) {350596212065, DIM_RED, "DIM_RED"},
  (ColorEffect) {435421485153, GREEN, "GREEN"},
  (ColorEffect) {370996972641, GREEN, "GREEN"},
  (ColorEffect) {370996974689, GREEN, "GREEN"},
  (ColorEffect) {370996978785, YELLOWGREEN, "GREEN"},
  (ColorEffect) {370997500001, YELLOWGREEN, "GREEN"},
  (ColorEffect) {370996840545, DIM_GREEN, "GREEN_DIM"},
  (ColorEffect) {370996978761, LIGHT_GREEN, "LIGHT_GREEN"},
  (ColorEffect) {370996978769, LIGHT_GREEN, "LIGHT_GREEN_2"},
  (ColorEffect) {370995926113, YELLOWGREEN, "YELLOWGREEN"},
  (ColorEffect) {370997504097, YELLOWGREEN, "YELLOWGREEN_2"},
  (ColorEffect) {434348136545, YELLOWGREEN, "YELLOWGREEN_3"},
  (ColorEffect) {350596212049, BLUE, "BLUE"},
  (ColorEffect) {350596212049, BLUE, "BLUE_2"},
  (ColorEffect) {350596191633, LIGHT_BLUE, "LIGHT_BLUE"},
  (ColorEffect) {370996975705, LIGHT_BLUE, "LIGHT_BLUE_2"},
  (ColorEffect) {370996975721, LIGHT_BLUE, "LIGHT_BLUE_3"},
  (ColorEffect) {350596212041, DIM_BLUE, "DIM_BLUE"},
  (ColorEffect) {435420436577, YELLOW, "YELLOW"},
  (ColorEffect) {370996186209, YELLOW, "YELLOW_3"},
  (ColorEffect) {350596195745, YELLOW, "YELLOW_6"},
  (ColorEffect) {434347083873, YELLOWORANGE, "YELLOW_9"},
  (ColorEffect) {370996194385, PINK, "PINK"},
  (ColorEffect) {350595081297, PINK, "PINK_2"},
  (ColorEffect) {370995930209, ORANGE, "ORANGE"},
  (ColorEffect) {370995402849, ORANGE, "ORANGE_2"},
  (ColorEffect) {370995405921, REDORANGE, "REDORANGE"},
  (ColorEffect) {370996194401, REDORANGE, "REDORANGE_2"},
  (ColorEffect) {370997242977, YELLOWORANGE, "YELLOWORANGE"},
  (ColorEffect) {350596129889, YELLOWORANGE, "YELLOWORANGE"},
  (ColorEffect) {350596129865, WARM_WHITE, "WHITISH"},
  (ColorEffect) {350596129873, WARM_WHITE, "WHITISH"},
  (ColorEffect) {435420436561, WARM_WHITE, "WHITISH"},
  (ColorEffect) {350596129873, WARM_WHITE, "WHITISH"},
  (ColorEffect) {350596195729, WARM_WHITE, "WHITISH"},
  (ColorEffect) {370997499985, TURQUOISE, "TURQUOISE"},
  (ColorEffect) {370996974673, TURQUOISE, "TURQUOISE"},
  (ColorEffect) {370996975689, TURQUOISE, "TURQUOISE"},
};

TailEffect tail_codes[] = {
  (TailEffect) {1476705, 1200, true,  "FADE_1"},
  (TailEffect) {2533473, 900, true,  "FADE_2"},
  (TailEffect) {1484897, 1500, true,  "FADE_3"},
  (TailEffect) { 821857, 1300, true,  "FADE_4"},
  (TailEffect) {1480801, 1300, true,  "FADE_5"},
  (TailEffect) {2529377, 500, true,  "FADE_6"},
  (TailEffect) { 266337, 300, false, "SHARP_PROBABILISTIC_1"},
  (TailEffect) { 268385, 300, false, "SHARP_PROBABILISTIC_2"},
  (TailEffect) { 272481, 300, false, "SHARP_PROBABILISTIC_3"},
  (TailEffect) { 280673, 300, false, "SHARP_PROBABILISTIC_4"},
  (TailEffect) {1215585, 1000, true,  "FADE_PROBABILISTIC_1"},
  (TailEffect) {1223777, 1000, true,  "FADE_PROBABILISTIC_2"},
  (TailEffect) {2264161, 1000, true,  "FADE_PROBABILISTIC_3"},
  (TailEffect) {1346145, 1000, true,  "FADE_PROBABILISTIC_4"},
};

SpecialEffect special_effects[] = {
  (SpecialEffect) {1879741965961, RED, 200, false}, // last signal sent at the eras tour (41 bits)
  // other special effects from pixmob-ir-reverse-engineering
  // which the bracelet responded to
  // all special effects below are 63 bits long
  (SpecialEffect) {5287547451109086305, WARM_WHITE, 200, false},
  (SpecialEffect) {5882022601598605409, WARM_WHITE, 200, true},
  (SpecialEffect) {5882022601867040865, YELLOW, 200, true},
  (SpecialEffect) {5882005009680996449, ORANGE, 200, true},
  (SpecialEffect) {5882022532879128673, TURQUOISE, 200, true},
  (SpecialEffect) {5882022533147564129, GREEN, 200, true},
  (SpecialEffect) {5882004940961519713, YELLOW, 200, true},
  (SpecialEffect) {5882004957872953441, WARM_WHITE, 200, true},
  (SpecialEffect) {5287547451109092449, WARM_WHITE, 1000, true},
  (SpecialEffect) {5882009407458809953, PINK, 1000, true}, // purple fade
  (SpecialEffect) {5882010443619932257, LIGHT_BLUE, 200, false},
  (SpecialEffect) {5882009441818810465, PINK, 200, false},
  (SpecialEffect) {5882009338739595361, LIGHT_BLUE, 200, false}, // whitish blue
  (SpecialEffect) {5881991849632766049, PINK, 200, true}, // magenta
  (SpecialEffect) {5287534256969559137, PINK, 1200, true},
  (SpecialEffect) {5287534256701123681, PINK, 1200, true},
  (SpecialEffect) {5287534187981646945, WARM_WHITE, 1200, true},
  (SpecialEffect) {5287551780167691361, LIGHT_GREEN, 1200, true},
  (SpecialEffect) {5287551780166642785, LIGHT_GREEN, 1200, true},
  (SpecialEffect) {5287551780103211681, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103213729, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103276961, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103279009, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103283105, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103295329, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103425377, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103425377, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103427425, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103476385, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103474337, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103480481, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103480481, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103735969, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103740065, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103752289, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103801249, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287551780103805345, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5215497226768127329, WARM_WHITE, 1000, true},
  (SpecialEffect) {5215497226902345057, WARM_WHITE, 1000, true},
  (SpecialEffect) {5215499408879949153, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287556126610330977, GREEN, 1000, true},
  (SpecialEffect) {5263764195354908065, WARM_WHITE, 300, false},
  (SpecialEffect) {5263764195354912161, WARM_WHITE, 600, true},
  (SpecialEffect) {5287547451109084257, WARM_WHITE, 700, false},
};
