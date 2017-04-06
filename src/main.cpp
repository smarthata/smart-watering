#include <Arduino.h>
#include <DS3231.h>
#include <Relay.h>

DS3231 clock;
bool h12 = false;
bool PM = false;

Relay relay(13);

void setup() {
    Serial.begin(9600);
    Wire.begin();
}

void loop() {

    relay.enable();
    delay(500);
    relay.disable();

    Serial.print(clock.getHour(h12, PM));
    Serial.print(':');
    Serial.print(clock.getMinute());
    Serial.print(':');
    Serial.println(clock.getSecond());
    delay(500);
}
