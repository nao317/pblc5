#ifndef SensorData_h
#define SensorData_h

struct SensorData {

    // 超音波センサで計測した距離 [mm]
    float frontDistance;
    float leftDistance;
    float rightDistance;
    float downFrontDistance;
    float downRearDistance;

    // IMU
    float pitch;
    float roll;
    float yaw;

    // 足をコントロールするための真理値
    bool flContact;
    bool frContact;
    bool rlContact;
    bool rrContact;
};
#endif

