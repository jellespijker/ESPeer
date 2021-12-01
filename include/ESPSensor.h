//
// Created by peer23peer on 28-11-21.
//

#ifndef ESPEER_ESPSENSOR_H
#define ESPEER_ESPSENSOR_H

#include <string_view>
#include <string>
#include <utility>

#include <core_esp8266_features.h>

class ESPSensor {
public:
    ESPSensor(std::string topic, const int delay) : m_topic(std::move(topic)),
                                                    m_delay(delay),
                                                    m_last_update(millis()),
                                                    m_value(0.0) {};

    virtual void init() = 0;

    [[maybe_unused]] virtual bool task() = 0;

    [[nodiscard]] virtual std::string &getTopic() { return m_topic; };

    [[nodiscard]] virtual float getValue() const { return m_value; };

protected:
    std::string m_topic;
    int m_delay;
    unsigned long m_last_update;
    float m_value;
};

#endif //ESPEER_ESPSENSOR_H
