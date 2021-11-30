//
// Created by peer23peer on 28-11-21.
//

#ifndef ESPEER_DHT22HUMIDITY_H
#define ESPEER_DHT22HUMIDITY_H

#include <DHT.h>

#include "ESPSensor.h"

class DHT22Humidity : public ESPSensor {
public:
    explicit DHT22Humidity(DHT* dht);

    ~DHT22Humidity() = default;

    void init() override;

    void task() override;

    [[nodiscard]] float getValue() const override;

private:
    DHT* m_dht;
    float m_value{};
    int m_delay{};
    unsigned long m_last_update{};
};

#endif //ESPEER_DHT22HUMIDITY_H
