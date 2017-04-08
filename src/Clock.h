#ifndef SMART_WATERING_CLOCK_H
#define SMART_WATERING_CLOCK_H

#include <DS3231.h>
#include "Time.h"

class Clock : public DS3231 {
public:
    void setup() const {
        Wire.begin();
    }

    byte getMonth() {
        return DS3231::getMonth(century);
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

    void displayFullDate() {
        displayDate();
        Serial.print(" ");
        displayTime();
    }

    void displayDate() {
        Serial.print("Now 20");
        Serial.print(getYear());
        Serial.print("-");
        displayLeadingZero(getMonth());
        Serial.print("-");
        displayLeadingZero(getDate());

        Serial.print(" ");
        Serial.print(getDoWString());
    }

    const char *getDoWString() {
        switch (getDoW()) {
            case 1:
                return "Mon";
            case 2:
                return "Tue";
            case 3:
                return "Wed";
            case 4:
                return "Thu";
            case 5:
                return "Fri";
            case 6:
                return "Sut";
            case 7:
                return "Sun";
            default:
                return "None";
        }
    }

    void displayTime() {
        displayLeadingZero(getHour());
        Serial.print(":");
        displayLeadingZero(getMinute());
        Serial.print(":");
        displayLeadingZero(getSecond());
        Serial.println();
    }

    void displayLeadingZero(const byte number) const {
        if (number < 10) {
            Serial.print("0");
        }
        Serial.print(number);
    }

private:
    bool century = false;
    bool h12 = false;
    bool PM = false;

    Time time;
};

#endif
