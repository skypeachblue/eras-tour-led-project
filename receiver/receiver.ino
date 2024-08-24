#include <Arduino.h>
#include <IRremote.hpp>
#include "effects.h"

void rainbow(uint16_t first_hue, int8_t reps,
  uint8_t saturation, uint8_t brightness, bool gammify) {
  for (uint16_t i=0; i<NUMPIXELS; i++) {
    uint16_t hue = first_hue + (i * reps * 65536) / NUMPIXELS;
    uint32_t color = pixels.ColorHSV(hue, saturation, brightness);
    if (gammify) color = pixels.gamma32(color);
    pixels.setPixelColor(i, color);
    delay(50);
    pixels.show();
  }
  delay(100);
  pixels.clear();
  pixels.show();
}

void set_color(uint32_t color) {
  for (int i=0; i<NUMPIXELS; i++) {
    if (i % 2 == 0) {
      pixels.setPixelColor(i, color);
    }
  }
  pixels.show();
}

void fade_in(uint32_t color) {
  uint32_t r = (color >> 16) & 0xff;
  uint32_t g = (color >> 8) & 0xff;
  uint32_t b = (color) & 0xff;
  set_color(pixels.Color(r/8,g/8,b/8));
  delay(100);
  set_color(pixels.Color(r/4,g/4,b/4));
  delay(100);
  set_color(pixels.Color(r/2, g/2, b/2));
  delay(100);
  set_color(pixels.Color(r, g, b));
}

void fade_out(uint32_t color) {
  uint32_t r = (color >> 16) & 0xff;
  uint32_t g = (color >> 8) & 0xff;
  uint32_t b = (color) & 0xff;
  set_color(pixels.Color(r, g, b));
  pixels.show();
  delay(100);
  set_color(pixels.Color(r/2, g/2, b/2));
  pixels.show();
  delay(100);
  set_color(pixels.Color(r/4,g/4,b/4));
  pixels.show();
  delay(100);
  set_color(pixels.Color(r/8,g/8,b/8));
  pixels.show();
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_RECEIVE_PIN, INPUT_PULLUP);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pixels.begin();
  pixels.clear();

  // start up effect
  /*
  for (int p=0; p<NUMPIXELS; p++) {
    pixels.setPixelColor(p, WHITE);
    delay(50);
    pixels.show();
  }

  delay(100);
  pixels.clear();
  pixels.show();
  */
  rainbow(0, 1, 255, 50, true);
}

void loop() {
  //IrReceiver.restartAfterSend();

  // wait until we receive a signal
  while (!IrReceiver.decode());
  Serial.println("received");
  IrReceiver.printIRResultRawFormatted(&Serial, true);

  // check for buffer overflow
  if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
    Serial.println("Try to increase the \"RAW_BUFFER_LENGTH\"");
    for (int p=0; p<NUMPIXELS; p++) {
      pixels.setPixelColor(p, RED);
      delay(100);
      pixels.show();
    }
    delay(100);
    pixels.clear();
    pixels.show();
    IrReceiver.resume();
    // see also https://github.com/Arduino-IRremote/Arduino-IRremote#compile-options--macros-for-this-library
  } else {
    // convert the run legths of the signal into an uint64_t
    String s = "";
    bool one_or_zero = 1;
    uint64_t cmd = 0;
    int bit_len = 0;
    for (IRRawlenType i=1; i<IrReceiver.decodedIRData.rawlen; i++) {
      uint64_t num = int(round(IrReceiver.decodedIRData.rawDataPtr->rawbuf[i] / 14.0f));
      bit_len += num;
      s += String(num);
      cmd <<= num;
      if (one_or_zero == 1) {
        for (int j=0; j<num; j++) {
          cmd |= (((uint64_t) 1) << j);
        }
      }
      one_or_zero = !one_or_zero;
    }
    Serial.println(s);
    Serial.printf("\nbit len: %d\n", bit_len);
    IrReceiver.resume();
    bool performed_command = false;

    // check if we received a known command
    if (bit_len == 39) { // command is a base color
      // iterate through base colors
      for (int i=0; i<num_base_colors; i++) {
        if (base_colors[i].cmd == cmd) {
          Serial.printf("BASE COLOR %d\n", i);
          pixels.clear();
          set_color(base_colors[i].color);
          delay(200); // base colors always have this duration
          performed_command = true;
          break;
        }
      }
    } else if (bit_len == 63) { // command is special effect or base + tail
      // iterate through special effects
      if (!performed_command) {
        for (int i=0; i<num_special_effects; i++) {
          if (special_effects[i].cmd == cmd) {
            Serial.printf("SPECIAL %d\n", i);
            pixels.clear();
            if (special_effects[i].fade) {
              fade_in(special_effects[i].color);
              set_color(special_effects[i].color);
              delay(special_effects[i].duration_micros);
              fade_out(special_effects[i].color);
            } else {
              set_color(special_effects[i].color);
              delay(special_effects[i].duration_micros);
            }
            performed_command = true;
            break;
          }
        }
      }

      // iterate through tail codes
      if (!performed_command) {
        uint64_t base_cmd = (cmd >> 24) & 0x7fffffffff;
        uint64_t tail_cmd = cmd & 0xffffff;
        printf("\n%llx %llx %llx \n", cmd, base_cmd, tail_cmd);
        printf("%llu %llu\n", base_cmd, tail_cmd);
        for (int i=0; i<num_tail_codes; i++) {
          if (tail_codes[i].cmd == tail_cmd) {
            Serial.printf("TAIL %d\n", i);
            for (int j=0; j<num_base_colors; j++) {
              if (base_colors[j].cmd == base_cmd) {
                if (tail_codes[i].fade) {
                  fade_in(base_colors[j].color);
                  set_color(base_colors[j].color);
                  delay(tail_codes[i].duration_micros);
                  fade_out(base_colors[j].color);
                } else {
                  set_color(base_colors[j].color);
                  delay(tail_codes[i].duration_micros);
                }
                performed_command = true;
                break;
              }
            }
          }
        }
      }
    }

    if (!performed_command) {
      Serial.println("UNKNOWN COMMAND");
    }
  }
  pixels.clear();
  pixels.show();
}
