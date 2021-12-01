//
// Created by peer23peer on 28-11-21.
//

#ifndef ESPEER_HOMEASSISTANT_H
#define ESPEER_HOMEASSISTANT_H

#include <vector>

#include <ESP8266WiFi.h>
#include <MQTT.h>

#include "ESPSensor.h"

class HomeAssistant {
public:
    explicit HomeAssistant(std::string mqtt_id);

    void connect(const std::string &ssid, const std::string &password, const std::string &server, int port,
                 const std::string &user, const std::string &mqtt_password);

    void task();

    bool isConnected();

    static String getLocalIP();

    void addSensor(ESPSensor *sensor);

private:
    WiFiClient m_net;
    MQTTClient m_client;

    std::vector<ESPSensor *> m_sensors;
    std::string m_mqtt_id;
};

#endif //ESPEER_HOMEASSISTANT_H
