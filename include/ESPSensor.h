//
// Created by peer23peer on 28-11-21.
//

#ifndef ESPEER_ESPSENSOR_H
#define ESPEER_ESPSENSOR_H

class ESPSensor {
public:
    virtual void init() = 0;
    virtual void task() = 0;
    [[nodiscard]] virtual float getValue() const = 0;
};

#endif //ESPEER_ESPSENSOR_H
