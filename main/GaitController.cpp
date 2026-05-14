#include "GaitController.h"

void GaitController::update(const GaitParameters& params) {

    for(int i = 0; i < 4; i++) {

        targets[i].x = params.stepLength;
        targets[i].y = 0;

        if(params.climbingMode) {
            targets[i].z = -params.bodyHeight + params.stepHeight;
        }
        else {
            targets[i].z = -params.bodyHeight;
        }
    }
}

LegTarget* GaitController::getTargets() {
    return targets;
}
