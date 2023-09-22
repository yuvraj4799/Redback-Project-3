#include <Adafruit_GPS.h>
#define GPSSerial Serial1
Adafruit_GPS GPS(&GPSSerial);
#define GPSECHO false
uint32_t timer = millis();
const String id = "1";

void setup()
{
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic parsing test!");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  GPSSerial.println(PMTK_Q_RELEASE);
}

void loop()
{
  char c = GPS.read();
  if (GPSECHO)
    if (c)
      Serial.print(c);
  if (GPS.newNMEAreceived())
  {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }
  if (millis() - timer > 2000)
  {
    Serial.print(id + " ");
    timer = millis();
    if (GPS.hour < 10)
    {
      Serial.print('0');
    }
    Serial.print(GPS.hour, DEC);
    Serial.print(':');
    if (GPS.minute < 10)
    {
      Serial.print('0');
    }
    Serial.print(GPS.minute, DEC);
    Serial.print(':');
    if (GPS.seconds < 10)
    {
      Serial.print('0');
    }
    Serial.print(GPS.seconds, DEC);
    Serial.print('.');
    if (GPS.milliseconds < 10)
    {
      Serial.print("00");
    }
    else if (GPS.milliseconds > 9 && GPS.milliseconds < 100)
    {
      Serial.print("0");
    }
    Serial.print(GPS.milliseconds);
    Serial.print(" ");
    Serial.print(GPS.day, DEC);
    Serial.print('/');
    Serial.print(GPS.month, DEC);
    Serial.print("/20");
    Serial.print(GPS.year, DEC);
    if (GPS.fix)
    {
      Serial.print(" ");
      Serial.print(GPS.latitude, 4);
      Serial.print(GPS.lat);
      Serial.print(" ");
      Serial.print(GPS.longitude, 4);
      Serial.print(GPS.lon);
      Serial.print(" ");
      Serial.print(GPS.altitude);
      Serial.print(" ");
      Serial.println((int)GPS.satellites);
    }
  }
}
