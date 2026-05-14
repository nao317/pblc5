#ifndef RobotController_h
#define RobotController_h

#include "SensorData.h"
#include "UltrasonicSensor.h"
#include "GaitParameters.h"
#include "GaitController.h"
#include "LegController.h"
#include "StateMachine.h"

class RobotController {
private:
    SensorData sensorData;
    GaitParameters gaitParameters;
    GaitController gaitController;
    LegController legController;
    StateMachine stateMachine;

    // 超音波センサ
    UltrasonicSensor frontSensor;
    UltrasonicSensor downFrontSensor;
    UltrasonicSensor downRearSensor;
    void readSensors();
    void updateGaitParameters();

public:
    RobotController();
    void setup();
    void update();
};

#endif

