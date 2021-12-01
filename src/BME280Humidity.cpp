//
// Created by peer23peer on 28-11-21.
//

#include "BME280Humidity.h"
#include "Debug.h"

BME280Humidity::BME280Humidity(std::string topic, const int delay, Adafruit_BME280 *bme) :
        ESPSensor(std::move(topic), delay),
        m_bme(bme) {}

BME280Humidity::~BME280Humidity() {
    delete m_bme;
}

void BME280Humidity::init() {}

bool BME280Humidity::task() {
    if (millis() >= m_last_update + m_delay) {
        m_last_update = millis();
        auto value = m_bme->readHumidity();
        if (m_value != value) {
            m_value = value;
            return true;
        }
#ifdef DEBUG
        Serial.println("Obtain humidity from BME280: " + String(m_value));
#endif
    }
    return false;
}
