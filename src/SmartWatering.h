#ifndef SMART_WATERING_SMARTWATERING_H
#define SMART_WATERING_SMARTWATERING_H

#include <DS3231.h>
#include <Relay.h>
#include "Time.h"

class SmartWatering {
public:
    void setup() {
        Wire.begin();
    }

    void loop() {
        Serial.print(clock.getHour(h12, PM));
        Serial.print(':');
        Serial.print(clock.getMinute());
        Serial.print(':');
        Serial.println(clock.getSecond());

        Serial.println(time.equals(clock.getHour(h12, PM), clock.getMinute(), clock.getSecond()));

        relay.enable();
        delay(500);
        relay.disable();
        delay(500);
    }

private:
    DS3231 clock;
    bool h12 = false;
    bool PM = false;

    Time time = Time(21, 20, 30);

    Relay relay = Relay(13);
};

#endif
