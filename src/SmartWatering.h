#ifndef SMART_WATERING_SMARTWATERING_H
#define SMART_WATERING_SMARTWATERING_H

#include <DS3231.h>
#include "Channel.h"

class SmartWatering {
public:
    SmartWatering(byte time[3]) {
        this->startTime = new Time(time);
        this->finishTime = new Time();
    }

    void setup() {
        Wire.begin();
    }

    void loop() {

        if (interval.isReady()) {

            if (startTime->equals(clock.getHour(h12, PM), clock.getMinute(), clock.getSecond())) {
                channel->relay->enable();
                calculateFinishTime();
                Serial.print("Enable channel");
            }

            if (finishTime->equals(clock.getHour(h12, PM), clock.getMinute(), clock.getSecond())) {
                channel->relay->disable();
                Serial.print("Disable channel");
            }

            Serial.print(clock.getHour(h12, PM));
            Serial.print(':');
            Serial.print(clock.getMinute());
            Serial.print(':');
            Serial.println(clock.getSecond());
        }
    }

    void setChannel(byte relayPin, byte enabledMinutes) {
        this->channel = new Channel(new Relay(relayPin), enabledMinutes);
    }

private:
    DS3231 clock;
    bool h12 = false;
    bool PM = false;

    Interval interval = Interval(1000);

    Time *startTime;
    Time *finishTime;

    Channel *channel;

    void calculateFinishTime() const {
        finishTime->setDaySeconds(startTime->getDaySeconds() + channel->enabledMinutes * 60);
    }
};

#endif
