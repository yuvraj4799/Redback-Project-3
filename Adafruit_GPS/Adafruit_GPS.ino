#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

// Define the pins for the SoftwareSerial communication
#define GPS_RX_PIN 1
#define GPS_TX_PIN 0

// Create a SoftwareSerial object for communication with the GPS module
SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

// Create an Adafruit_GPS object
Adafruit_GPS GPS(&gpsSerial);

void setup() {
  // Start the serial communication for debugging
  Serial.begin(9600);

  // Initialize the GPS module
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  // Enable the desired GPS sentences
  GPS.sendCommand(PMTK_ENABLE_SBAS);
  GPS.sendCommand(PMTK_ENABLE_WAAS);
}

void loop() {
  // Read data from the GPS module
  char c = GPS.read();

  // If a new valid sentence has been parsed, print it
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) {
      return; // Parsing failed, skip this sentence
    }

    // Check if the sentence is an RMC (Recommended Minimum) sentence
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitudeDegrees, 6);
      Serial.print(", ");
      Serial.print(GPS.longitudeDegrees, 6);
      Serial.print("  Speed: ");
      Serial.print(GPS.speed);
      Serial.print(" m/s  ");
      Serial.print("Time: ");
      Serial.print(GPS.hour);
      Serial.print(":");
      Serial.print(GPS.minute);
      Serial.print(":");
      Serial.print(GPS.seconds);
      Serial.println();
    }
  }
}
