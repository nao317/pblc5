#include "StateMachine.h"

void StateMachine::update(const SensorData& sensorData) {

    if(sensorData.frontDistance < 15) {
        Serial.println("Obstacle detected");
    }
}
