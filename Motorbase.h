#ifndef Motorbase_h 
#define Motorbase_h 

#include "Arduino.h"

class Motorbase{
  public: 
  virtual void initialize(const int stepsPerRevolution, int p1, int p2, int p3, int p4) = 0; 
  virtual void speedSet(int speed) = 0; 
  virtual void setDirection(int direction) = 0; 
  virtual void stop() = 0; 
  virtual void step() = 0; 
  virtual void delayMotor(unsigned long int delayMS) = 0; 
}; 

#endif Motorbase_h 