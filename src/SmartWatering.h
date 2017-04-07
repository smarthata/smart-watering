#ifndef SMART_WATERING_SMARTWATERING_H
#define SMART_WATERING_SMARTWATERING_H

#include <DS3231.h>
#include "ChannelHolder.h"

class SmartWatering {
public:
    SmartWatering(byte time[3], byte maxChannelCount) {
        this->startTime = new Time(time);
        this->finishTime = new Time(time);
        this->channelHolder = new ChannelHolder(maxChannelCount);
    }

    void setup() {
        Wire.begin();
    }

    void loop() {

        if (interval.isReady()) {
            if (startTime->equals(clock.getHour(h12, PM), clock.getMinute(), clock.getSecond())) {
                channelHolder->startEnable();
                calculateFinishTime();
            }

            if (finishTime->equals(clock.getHour(h12, PM), clock.getMinute(), clock.getSecond())) {
                if (channelHolder->nextEnable()) {
                    calculateFinishTime();
                }
            }
        }

        if (clockInterval.isReady()) {
            Serial.print(clock.getHour(h12, PM));
            Serial.print(':');
            Serial.print(clock.getMinute());
            Serial.print(':');
            Serial.println(clock.getSecond());
        }
    }

    void addChannel(byte relayPin, byte enabledMinutes) {
        channelHolder->addChannel(new Channel(new Relay(relayPin), enabledMinutes));
    }

private:
    DS3231 clock;
    bool h12 = false;
    bool PM = false;

    Interval interval = Interval(1000);
    Interval clockInterval = Interval(5000);

    Time *startTime;
    Time *finishTime;

    ChannelHolder *channelHolder;

    void calculateFinishTime() const {
        unsigned int enabledMinutes = channelHolder->current()->enabledMinutes;
        Serial.print("Enabling for ");
        Serial.print(enabledMinutes);
        Serial.println(" minutes");

        finishTime->setDaySeconds(finishTime->getDaySeconds() + enabledMinutes * 60);

        Serial.print("Time to disable: ");
        Serial.print(finishTime->hour);
        Serial.print(':');
        Serial.print(finishTime->minute);
        Serial.print(':');
        Serial.println(finishTime->second);
    }
};

#endif
