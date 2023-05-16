#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

class UltrasonicSensor
{
public:
    UltrasonicSensor(int echoPin, int triggerPin);
    float getDistanceInCentimeters();

private:
    int _triggerPin;
    int _echoPin;
};

UltrasonicSensor::UltrasonicSensor(int echoPin, int triggerPin)
{
    _triggerPin = triggerPin;
    _echoPin = echoPin;
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

float UltrasonicSensor::getDistanceInCentimeters()
{
    float filtro = 0.8;
    float ultimo_valor = 0;
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);
    long duration = pulseIn(_echoPin, HIGH, 5000);
    float distance1 = duration / 58.0;
    return distance1;
}

#endif // ULTRASONIC_SENSOR_H
