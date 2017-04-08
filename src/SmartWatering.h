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

    void setup() {
        clock.setup();
        clock.displayFullDate();
    }

    void setDate(unsigned int year, byte month, byte dayOfMonth, byte dayOfWeek) {
        clock.setYear(year - 2000);
        clock.setMonth(month);
        clock.setDate(dayOfMonth);
        clock.setDoW(dayOfWeek);
        clock.displayFullDate();
    }

    void setTime(byte hour, byte minute, byte second) {
        clock.setHour(hour);
        clock.setMinute(minute);
        clock.setSecond(second);
        clock.displayFullDate();
    }

    void loop() {

        if (interval.isReady()) {
            Time now = clock.readTime();
            if (inProgress) {
                checkFinish(now);
            }
            if (!inProgress) {
                checkStart(now);
            }
        }

        if (clockInterval.isReady()) {
            clock.readTime().display();
        }
    }

    void checkStart(const Time &now) {
        for (byte i = 0; i < timesCount; ++i) {
            if (now.equals(times[i])) {
                channelHolder->start();
                finishTime->setDaySeconds(times[i]->getDaySeconds());
                calculateFinishTime();
                inProgress = true;
                break;
            }
        }
    }

    void checkFinish(const Time &now) {
        if (now.equals(finishTime)) {
            if (channelHolder->enableNext()) {
                calculateFinishTime();
            } else {
                inProgress = false;
            }
        }
    }

    void addChannel(Channel *channel) {
        Serial.print("Add channel on pin [");
        Serial.print(channel->getPin());
        Serial.print("] and [");
        Serial.print(channel->getEnabledMinutes());
        Serial.println("] minutes");
        channelHolder->addChannel(channel);
    }

    void addTime(Time *time) {
        Serial.print("Add alarm [");
        Serial.print(timesCount);
        Serial.print("] on ");
        time->display();
        this->times[timesCount] = time;
        timesCount++;
    }

private:
    Clock clock;

    Interval interval = Interval(1000);
    Interval clockInterval = Interval(5000);

    byte timesCount = 0;
    Time **times;
    Time *finishTime;

    bool inProgress = false;

    ChannelHolder *channelHolder;

    void calculateFinishTime() const {
        finishTime->addDaySeconds(channelHolder->current()->getEnabledMinutes() * 60);

        Serial.print("Time to disable: ");
        finishTime->display();
    }
};

#endif
