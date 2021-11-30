//
// Created by peer23peer on 28-11-21.
//

#include "BME280Humidity.h"
#include "Debug.h"

BME280Humidity::BME280Humidity(Adafruit_BME280* bme) {
m_bme = bme;
m_delay = 2000;
m_last_update = millis();
}

void BME280Humidity::init() {

}

void BME280Humidity::task() {
    if (millis() >= m_last_update + m_delay) {
        m_last_update = millis();
        m_value = m_bme->readHumidity();
#ifdef DEBUG
        Serial.println("Obtain humidity from BME280: " + String(m_value));
#endif
    }
}

float BME280Humidity::getValue() const {
    return m_value;
}
