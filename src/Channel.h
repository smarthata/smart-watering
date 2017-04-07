#ifndef SMART_WATERING_CHANNEL_H
#define SMART_WATERING_CHANNEL_H

class Channel {
public:
    Channel(const byte pin, const unsigned int enabledMinutes) : pin(pin), enabledMinutes(enabledMinutes) {
        pinMode(pin, OUTPUT);
    }

    void enable() {
        digitalWrite(pin, HIGH);
        enabled = true;
    }

    void disable() {
        digitalWrite(pin, LOW);
        enabled = false;
    }

    bool isEnabled() const {
        return enabled;
    }

    const unsigned int getEnabledMinutes() const {
        return enabledMinutes;
    }

private:
    const byte pin;
    const unsigned int enabledMinutes;
    bool enabled = false;
};

#endif
