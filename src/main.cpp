#include <Arduino.h>
#include <DS3231.h>
#include <Relay.h>
#include <Time.h>

DS3231 clock;
bool h12 = false;
bool PM = false;

Time time(21, 20, 30);

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
    Serial.println(time.equals(clock.getHour(h12, PM), clock.getMinute(), clock.getSecond()));
    delay(500);
}
