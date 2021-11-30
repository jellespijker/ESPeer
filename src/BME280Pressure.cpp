//
// Created by peer23peer on 28-11-21.
//

#include "BME280Pressure.h"
#include "Debug.h"

BME280Pressure::BME280Pressure(Adafruit_BME280* bme) {
    m_bme = bme;
    m_delay = 2000;
    m_last_update = millis();
}

void BME280Pressure::init() {

}

void BME280Pressure::task() {
    if (millis() >= m_last_update + m_delay) {
        m_last_update = millis();
        m_value = m_bme->readPressure();
#ifdef DEBUG
        Serial.println("Obtain pressure from BME280: " + String(m_value));
#endif
    }
}

float BME280Pressure::getValue() const {
    return m_value;
}
