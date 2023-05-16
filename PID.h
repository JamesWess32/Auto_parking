#ifndef PID_H
#define PID_H
#include "Auto.h""
#include <Arduino.h>

class PID
{
public:
    PID();
    PID(float,float,float);
    int PID_module(Auto,float);


private:
    float current_SP;
    float Kp = 0;
    float Kd = 0;
    float Ki = 0;

    long prevT = 0;
    float eprev = 0;
    float eintegral = 0;
    volatile int posi = 0;
   
};

PID::PID()
{
}
PID::PID(float new_Kp, float new_Kd, float new_Ki)
{
    Kp = new_Kp;
    Kd = new_Kd;
    Ki = new_Ki;
    
}


int PID::PID_module(Auto maccquen, float new_SP)
{

    current_SP = new_SP;
    // time difference
    long currT = micros();
    float deltaT = ((float)(currT - prevT)) / (1.0e6);
    prevT = currT;

    // Read distance
    //sensores();
    // Read the position
    int pos = 0;
    noInterrupts(); // disable interrupts temporarily while reading
    pos = maccquen.get_encoder();
    interrupts(); // turn interrupts back on
    ///pos=(pos/ppr)*20.4204;
    //  error
    int e = pos - current_SP;
    
    // derivative
    float dedt = (e - eprev) / (deltaT);

    // integral
    eintegral = eintegral + e * deltaT;

    // control signal
    float u = Kp * e + Kd * dedt + Ki * eintegral;
    
    // store previous error
    eprev = e;
    
    //   motor power
    float pwr = fabs(u);
    if (pwr > 100)
    {
        pwr = 100;
        
    }
    
    
    // motor direction
    int d = 1;
    if(u < 0)
    {
        d = -1;    
    }

    maccquen.change_PWM(pwr);
    if(d==1){
        maccquen.move_back();
    }else
    {
        maccquen.move_on();
    }

    Serial.print(current_SP);
    Serial.print(" ");
    Serial.print(pos);
    Serial.println();
}

#endif // PID_H
