#ifndef SMART_WATERING_CHANNELHOLDER_H
#define SMART_WATERING_CHANNELHOLDER_H

#include "Channel.h"

class ChannelHolder {
public:
    ChannelHolder(byte maxChannelCount) {
        this->channels = new Channel *[maxChannelCount];
    }

    void addChannel(Channel *channel) {
        this->channels[channelCount] = channel;
        channelCount++;
    }

    void startEnable() {
        currentChannel = 0;
        enableCurrent();
    }

    bool nextEnable() {
        disableCurrent();

        currentChannel++;
        if (currentChannel < channelCount) {
            enableCurrent();
            return true;
        }

        Serial.println("Finish all channels");
        return false;
    }

    Channel *current() {
        return channels[currentChannel];
    }

private:

    byte channelCount = 0;
    byte currentChannel = 0;

    Channel **channels;

    void enableCurrent() {
        current()->relay->enable();
        Serial.print("Enable channel: ");
        Serial.println(currentChannel);
    }

    void disableCurrent() {
        current()->relay->disable();
        Serial.print("Disable channel: ");
        Serial.println(currentChannel);
    }
};


#endif
