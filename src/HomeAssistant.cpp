//
// Created by peer23peer on 28-11-21.
//

#include <HardwareSerial.h>

#include <utility>

#include "Debug.h"
#include "HomeAssistant.h"

HomeAssistant::HomeAssistant(std::string mqtt_id) : m_mqtt_id(std::move(mqtt_id)) {}

void HomeAssistant::connect(const std::string &ssid, const std::string &password, const std::string &server, int port,
                            const std::string &user, const std::string &mqtt_password) {
#ifdef DEBUG
    Serial.println("\n\nTrying to establish connections.");
#endif
    if (!WiFi.isConnected()) {
        WiFi.begin(ssid.data(), password.data());
        while (!WiFi.isConnected()) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(500);
#ifdef DEBUG
            Serial.print(".");
#endif
        }
#ifdef DEBUG
        Serial.println("Connected to WiFi, assigned IP: " + getLocalIP());
#endif
    }
    if (!m_client.connected()) {
#ifdef DEBUG
        Serial.print("Trying to connect to MQTT server: ");
        Serial.print(server.data());
        Serial.print(" using port: ");
        Serial.println(std::to_string(port).data());
#endif
        m_client.begin(server.data(), port, m_net);
#ifdef DEBUG
        Serial.print("Using ID: ");
        Serial.println(m_mqtt_id.data());
        Serial.print("Using user: ");
        Serial.println(user.data());
        Serial.print("Using password: ");
        Serial.println(mqtt_password.data());
#endif
        while (!m_client.connect(m_mqtt_id.data(), user.data(), mqtt_password.data())) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(50);
            digitalWrite(LED_BUILTIN, LOW);
            delay(240);
#ifdef DEBUG
            Serial.print(".");
#endif
        }
    }
#ifdef DEBUG
    Serial.println("MQTT connected.");
#endif
    digitalWrite(LED_BUILTIN, HIGH);
}

void HomeAssistant::task() {
    for (auto sensor: m_sensors) {
        if (sensor->task()) {
            auto topic = m_mqtt_id + sensor->getTopic();
            m_client.publish(topic.data(), std::to_string(sensor->getValue()).data());
        }
    }
}

bool HomeAssistant::isConnected() {
    return WiFi.isConnected() && m_client.connected();
}

String HomeAssistant::getLocalIP() {
    return WiFi.localIP().toString();
}

void HomeAssistant::addSensor(ESPSensor *sensor) {
    m_sensors.push_back(sensor);
}
