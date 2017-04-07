#include <Arduino.h>
#include "SmartWatering.h"

byte relay_pins[] = {13, 12, 11};
byte minutes[] = {1, 2, 3};

SmartWatering smartWatering(new byte[3]{18, 43, 10}, sizeof(relay_pins));

void setup() {
    Serial.begin(9600);
    smartWatering.setup();
    for (int i = 0; i < sizeof(relay_pins); ++i) {
        smartWatering.addChannel(relay_pins[i], minutes[i]);
    }
}

void loop() {
    smartWatering.loop();
}
