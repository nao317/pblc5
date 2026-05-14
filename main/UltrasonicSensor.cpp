#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(
    int trig,
    int echo
) {
    trigPin = trig;
    echoPin = echo;
}

void UltrasonicSensor::setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float UltrasonicSensor::readDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration =
        pulseIn(echoPin, HIGH);
    float distance =
        duration * 0.343f / 2.0f;
    return distance;
}

