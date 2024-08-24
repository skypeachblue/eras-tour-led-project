#pragma once

#include <Adafruit_NeoPixel.h>

// Rb = 1.5k
// Rled = 47

#define NEOPIXEL_PIN D7
#define NUMPIXELS 16
#define DELAYVAL 100
const uint16_t IR_RECEIVE_PIN = D10;
int num_base_colors = 40;
int num_tail_codes = 14;
int num_special_effects = 44;

Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

uint32_t RED = pixels.Color(50, 0, 0);
uint32_t DIM_RED = pixels.Color(25, 0, 0);
uint32_t PINK = pixels.Color(50, 15, 40);
uint32_t BLUE = pixels.Color(0, 0, 45);
uint32_t DIM_BLUE = pixels.Color(0, 0, 25);
uint32_t LIGHT_BLUE = pixels.Color(1, 30, 40);
uint32_t TURQUOISE = pixels.Color(0, 50, 40);
uint32_t GREEN = pixels.Color(0, 35, 0);
uint32_t DIM_GREEN = pixels.Color(0, 20, 0);
uint32_t LIGHT_GREEN = pixels.Color(20, 45, 2);
uint32_t YELLOWGREEN = pixels.Color(20, 50, 0);
uint32_t YELLOW = pixels.Color(50, 50, 0);
uint32_t YELLOWORANGE = pixels.Color(50, 40, 0);
uint32_t ORANGE = pixels.Color(50, 20, 0);
uint32_t REDORANGE = pixels.Color(50, 5, 0);
uint32_t WHITE = pixels.Color(40, 40, 25);

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
  (ColorEffect) {350596129865, WHITE, "WHITISH"},
  (ColorEffect) {350596129873, WHITE, "WHITISH"},
  (ColorEffect) {435420436561, WHITE, "WHITISH"},
  (ColorEffect) {350596129873, WHITE, "WHITISH"},
  (ColorEffect) {350596195729, WHITE, "WHITISH"},
  (ColorEffect) {370997499985, TURQUOISE, "TURQUOISE"},
  (ColorEffect) {370996974673, TURQUOISE, "TURQUOISE"},
  (ColorEffect) {370996975689, TURQUOISE, "TURQUOISE"},
};

TailEffect tail_codes[] = {
  (TailEffect) {1476705, 1200, true,  "FADE_1"},
  (TailEffect) {2533473, 800, true,  "FADE_2"},
  (TailEffect) {1484897, 1200, true,  "FADE_3"},
  (TailEffect) { 821857, 1200, true,  "FADE_4"},
  (TailEffect) {1480801, 1200, true,  "FADE_5"},
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
  (SpecialEffect) {5287547451109086305, WHITE, 200, false},
  (SpecialEffect) {5882022601598605409, WHITE, 200, true},
  (SpecialEffect) {5882022601867040865, YELLOW, 200, true},
  (SpecialEffect) {5882005009680996449, ORANGE, 200, true},
  (SpecialEffect) {5882022532879128673, TURQUOISE, 200, true},
  (SpecialEffect) {5882022533147564129, GREEN, 200, true},
  (SpecialEffect) {5882004940961519713, YELLOW, 200, true},
  (SpecialEffect) {5882004957872953441, WHITE, 200, true},
  (SpecialEffect) {5287547451109092449, WHITE, 1000, true},
  (SpecialEffect) {5882009407458809953, PINK, 1000, true}, // purple fade
  (SpecialEffect) {5882010443619932257, LIGHT_BLUE, 200, false},
  (SpecialEffect) {5882009441818810465, PINK, 200, false},
  (SpecialEffect) {5882009338739595361, LIGHT_BLUE, 200, false}, // whitish blue
  (SpecialEffect) {5881991849632766049, PINK, 200, true}, // magenta
  (SpecialEffect) {5287534256969559137, PINK, 1200, true},
  (SpecialEffect) {5287534256701123681, PINK, 1200, true},
  (SpecialEffect) {5287534187981646945, WHITE, 1200, true},
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
  (SpecialEffect) {5215497226768127329, WHITE, 1000, true},
  (SpecialEffect) {5215497226902345057, WHITE, 1000, true},
  (SpecialEffect) {5215499408879949153, LIGHT_GREEN, 1000, true},
  (SpecialEffect) {5287556126610330977, GREEN, 1000, true},
  (SpecialEffect) {5263764195354908065, WHITE, 300, false},
  (SpecialEffect) {5263764195354912161, WHITE, 600, true},
  (SpecialEffect) {5287547451109084257, WHITE, 700, false},
};
