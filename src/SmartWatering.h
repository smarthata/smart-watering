#ifndef SMART_WATERING_SMARTWATERING_H
#define SMART_WATERING_SMARTWATERING_H

#include <DS3231.h>
#include <Relay.h>
#include <Timing.h>
#include "Time.h"

class SmartWatering {
public:
    SmartWatering(byte relayPin, byte enabledMinutes, byte time[3]) {
        this->relay = new Relay(relayPin);
        this->time = new Time(time);
        this->enabledMs = enabledMinutes * 60 * 1000;
    }

    void setup() {
        Wire.begin();
    }

    void loop() {

        if (interval.isReady()) {

            if (time->equals(clock.getHour(h12, PM), clock.getMinute(), clock.getSecond())) {
                relay->enable();
                enabledTimeout.start(enabledMs);
            }

            if (relay->isEnabled() & enabledTimeout.isReady()) {
                relay->disable();
            }

            Serial.print(clock.getHour(h12, PM));
            Serial.print(':');
            Serial.print(clock.getMinute());
            Serial.print(':');
            Serial.println(clock.getSecond());
        }
    }

private:
    DS3231 clock;
    bool h12 = false;
    bool PM = false;

    Interval interval = Interval(1000);

    Timeout enabledTimeout;
    unsigned int enabledMs;

    Time *time;

    Relay *relay;
};

#endif
