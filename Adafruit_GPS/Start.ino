// Examples: Adafrut GPS Flora Start

#include <Adafruit_GPS.h>
#define GPSSerial Serial1

Adafruit_GPS GPS(&GPSSerial);
#define GPSECHO true

void setup()
{

    Serial.begin(115200);
    delay(1000);
    Serial.println("GPS logging start test");
    GPS.begin(9600);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    GPS.sendCommand(PGCMD_ANTENNA);
    GPS.sendCommand(PMTK_Q_RELEASE);
    Serial.print("\nSTARTING LOGGING....");
    if (GPS.LOCUS_StartLogger())
        Serial.println(" STARTED!");
    else
        Serial.println(" no response :(");
}

void loop()
{
    if (GPSSerial.available())
    {
        char c = GPSSerial.read();
        Serial.write(c);
    }

    // Do other things here....
}
