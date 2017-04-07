#include <Arduino.h>
#include "SmartWatering.h"

#define RELAY_PIN 13
#define ENABLED_MINUTES 1

SmartWatering smartWatering(new byte[3]{17, 46, 0});

void setup() {
    Serial.begin(9600);
    smartWatering.setup();
    smartWatering.setChannel(RELAY_PIN, ENABLED_MINUTES);
}

void loop() {
    smartWatering.loop();
}
