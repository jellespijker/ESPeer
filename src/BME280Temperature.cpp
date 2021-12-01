//
// Created by peer23peer on 28-11-21.
//

#include "BME280Temperature.h"
#include "Debug.h"

BME280Temperature::BME280Temperature(std::string topic, const int delay, Adafruit_BME280 *bme) :
        ESPSensor(std::move(topic), delay),
        m_bme(bme) {}

BME280Temperature::~BME280Temperature() {
    delete m_bme;
}

void BME280Temperature::init() {}

bool BME280Temperature::task() {
    if (millis() >= m_last_update + m_delay) {
        m_last_update = millis();
        auto value = m_bme->readTemperature();
        if (m_value != value) {
            m_value = value;
            return true;
        }
#ifdef DEBUG
        Serial.println("Obtain temperature from BME280: " + String(m_value));
#endif
    }
    return false;
}