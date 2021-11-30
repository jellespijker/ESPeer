// This example uses an Adafruit Huzzah ESP8266
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <Wire.h>
#include <SPI.h>

#include "Debug.h"
#include "HomeAssistant.h"
#include "DHT22Temperature.h"
#include "DHT22Humidity.h"
#include "BME280Pressure.h"
#include "BME280Temperature.h"
#include "BME280Humidity.h"

HomeAssistant ha;

constexpr int dht22_pin = 0;
DHT dht{dht22_pin, DHT22};

Adafruit_BME280 bme280 {};

unsigned long lastMillis = 0;

void setup() {
    // Setup pins
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(dht22_pin, INPUT);

#ifdef DEBUG
    Serial.begin(115200);  // Setup Serial
#endif

    // Connect to the Home Assistant
    ha.connect();

    // Setup the DHT22Sensor sensor
    dht.begin();
    auto dht22Temperature = new DHT22Temperature {&dht};
    ha.addSensor(dht22Temperature);
    auto dht22Humidity = new DHT22Humidity {&dht};
    ha.addSensor(dht22Humidity);

    // Setup BME280
    Wire.begin();
    bool status;
    status = bme280.begin(0x77, &Wire);
    if (status)
    {
#ifdef DEBUG
      Serial.println("BME280 connected");
#endif
    }
    auto bme280Pressure = new BME280Pressure{&bme280};
    ha.addSensor(bme280Pressure);
    auto bme280Humidity = new BME280Humidity{&bme280};
    ha.addSensor(bme280Humidity);
    auto bme280Temperature = new BME280Temperature{&bme280};
    ha.addSensor(bme280Temperature);
}

void loop() {
    ha.task();
    delay(10);  // <- fixes some issues with WiFi stability

    if (!ha.isConnected()) {
        ha.connect();
    }
}
