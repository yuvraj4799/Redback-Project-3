#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "BluefruitConfig.h"

// Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// Replace these placeholders with actual pin values
#define BLUEFRUIT_SPI_CS 10
#define BLUEFRUIT_SPI_IRQ 7
#define BLUEFRUIT_SPI_RST 4

void setup()
{
    while (!Serial)
        ; // Wait for Serial Monitor to open
    Serial.begin(115200);

    if (!ble.begin(VERBOSE_MODE))
    {
        Serial.println(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
        while (1)
            ;
    }

    ble.echo(false);

    Serial.println(F("Adafruit Bluefruit LE App Example"));
    Serial.println(F("----------------------------------"));

    // Wait for a connection to be established
    while (!ble.isConnected())
    {
        delay(500);
    }

    Serial.println(F("Connected to Adafruit Bluefruit LE App"));
}

void loop()
{
    // Generate a random number between 0 and 100
    int randomNumber = random(101);

    // Convert the random number to a string
    char randomData[6]; // Maximum of 5 characters plus null terminator
    snprintf(randomData, sizeof(randomData), "%d", randomNumber);

    // Send the random data to the Adafruit Bluefruit LE App
    ble.print("AT+BLEUARTTX=");
    ble.println(randomData);

    // Wait for a short period before sending the next random data
    delay(1000);
}
