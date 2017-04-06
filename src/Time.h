#ifndef SMART_WATERING_TIME_H
#define SMART_WATERING_TIME_H

class Time {
public:
    Time(byte hour, byte minute, byte second) : hour(hour), minute(minute), second(second) {}

    bool equals(byte hour, byte minute, byte second) {
        return hour == this->hour & minute == this->minute & second == this->second;
    }

private:
    byte hour, minute, second;
};

#endif
