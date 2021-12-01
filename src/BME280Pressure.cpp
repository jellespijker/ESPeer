//
// Created by peer23peer on 28-11-21.
//

#include "BME280Pressure.h"
#include "Debug.h"

BME280Pressure::BME280Pressure(std::string topic, const int delay, Adafruit_BME280 *bme) :
        ESPSensor(std::move(topic), delay),
        m_bme(bme) {}

BME280Pressure::~BME280Pressure() {
    delete m_bme;
}

void BME280Pressure::init() {}

bool BME280Pressure::task() {
    if (millis() >= m_last_update + m_delay) {
        m_last_update = millis();
        auto value = m_bme->readPressure() / 100;
        if (m_value != value) {
            m_value = value;
            return true;
        }
#ifdef DEBUG
        Serial.println("Obtain pressure from BME280: " + String(m_value));
#endif
    }
    return false;
}