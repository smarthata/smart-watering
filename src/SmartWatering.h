#ifndef SMART_WATERING_SMARTWATERING_H
#define SMART_WATERING_SMARTWATERING_H

#include "Timing.h"
#include "Clock.h"
#include "ChannelHolder.h"

class SmartWatering {
public:
    SmartWatering(byte time[3], byte maxChannelCount) {
        this->startTime = new Time(time);
        this->finishTime = new Time(time);
        this->channelHolder = new ChannelHolder(maxChannelCount);
    }

    void setup() const {
        clock.setup();
    }

    void loop() {

        if (interval.isReady()) {
            if (clock.equals(startTime)) {
                channelHolder->startEnable();
                finishTime->setDaySeconds(startTime->getDaySeconds());
                calculateFinishTime();
            }

            if (clock.equals(finishTime)) {
                if (channelHolder->nextEnable()) {
                    calculateFinishTime();
                }
            }
        }

        if (clockInterval.isReady()) {
            Serial.print(clock.getHour());
            Serial.print(':');
            Serial.print(clock.getMinute());
            Serial.print(':');
            Serial.println(clock.getSecond());
        }
    }

    void addChannel(byte relayPin, byte enabledMinutes) {
        channelHolder->addChannel(new Channel(relayPin, enabledMinutes));
    }

private:
    Clock clock;

    Interval interval = Interval(1000);
    Interval clockInterval = Interval(5000);

    Time *startTime;
    Time *finishTime;

    ChannelHolder *channelHolder;

    void calculateFinishTime() const {
        finishTime->addDaySeconds(channelHolder->current()->getEnabledMinutes() * 60);

        Serial.print("Time to disable: ");
        Serial.print(finishTime->hour);
        Serial.print(':');
        Serial.print(finishTime->minute);
        Serial.print(':');
        Serial.println(finishTime->second);
    }
};

#endif
