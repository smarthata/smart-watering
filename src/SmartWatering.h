#ifndef SMART_WATERING_SMARTWATERING_H
#define SMART_WATERING_SMARTWATERING_H

#include <DS3231.h>
#include <Relay.h>
#include <Timing.h>
#include "Time.h"

class SmartWatering {
public:
    SmartWatering(byte relayPin, byte enabledMinutes, byte time[3]) : enabledMinutes(enabledMinutes) {
        this->relay = new Relay(relayPin);
        this->startTime = new Time(time);
        this->finishTime = new Time();
    }

    void setup() {
        Wire.begin();
    }

    void loop() {

        if (interval.isReady()) {

            if (startTime->equals(clock.getHour(h12, PM), clock.getMinute(), clock.getSecond())) {
                relay->enable();
                calculateFinishTime();
            }

            if (finishTime->equals(clock.getHour(h12, PM), clock.getMinute(), clock.getSecond())) {
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

    unsigned int enabledMinutes;

    Time *startTime;
    Time *finishTime;

    Relay *relay;

    void calculateFinishTime() const {
        finishTime->setDaySeconds(startTime->getDaySeconds() + enabledMinutes * 60);
    }
};

#endif
