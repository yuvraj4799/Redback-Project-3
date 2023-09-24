#include "thingProperties.h"
#include <DHT.h>
#define DHTPIN 6
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);
    delay(1500);
    pinMode(LED_BUILTIN, OUTPUT);
    dht.begin();
    initProperties();
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);
    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();
}

void loop()
{
    ArduinoCloud.update();
    temp = dht.readTemperature();
    delay(1000);
}

void onLedChange()
{
    digitalWrite(LED_BUILTIN, led);
}
