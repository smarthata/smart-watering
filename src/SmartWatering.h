#ifndef SMART_WATERING_SMARTWATERING_H
#define SMART_WATERING_SMARTWATERING_H

#include "Timing.h"
#include "Clock.h"
#include "ChannelHolder.h"

class SmartWatering {
public:
    SmartWatering(const byte totalTimes, const byte totalChannels) {
        this->times = new Time *[totalTimes];
        this->finishTime = new Time();
        this->channelHolder = new ChannelHolder(totalChannels);
    }

    void setup() const {
        clock.setup();
    }

    void loop() {

        if (interval.isReady()) {
            Time now = clock.readTime();
            for (byte i = 0; i < timesCount; ++i) {
                if (now.equals(times[i])) {
                    channelHolder->start();
                    finishTime->setDaySeconds(times[i]->getDaySeconds());
                    calculateFinishTime();
                    break;
                }
            }

            if (now.equals(finishTime)) {
                if (channelHolder->enableNext()) {
                    calculateFinishTime();
                }
            }
        }

        if (clockInterval.isReady()) {
            clock.readTime().display();
        }
    }

    void addChannel(const byte relayPin, const unsigned int enabledMinutes) {
        channelHolder->addChannel(new Channel(relayPin, enabledMinutes));
    }

    void addTime(Time *time) {
        this->times[timesCount] = time;
        timesCount++;
    }

private:
    Clock clock;

    Interval interval = Interval(1000);
    Interval clockInterval = Interval(5000);

    byte timesCount;
    Time **times;
    Time *finishTime;

    ChannelHolder *channelHolder;

    void calculateFinishTime() const {
        finishTime->addDaySeconds(channelHolder->current()->getEnabledMinutes() * 60);

        Serial.print("Time to disable: ");
        finishTime->display();
    }
};

#endif
