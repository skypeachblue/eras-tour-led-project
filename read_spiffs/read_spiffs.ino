#include <Arduino.h>
#include "spiffs.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(3000);

  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
      Serial.println("SPIFFS Mount Failed");
  } else {
    Serial.println("\nMOUNTED");
  }

  list_dir(SPIFFS, "/");
  print_all_files(SPIFFS, "/");
}

void loop() {
  return;
}
