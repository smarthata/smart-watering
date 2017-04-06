#include <Arduino.h>
#include "SmartWatering.h"

#define RELAY_PIN 13

SmartWatering smartWatering(RELAY_PIN);

void setup() {
    Serial.begin(9600);
    smartWatering.setup();
}

void loop() {
    smartWatering.loop();
}
