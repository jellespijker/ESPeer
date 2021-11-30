//
// Created by peer23peer on 28-11-21.
//

#include "BME280Temperature.h"
#include "Debug.h"

BME280Temperature::BME280Temperature(Adafruit_BME280* bme) {
    m_bme = bme;
    m_delay = 2000;
    m_last_update = millis();
}

void BME280Temperature::init() {

}

void BME280Temperature::task() {
    if (millis() >= m_last_update + m_delay) {
        m_last_update = millis();
        m_value = m_bme->readTemperature();
#ifdef DEBUG
        Serial.println("Obtain temperature from BME280: " + String(m_value));
#endif
    }
}

float BME280Temperature::getValue() const {
    return m_value;
}
