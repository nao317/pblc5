#include "RobotController.h"

RobotController::RobotController()
    :
    frontSensor(2, 3),
    downFrontSensor(4, 5),
    downRearSensor(6, 7)
{

}

void RobotController::setup() {
    frontSensor.setup();
    downFrontSensor.setup();
    downRearSensor.setup();
    gaitParameters.stepLength = 50;
    gaitParameters.stepHeight = 30;
    gaitParameters.cycleTime = 1.0f;
    gaitParameters.bodyHeight = 120;
    gaitParameters.turnRate = 0;
    gaitParameters.climbingMode = false;
}

void RobotController::update() {
    readSensors();
    stateMachine.update(sensorData);
    updateGaitParameters();
    gaitController.update(
        gaitParameters
    );
    legController.update(
        gaitController.getTargets()
    );
}

void RobotController::readSensors() {
    sensorData.frontDistance = frontSensor.readDistance();
    sensorData.downFrontDistance = downFrontSensor.readDistance();
    sensorData.downRearDistance = downRearSensor.readDistance();
}

void RobotController::updateGaitParameters() {

    if (sensorData.frontDistance < 150) {

        gaitParameters.climbingMode = true;
        gaitParameters.stepHeight = 60;

    } else {

        gaitParameters.climbingMode = false;
        gaitParameters.stepHeight = 30;
    }
}



