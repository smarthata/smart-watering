#ifndef SMART_WATERING_CLOCK_H
#define SMART_WATERING_CLOCK_H

#include <DS3231.h>
#include "Time.h"

class Clock : public DS3231 {
public:
    void setup() const {
        Wire.begin();
    }

    byte getHour() {
        return DS3231::getHour(h12, PM);
    }

    Time &readTime() {
        time.hour = getHour();
        time.minute = getMinute();
        time.second = getSecond();
        return time;
    }

private:
    bool h12 = false;
    bool PM = false;

    Time time;
};

#endif
