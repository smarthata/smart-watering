#include <Arduino.h>
#include "SmartWatering.h"

SmartWatering smartWatering;

void setup() {
    Serial.begin(9600);
    smartWatering.setup();
}

void loop() {
    smartWatering.loop();
}
