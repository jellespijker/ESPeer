//
// Created by peer23peer on 28-11-21.
//

#ifndef ESPEER_BME280TEMPERATURE_H
#define ESPEER_BME280TEMPERATURE_H

#include "ESPSensor.h"

#include <Adafruit_BME280.h>

class BME280Temperature : public ESPSensor {

public:
    explicit BME280Temperature(Adafruit_BME280* bme);

    ~BME280Temperature() = default;

    void init() override;

    void task() override;

    [[nodiscard]] float getValue() const override;

private:
    Adafruit_BME280* m_bme;
    float m_value{};
    int m_delay{};
    unsigned long m_last_update{};
};

#endif //ESPEER_BME280TEMPERATURE_H
