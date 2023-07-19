#include "Smallmotor.h"
#include <Stepper.h> 
#include <SoftwareSerial.h> 

const byte rxPin = 6; 
const byte txPin = 7; 
// SoftwareSerial slave1(rxPin, txPin); 
String sMotor;
String sCommand;
bool bStep = false;
bool bDelayStop;
unsigned long int delayMS = 10;
//Creating Smallmotor object to invoke function calls 
Motorbase* motor1 = NULL; 
 

const int stepsPerRevolution = 2038; 
void setup() {
  Serial.begin(9600); 
  Serial.println("Started slave 1"); 
  motor1 = new Smallmotor();
  motor1->initialize(2038, 8, 9, 10, 11); 
   Serial.println("Motor initialized successfully"); 
  // slave1.begin(9600); 
  motor1->speedSet(8); 
  motor1->step();
}

bool GetCommand(String& sCommand)
{
 
  if(!Serial.available()){
    return false; 
  }
  char sig= Serial.read();
  if(sig != '$')
   return false;
  int iCount =0;
  
  sCommand ="";
  while (iCount < 3)
  {
    if (Serial.available())
    {
      char rc= Serial.read();
      Serial.print (" - "); 
      Serial.println(rc);
      sCommand += rc;
      iCount++;
    } 
  }
 return true;
}

void ProcessCommand(String sCommand, bool& bStep)
{
  bool bDelayStop = false;
  int delayMS = 0;
  if(sCommand == "000")
 {
   bStep = false;
   return;
 }

 if (sCommand == "001")
 {
   bStep=true;
   motor1->setDirection(1);
  //  direction = 1; 
   return;
 }

 if(sCommand == "002")
 {
   bStep=true;
   motor1->setDirection(-1);
  //  direction = -1; 
   return;
 }

 if(sCommand == "003")
 {

   motor1->speedSet(5);
   return;
 }


 if(sCommand == "004")
 {

   motor1->speedSet(8);
   return;
 }
 if(sCommand == "005")
 {

   motor1->speedSet(10);
   return;
 }

 if(sCommand == "006")
 {
   bDelayStop = true;
   delayMS = 1000;
   bStep = false; 
   return; 
 }
 if(sCommand == "007")
 {
   Serial.println("7 command working");
   bDelayStop = true;
   motor1->delayMotor(3000); 
   motor1->stop(); 
   bStep = false;   
   return; 
 }
 if(sCommand == "008")
 {
   bDelayStop = true;
   delayMS = 5000;
   motor1->delayMotor(delayMS); 
  //  motor1->stop(); 
   bStep = false; 
   return; 
  //  bStep = false; 
 }




}
void loop() {
// Serial.println("starting"); 
 if(GetCommand(sCommand)){
  ProcessCommand(sCommand,bStep);
 }
 if(bStep)
 {
   motor1->step();
 }


}
