#ifndef SMART_WATERING_CHANNEL_H
#define SMART_WATERING_CHANNEL_H

#include <Relay.h>
#include <Timing.h>
#include "Time.h"

class Channel {
public:
    Channel(Relay *relay, byte enabledMinutes) : relay(relay), enabledMinutes(enabledMinutes) {}

    Relay *relay;

    unsigned int enabledMinutes;
};

#endif
