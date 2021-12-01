//
// Created by peer23peer on 28-11-21.
//

#include "Debug.h"
#include "DHT22Humidity.h"

DHT22Humidity::DHT22Humidity(std::string topic, const int delay, DHT *dht) :
        ESPSensor(std::move(topic), delay),
        m_dht(dht) {}

DHT22Humidity::~DHT22Humidity() {
    delete m_dht;
}

void DHT22Humidity::init() {}

bool DHT22Humidity::task() {
    if (millis() >= m_last_update + m_delay) {
        m_last_update = millis();
        auto value = m_dht->readHumidity();
        if (m_value != value) {
            m_value = value;
            return true;
        }
#ifdef DEBUG
        Serial.println("Obtain humidty from DHT22: " + String(m_value));
#endif
    }
    return false;
}