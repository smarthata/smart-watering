#include <Arduino.h>
#include "SmartWatering.h"

byte relay_pins[] = {13, 12, 11, 10, 9};
byte relay_enabled[] = {HIGH, LOW, LOW, LOW, LOW};
byte minutes[] = {2, 3, 3, 1, 2};

byte alarms[] = {
        23, 59, 55,
        0, 0, 10,
        0, 1, 25,
};

SmartWatering *smartWatering;

void setup() {
    Serial.begin(9600);

    byte totalAlarms = sizeof(alarms) / 3;
    byte totalRelays = sizeof(relay_pins);

    smartWatering = new SmartWatering(totalAlarms, totalRelays);
    smartWatering->setup();
    smartWatering->setDate(2017, 4, 8, 6);
    smartWatering->setTime(23, 59, 50);

    for (byte i = 0; i < totalRelays; ++i) {
        smartWatering->addChannel(new Channel(relay_pins[i], minutes[i], relay_enabled[i]));
    }

    for (byte i = 0; i < totalAlarms; ++i) {
        smartWatering->addTime(new Time(alarms[i * 3], alarms[i * 3 + 1], alarms[i * 3 + 2]));
    }
}

void loop() {
    smartWatering->loop();
}
