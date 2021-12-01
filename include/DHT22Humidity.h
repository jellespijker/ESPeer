//
// Created by peer23peer on 28-11-21.
//

#ifndef ESPEER_DHT22HUMIDITY_H
#define ESPEER_DHT22HUMIDITY_H

#include <DHT.h>

#include "ESPSensor.h"

class DHT22Humidity : public ESPSensor {
public:
    explicit DHT22Humidity(std::string topic, int delay, DHT *dht);

    ~DHT22Humidity();

    void init() override;

    [[maybe_unused]] bool task() override;

private:
    DHT *m_dht;
};

#endif //ESPEER_DHT22HUMIDITY_H
