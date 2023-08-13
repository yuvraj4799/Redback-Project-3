// Examples:Adafruit_GPS : locus_erase

#include <Adafruit_GPS.h>
#define GPSSerial Serial1

Adafruit_GPS GPS(&GPSSerial);

#define GPSECHO true

void setup()
{
    while (!Serial)
        ;
    Serial.begin(115200);
    Serial.println("Adafruit GPS erase FLASH!");

    GPS.begin(9600);

    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_OFF);

    Serial.println("This code will ERASE the data log stored in the FLASH - Permanently!");
    Serial.print("Are you sure you want to do this? ");
    while (Serial.read() != 'Y')
        delay(10);
    Serial.println("\nERASING!!");
    delay(5000);
    GPS.sendCommand(PMTK_LOCUS_ERASE_FLASH);
    Serial.println("Erased");
}

void loop()
{
    if (GPSSerial.available())
    {
        char c = GPSSerial.read();
        if (GPSECHO)
            Serial.write(c);
    }
}