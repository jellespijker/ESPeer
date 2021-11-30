//
// Created by peer23peer on 28-11-21.
//

#include "Debug.h"
#include "DHT22Temperature.h"

DHT22Temperature::DHT22Temperature(DHT* dht) {
    m_dht = dht;
    m_delay = 2000;
    m_last_update = millis();
}

void DHT22Temperature::init() {

}

void DHT22Temperature::task() {
    if (millis() >= m_last_update + m_delay) {
        m_last_update = millis();
        m_value = m_dht->readTemperature();
#ifdef DEBUG
        Serial.println("Obtain temperature from DHT22: " + String(m_value));
#endif
    }
}

float DHT22Temperature::getValue() const {
    return m_value;
}
