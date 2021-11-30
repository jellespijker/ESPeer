//
// Created by peer23peer on 28-11-21.
//

#ifndef ESPEER_BME280HUMIDITY_H
#define ESPEER_BME280HUMIDITY_H

#include "ESPSensor.h"

#include <Adafruit_BME280.h>

class BME280Humidity : public ESPSensor {

public:
    explicit BME280Humidity(Adafruit_BME280* bme);

    ~BME280Humidity() = default;

    void init() override;

    void task() override;

    [[nodiscard]] float getValue() const override;

private:
    Adafruit_BME280* m_bme;
    float m_value{};
    int m_delay{};
    unsigned long m_last_update{};
};

#endif //ESPEER_BME280HUMIDITY_H
