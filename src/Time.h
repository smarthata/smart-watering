#ifndef SMART_WATERING_TIME_H
#define SMART_WATERING_TIME_H

class Time {
public:
    Time() {}

    Time(byte hour, byte minute, byte second) : hour(hour), minute(minute), second(second) {}

    Time(byte time[3]) : hour(time[0]), minute(time[1]), second(time[2]) {}

    bool equals(byte hour, byte minute, byte second) const {
        return (hour == this->hour) & (minute == this->minute) & (second == this->second);
    }

    unsigned long getDaySeconds() const {
        return (unsigned long) ((hour * 60L + minute) * 60 + second);
    }

    void setDaySeconds(unsigned long daySeconds) {
        second = (byte) (daySeconds % 60);
        daySeconds /= 60;
        minute = (byte) (daySeconds % 60);
        daySeconds /= 60;
        hour = (byte) (daySeconds % 24);
    }

    void addDaySeconds(unsigned long daySeconds) {
        setDaySeconds(getDaySeconds() + daySeconds);
    }

    byte hour, minute, second;
};

#endif
