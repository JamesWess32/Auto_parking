#ifndef AUTO_H
#define AUTO_H

#include <Arduino.h>
#include "Encoder.h"
#include "Ultrasonic.h"
#include "Pwm.h"
#include <Servo.h>
/////////////////////////////////ENCODER//////////////////////////
#define encoderPinA 2
#define encoderPinB 3
//////////////////////////ULTRASONICOS DELANTEROS/////////////////
#define d01_echoPin 39
#define d01_triggerPin 38

#define d02_echoPin 46
#define d02_triggerPin 47

#define d03_echoPin 37
#define d03_triggerPin 36
///////////////////////////ULTRASONICOS TRASEROS//////////////////
#define t01_echoPin 40
#define t01_triggerPin 41

#define t02_echoPin 42
#define t02_triggerPin 43

#define t03_echoPin 45
#define t03_triggerPin 44

///////////////////////////////SERVO/////////////////////////////
#define servoPin 10
///////////////////////////////PWM///////////////////////////////
#define pwmPin 5
//////////////////////////////MOTOR//////////////////////////////
#define motorPinA 6
#define motorPinB 7

//OBJETOS CREADOS
Encoder encoder(encoderPinA, encoderPinB);
UltrasonicSensor ultrasonic_sensor[6] = {
    UltrasonicSensor(d01_echoPin, d01_triggerPin),
    UltrasonicSensor(d02_echoPin, d02_triggerPin),
    UltrasonicSensor(d03_echoPin, d03_triggerPin),
    UltrasonicSensor(t01_echoPin, t01_triggerPin),
    UltrasonicSensor(t02_echoPin, t02_triggerPin),
    UltrasonicSensor(t03_echoPin, t03_triggerPin)
};

PWM pwm_output(pwmPin);
Servo moto_servo;


class Auto
{
public:
    Auto(int, int); ///grados 0-180% and 0-255
    Auto();
    void move_on();
    void move_back();
    void move_stop();
    float get_ultrasonic_sensor(String);
    long get_encoder();
    void change_PWM(float);
    void turn(int);
    void take_reference();
    float get_reference();

private:
       float reference = 0.0;
};
Auto::Auto()
{
    
}
Auto::Auto(int init_position, int pwm)
{
    moto_servo.attach(servoPin);
    turn(init_position);
    change_PWM(pwm);
}
void Auto::change_PWM(float new_pwm)
{
    pwm_output.setDutyCycle(new_pwm);
}

void Auto::move_on()
{
    digitalWrite(motorPinA, HIGH);
    digitalWrite(motorPinB, LOW);
}

void Auto::move_back()
{
    digitalWrite(motorPinA, LOW);
    digitalWrite(motorPinB, HIGH);
}

void Auto::move_stop()
{
    digitalWrite(motorPinA, LOW);
    digitalWrite(motorPinB, LOW);
}

float Auto::get_ultrasonic_sensor(String inputString)
{
    if (inputString == "d01")
    {
        return ultrasonic_sensor[0].getDistanceInCentimeters();
    }
    else if (inputString == "d02")
    {
        return ultrasonic_sensor[1].getDistanceInCentimeters();
    }
    else if (inputString == "d03")
    {
        return ultrasonic_sensor[2].getDistanceInCentimeters();
    }
    else if (inputString == "t01")
    {
        return ultrasonic_sensor[3].getDistanceInCentimeters();
    }
    else if (inputString == "t02")
    {
        return ultrasonic_sensor[4].getDistanceInCentimeters();
    }

    else if (inputString == "t03")
    {
        return ultrasonic_sensor[5].getDistanceInCentimeters();
    }
    else
    {
        // Nothing
    }
}


long Auto::get_encoder()
{
    return encoder.getPosition();
}

void Auto::turn(int grades)
{
    
    moto_servo.write(grades);
}

void Auto::take_reference()
{

    reference = get_ultrasonic_sensor("t03");
}

float Auto::get_reference()
{

    return reference;
}

#endif // ULTRASONIC_SENSOR_H
