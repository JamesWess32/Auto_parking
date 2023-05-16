#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder
{
public:
    Encoder(int pinA, int pinB); // constructor to initialize encoder pins and attach interrupts
    long getPosition();          // returns the current position of the encoder

private:
    static void handleInterruptA(); // interrupt handler for encoder pin A
    static void handleInterruptB(); // interrupt handler for encoder pin B
    int _pinA;                      // encoder pin A
    int _pinB;                      // encoder pin B
    volatile long _position;        // current position of the encoder
    static Encoder *instance;       // static instance of the encoder class
};

Encoder *Encoder::instance = nullptr; // initialize the static instance to null

Encoder::Encoder(int pinA, int pinB)
{
    _pinA = pinA;
    _pinB = pinB;
    pinMode(_pinA, INPUT_PULLUP);                                            // configure encoder pin A as input with internal pull-up resistor
    pinMode(_pinB, INPUT_PULLUP);                                            // configure encoder pin B as input with internal pull-up resistor
    attachInterrupt(digitalPinToInterrupt(_pinA), handleInterruptA, CHANGE); // attach interrupt for encoder pin A
    attachInterrupt(digitalPinToInterrupt(_pinB), handleInterruptB, CHANGE); // attach interrupt for encoder pin B
    _position = 0;                                                           // initialize the position to zero
    instance = this;                                                         // assign the instance to the current object
}

long Encoder::getPosition()
{
    return _position; // return the current position of the encoder
}

void Encoder::handleInterruptA()
{
    if (digitalRead(instance->_pinA) == digitalRead(instance->_pinB)) // check the logic level of encoder pin B
    {
        instance->_position++; // increment the position if the logic level of encoder pin B is the same as that of encoder pin A
    }
    else
    {
        instance->_position--; // decrement the position if the logic level of encoder pin B is different from that of encoder pin A
    }
}

void Encoder::handleInterruptB()
{
    if (digitalRead(instance->_pinA) != digitalRead(instance->_pinB)) // check the logic level of encoder pin A
    {
        instance->_position++; // increment the position if the logic level of encoder pin A is different from that of encoder pin B
    }
    else
    {
        instance->_position--; // decrement the position if the logic level of encoder pin A is the same as that of encoder pin B
    }
}

#endif // ENCODER_H
