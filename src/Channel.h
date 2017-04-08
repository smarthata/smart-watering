#ifndef SMART_WATERING_CHANNEL_H
#define SMART_WATERING_CHANNEL_H

class Channel {
public:
    Channel(const byte pin, const unsigned int enabledMinutes, const byte enabledVoltage) :
            pin(pin), enabledMinutes(enabledMinutes), enabledVoltage(enabledVoltage) {
        pinMode(pin, OUTPUT);
        disable();
    }

    void enable() {
        digitalWrite(pin, enabledVoltage);
        enabled = true;
    }

    void disable() {
        digitalWrite(pin, HIGH - enabledVoltage);
        enabled = false;
    }

    bool isEnabled() const {
        return enabled;
    }

    const byte getPin() const {
        return pin;
    }

    const unsigned int getEnabledMinutes() const {
        return enabledMinutes;
    }

private:
    const byte pin;
    const unsigned int enabledMinutes;
    const byte enabledVoltage;
    bool enabled = false;
};

#endif
