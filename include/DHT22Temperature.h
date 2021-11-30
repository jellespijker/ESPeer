//
// Created by peer23peer on 28-11-21.
//

#ifndef ESPEER_DHT22TEMPERATURE_H
#define ESPEER_DHT22TEMPERATURE_H

#include <DHT.h>

#include "ESPSensor.h"


class DHT22Temperature : public ESPSensor {
public:
    explicit DHT22Temperature(DHT* dht);

    ~DHT22Temperature() = default;

    void init() override;

    void task() override;

    [[nodiscard]] float getValue() const override;

private:
    DHT* m_dht;
    float m_value{};
    int m_delay{};
    unsigned long m_last_update{};
};

#endif //ESPEER_DHT22TEMPERATURE_H
