# ESPeer

Simple extendable NodeMCU ESP8266 project to read out various sensors and
publish the result via MQTT. Such that they can be used in my Home Assistant.

*Nothing to fancy.*

To compile add your own `include/Credentials.h` containing the follow:

```c++
#ifndef ESPEER_CREDENTIALS_H
#define ESPEER_CREDENTIALS_H

const char* ssid = "ssid_you_want_to_connect_with";
const char* password = "ssid_password";
const char* mqtt_server = "ip_mqtt_server";
const char* mqtt_user = "user_mqtt";
const char* mqtt_password = "password_mqtt";
const char* mqtt_id = "id_of_this_device_for_mqtt";
const int mqtt_port = 1883; // or your own port

#endif //ESPEER_CREDENTIALS_H
```

# Implemented sensors

- DHT22
  - Humidity
  - Temperature
- BME280
  - Humidity
  - Temperature
  - Pressure