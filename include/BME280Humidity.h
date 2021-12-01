//
// Created by peer23peer on 28-11-21.
//

#ifndef ESPEER_BME280HUMIDITY_H
#define ESPEER_BME280HUMIDITY_H

#include "ESPSensor.h"

#include <Adafruit_BME280.h>

class BME280Humidity : public ESPSensor {

public:
    explicit BME280Humidity(std::string topic, int delay, Adafruit_BME280 *bme);

    ~BME280Humidity();

    void init() override;

    [[maybe_unused]] bool task() override;

private:
    Adafruit_BME280 *m_bme;
};

#endif //ESPEER_BME280HUMIDITY_H
