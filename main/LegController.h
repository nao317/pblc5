#ifndef LEG_CONTROLLER_H
#define LEG_CONTROLLER_H

#include <Arduino.h>
#include "GaitController.h"

class LegController {
public:
    void update(LegTarget* targets);
};

#endif