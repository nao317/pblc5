#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h

class UltrasonicSensor {

private:
    int trigPin;
    int echoPin;

public:
    UltrasonicSensor(
        int trig,
        int echo
    );
    void setup();
    float readDistance();
};

#endif

