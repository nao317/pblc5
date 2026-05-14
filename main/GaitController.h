#ifndef GAIT_CONTROLLER_H
#define GAIT_CONTROLLER_H

#include <Arduino.h>
#include "GaitParameters.h"
struct LegTarget {
    float x;
    float y;
    float z;
};

class GaitController {
private:
    LegTarget targets[4];

public:
    void update(const GaitParameters& params);

    LegTarget* getTargets();
};

#endif