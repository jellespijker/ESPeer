//
// Created by peer23peer on 28-11-21.
//

#include "Debug.h"
#include "DHT22Temperature.h"

DHT22Temperature::DHT22Temperature(std::string topic, const int delay, DHT *dht) :
        ESPSensor(std::move(topic), delay),
        m_dht(dht) {}

DHT22Temperature::~DHT22Temperature() {
    delete m_dht;
}

void DHT22Temperature::init() {}

bool DHT22Temperature::task() {
    if (millis() >= m_last_update + m_delay) {
        m_last_update = millis();
        auto value = m_dht->readTemperature();
        if (m_value != value) {
            m_value = value;
            return true;
        }
#ifdef DEBUG
        Serial.println("Obtain temperature from DHT22: " + String(m_value));
#endif
    }
    return false;
}
