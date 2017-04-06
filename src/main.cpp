#include <Arduino.h>
#include <DS3231.h>

DS3231 clock;
bool h12 = false;
bool PM = false;

void setup() {
    Serial.begin(9600);
    Wire.begin();
}

void loop() {
    Serial.println(millis());
    Serial.print(clock.getHour(h12, PM));
    Serial.print(':');
    Serial.print(clock.getMinute());
    Serial.print(':');
    Serial.println(clock.getSecond());
    delay(1000);
}
