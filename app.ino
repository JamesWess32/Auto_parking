#include "Auto.h"
#include "PID.h"

#define init_position 81
#define pwm 120

float Ki = 0.0;
float Kd = 0.06;
float Kp = 0.35;
int Phase = 1;

Auto rayo_maccquen;
PID control;

unsigned long tiempoInicial;

void setup()
{
  
  Serial.begin(9600);
  rayo_maccquen = Auto(init_position, pwm);
  control = PID(Kp,Kd,Ki);
  delay(2000);
  rayo_maccquen.take_reference();
}
void loop(){
  //rayo_maccquen.move_on();
  //Backing_up();
  //Stopping_phase();
  //Serial.println(rayo_maccquen.get_ultrasonic_sensor("d01"));
  //Serial.println("d03: " + String(rayo_maccquen.get_ultrasonic_sensor("d03")));
  //delay(800);

  switch (Phase)
  {

  case 1:
    
    PhaseOne();
    break;
  case 2:
    delay(100);
    PhaseTwo();
    break;
  case 3:
    PhaseThree();
    //rayo_maccquen.move_back();
    //delay(1800);
    //rayo_maccquen.turn(55);
    //delay(1000);
    //Phase++;
    //rayo_maccquen.move_back();
    //delay(800);
    break;
  case 4:
    //rayo_maccquen.move_stop();
    //rayo_maccquen.turn(105);
    //delay(1000);
    //Phase++;
    delay(100);
    PhaseFour();
    break;

  case 5:

    //rayo_maccquen.move_on();
    delay(100);
    //rayo_maccquen.move_stop();
    // rayo_maccquen.move_on();
    // delay(1000);
    // rayo_maccquen.move_stop();
    //rayo_maccquen.turn(81);
    //Phase++;
    PhaseFive();
    break;
  }


}


//Detecting parking spot
int PhaseOne(){
  if (rayo_maccquen.get_ultrasonic_sensor("t03") > 15 && rayo_maccquen.get_ultrasonic_sensor("d03") > 15 && rayo_maccquen.get_ultrasonic_sensor("d01") > 15)
    {
      Phase++;
    }
  else
  {
    rayo_maccquen.move_on();
  }

    return Phase;
}

//Detecting last object to stop
int PhaseTwo(){
    if (rayo_maccquen.get_ultrasonic_sensor("t03") < 11 && rayo_maccquen.get_ultrasonic_sensor("t03") > 0)
    {
    rayo_maccquen.move_on();
    delay(800);
    rayo_maccquen.move_stop();
    delay(1000);
    rayo_maccquen.turn(103);
    delay(1000);
    rayo_maccquen.change_PWM(180);
    Phase ++;
    }
    else
    {
    rayo_maccquen.move_on();
    }
  return Phase;
}

//Backing up
int PhaseThree(){

  if (rayo_maccquen.get_ultrasonic_sensor("t02") > 1 && rayo_maccquen.get_ultrasonic_sensor("t02") <= 38)
  {
    rayo_maccquen.move_stop();
    rayo_maccquen.turn(52);
    delay(1000);
    Phase++;
  }
  else
  {
    rayo_maccquen.move_back();


  }
  return Phase;
}

int PhaseFour()
{

  if (rayo_maccquen.get_ultrasonic_sensor("t02") <= 11)
  {
    rayo_maccquen.move_stop();
    rayo_maccquen.turn(107);
    delay(1000);
    //rayo_maccquen.move_on();
    //delay(1000);
    //rayo_maccquen.move_stop();
    Phase++;
  }else{
    rayo_maccquen.move_back();
  }
  return Phase;
}

int PhaseFive()
{

  if (rayo_maccquen.get_ultrasonic_sensor("d03") <= 11)
  {
    rayo_maccquen.move_stop();
    // rayo_maccquen.move_on();
    // delay(1000);
    // rayo_maccquen.move_stop();
    rayo_maccquen.turn(81);
    Phase++;
  }
  else
  {
    rayo_maccquen.move_on();
  }
  return Phase;
}
