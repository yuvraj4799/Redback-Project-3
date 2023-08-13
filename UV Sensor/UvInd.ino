#include <Wire.h>

// Define the I2C address of the Flora UV Index sensor
#define FLORA_UV_SENSOR_ADDR 0x70

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    // Initialize communication with the Flora UV Index sensor
    Wire.beginTransmission(FLORA_UV_SENSOR_ADDR);
    Wire.write(0x03); // Command to request UV index reading
    Wire.endTransmission();
}

void loop()
{
    // Request UV index reading
    Wire.requestFrom(FLORA_UV_SENSOR_ADDR, 2);

    // Read the UV index data
    if (Wire.available() >= 2)
    {
        byte msb = Wire.read();
        byte lsb = Wire.read();

        // Combine the bytes to get the UV index value
        unsigned int uvIndex = (msb << 8) | lsb;

        Serial.print("UV Index: ");
        Serial.println(uvIndex);

        delay(1000);
    }
}
