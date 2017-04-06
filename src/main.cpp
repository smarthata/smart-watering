#include <Arduino.h>
#include "SmartWatering.h"

#define RELAY_PIN 13
#define ENABLED_MINUTES 1

byte arr[] = {22, 29, 00};
SmartWatering smartWatering(RELAY_PIN, ENABLED_MINUTES, arr);

void setup() {
    Serial.begin(9600);
    smartWatering.setup();
}

void loop() {
    smartWatering.loop();
}
