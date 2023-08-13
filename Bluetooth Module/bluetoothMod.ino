#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BLEUtils.h>
#include <Adafruit_BLEBattery.h>
#include <Adafruit_BLEGatt.h>

#define BLE_REQ
#define BLE_RDY
#define BLE_RST

Adafruit_BluefruitLE_SPI ble(BLE_REQ, BLE_RDY, BLE_RST);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    if (!ble.begin(VERBOSE_MODE))
    {
        Serial.println("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?");
        while (1)
            ;
    }

    ble.echo(false);

    Serial.println("Bluefruit initialized!");

    ble.setAdvertisingInterval(32, 244);
    ble.advertise();
}

void loop()
{
    ble.update(1000);

    if (ble.isConnected())
    {
    }
}
