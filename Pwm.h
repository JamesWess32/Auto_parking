#ifndef PWMOUTPUT_H
#define PWMOUTPUT_H

#include <Arduino.h>

class PWM
{
public:
    PWM(int pin);
    void setDutyCycle(float dutyCycle);

private:
    int _pin;
};

PWM::PWM(int pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void PWM::setDutyCycle(float dutyCycle)
{
    dutyCycle = constrain(dutyCycle, 0, 255); // ensure duty cycle is within valid range
    analogWrite(_pin, dutyCycle);
}

#endif // PWMOUTPUT_H
