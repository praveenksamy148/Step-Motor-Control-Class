#include "Smallmotor.h"
#include <Stepper.h> 
#include <SoftwareSerial.h> 


const byte rxPin1 = 6; 
const byte txPin1 = 7; 

//Arduino COM 5 
SoftwareSerial mySerial(rxPin1, txPin1); 

String sCommand;
bool bStep = false;
bool bDelayStop;
unsigned long int delayMS = 10;
//Creating Smallmotor object to invoke function calls 
Motorbase* motor1 = NULL; 
 

const int stepsPerRevolution = 2038; 
void setup() {
  Serial.begin(9600); 
  mySerial.begin(9600); 
  Serial.println("Started motor 1"); 
  motor1 = new Smallmotor();
  motor1->initialize(2038, 8, 9, 10, 11); 
  Serial.println("Motor initialized successfully");  
  motor1->speedSet(8); 
  motor1->step();
  Serial.print("reading character: "); 
  while(true){
    if(mySerial.available()){
      Serial.println(mySerial.read());
      break; 
    }    
  }
}

bool GetCommand(String& sCommand)
{
  if(!mySerial.available()){
    // Serial.println("not available"); 
    return false; 
  }
  int iCommand =0; 
  sCommand ="";
  // Serial.println("going to read"); 
  while (iCommand < 3)
  {
    // Serial.println("reading string"); 
    if (mySerial.available())
    {
      char rc= mySerial.read();
      // Serial.print (" - "); 
      // Serial.println(rc);
      sCommand += rc;
      iCommand++;
    } 
  }
  Serial.println(sCommand); 
 return true;
}

void ProcessCommand(String sCommand, bool& bStep)
{
  bool bDelayStop = false;
  int delayMS = 0;
  Serial.println(sCommand); 
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
   Serial.println("6 command working");
   bDelayStop = true;
   motor1->delayMotor(1000); 
   motor1->stop(); 
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
   bStep = false; 
   return; 
 }




}
void loop() {

 if(GetCommand(sCommand)){
  ProcessCommand(sCommand,bStep);
 }
 if(bStep)
 {
   motor1->step();
 }


}
