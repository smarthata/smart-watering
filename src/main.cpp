#include <Arduino.h>
#include "SmartWatering.h"

#define RELAY_PIN 13

byte arr[] = {22, 5, 40};
SmartWatering smartWatering(RELAY_PIN, arr);

void setup() {
    Serial.begin(9600);
    smartWatering.setup();
}

void loop() {
    smartWatering.loop();
}
