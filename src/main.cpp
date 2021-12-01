#include <Wire.h>
#include <SPI.h>

#include "Debug.h"
#include "Credentials.h"
#include "HomeAssistant.h"
#include "DHT22Temperature.h"
#include "DHT22Humidity.h"
#include "BME280Pressure.h"
#include "BME280Temperature.h"
#include "BME280Humidity.h"

HomeAssistant ha{std::string{mqtt_id}};

constexpr int dht22_pin = 0;
DHT dht{dht22_pin, DHT22};

Adafruit_BME280 bme280{};

unsigned long lastMillis = 0;

void setup() {
    // Setup pins
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(dht22_pin, INPUT);

#ifdef DEBUG
    Serial.begin(115200);  // Setup Serial
#endif

    // Connect to the Home Assistant
    ha.connect(ssid, password, mqtt_server, mqtt_port, mqtt_user, mqtt_password);

    // Setup BME280
    Wire.begin();
    bme280.begin(0x77, &Wire);
    ha.addSensor(new BME280Pressure{"/climate/pressure/0", 1000, &bme280});
    ha.addSensor(new BME280Humidity{"/climate/humidity/0", 1000, &bme280});
    ha.addSensor(new BME280Temperature{"/climate/temperature/0", 1000, &bme280});

    // Setup the DHT22Sensor sensor
    dht.begin();
    ha.addSensor(new DHT22Temperature{"/climate/temperature/1", 2000, &dht});
    ha.addSensor(new DHT22Humidity{"/climate/humidity/1", 2000, &dht});
}

void loop() {
    ha.task();
    delay(10);  // <- fixes some issues with WiFi stability

    if (!ha.isConnected()) {
        ha.connect(ssid, password, mqtt_server, mqtt_port, mqtt_user, mqtt_password);
    }
}
