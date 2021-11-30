//
// Created by peer23peer on 28-11-21.
//

#include <HardwareSerial.h>

#include "Debug.h"
#include "HomeAssistant.h"
#include "Credentials.h"


HomeAssistant::HomeAssistant() {

}

void HomeAssistant::connect() {
#ifdef DEBUG
    Serial.println("\n\nTrying to establish connections.");
#endif
    if (!WiFi.isConnected()) {
        Serial.println("Trying to connect to WiFi: " + String(ssid) + " using password: " + password);
        WiFi.begin(ssid, password);
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
      Serial.println("Trying to connect to MQTT server: " + String(mqtt_server) + " using port: " + String(mqtt_port));
#endif
        m_client.begin(mqtt_server, mqtt_port, m_net);
#ifdef DEBUG
        Serial.println("Using ID: " + String(mqtt_id));
        Serial.println("Using user: " + String(mqtt_user));
        Serial.println("Using password: " + String(mqtt_password));
#endif
        while (!m_client.connect(mqtt_id, mqtt_user, mqtt_password)) {
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
    for (auto sensor : m_sensors) {
        sensor->task();
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
