//
// Created by peer23peer on 28-11-21.
//

#include "Debug.h"
#include "DHT22Humidity.h"

DHT22Humidity::DHT22Humidity(DHT* dht) {
    m_dht = dht;
    m_delay = 2000;
    m_last_update = millis();
}

void DHT22Humidity::init() {

}

void DHT22Humidity::task() {
    if (millis() >= m_last_update + m_delay) {
        m_last_update = millis();
        m_value = m_dht->readHumidity();
#ifdef DEBUG
        Serial.println("Obtain humidty from DHT22: " + String(m_value));
#endif
    }
}

float DHT22Humidity::getValue() const {
    return m_value;
}
