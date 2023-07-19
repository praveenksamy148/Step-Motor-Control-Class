#ifndef Smallmotor_h 
#define Smallmotor_h 

#include "Arduino.h"
#include "Motorbase.h" 
#include <Stepper.h> 
#include "time.h"

class Smallmotor: public Motorbase{
  private: 
  Stepper* myStepper = NULL; 
  int m_direction = -1;
  public: 
  
  void initialize(const int stepsPerRevolution, int p1, int p2, int p3, int p4){
    Serial.println("initializing"); 
    myStepper = new Stepper(stepsPerRevolution, p1, p2, p3, p4); 
   Serial.println("initialized"); 
  } 
  void speedSet(int speed){
    myStepper->setSpeed(speed); 
    
  }
  void setDirection(int direction){
    this->m_direction = direction;
  } 
  void stop(){
    myStepper->step(0); 
  }
  void step()
  {
    Serial.print("direction - ");
    Serial.println(m_direction);
    myStepper->step(this->m_direction * 100);
  }
  void delayMotor(unsigned long int delayMS){
    unsigned long int secs = millis(); 
    myStepper->step(this->m_direction * 100); 
    while(millis() <= delayMS + secs){
      myStepper->step(this->m_direction * 100); 
      Serial.println(millis());   
      myStepper->step(this->m_direction * 100); 
    }
  }
}; 

#endif Smallmotor_h