#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <Arduino.h>
#include "SensorData.h"
class StateMachine {
public:
    void update(const SensorData& sensorData);
};

#endif
