
#include <Stepper.h> 
#include <SoftwareSerial.h> 

const byte rxPin1 = 6; 
const byte txPin1 = 7; 
const byte rxPin2 = 4; 
const byte txPin2 = 5; 
SoftwareSerial motor1(rxPin1, txPin1); 
SoftwareSerial motor2(rxPin2, txPin2); 
String sMotor;
String sCommand;
bool sendMotor = false; 
 

const int stepsPerRevolution = 2038; 
void setup() {
  Serial.begin(9600); 
  motor1.begin(9600); 
  motor2.begin(9600); 
  motor1.write(65); 
  Serial.println("Started Master");   
}

bool GetCommand(String& sCommand, String &sMotor)
{
 
  if(!Serial.available()){
    return false; 
  }
  char sig= Serial.read();
  if(sig != '$')
   return false;
  int iMotor =0, iCommand = 0; 
  
  sCommand ="";
  sMotor = ""; 
  Serial.print("Motor: "); 
  while(iMotor< 2){
    if(Serial.available()){
      char rc = Serial.read(); 
      Serial.print(rc); 
      sMotor+= rc; 
      iMotor++; 
    }
  }
  Serial.print ("-");
  while (iCommand < 4)
  {
    if (Serial.available())
    {
      char rc= Serial.read(); 
      Serial.print(rc);
      sCommand += rc;
      iCommand++;
    } 
  }
  Serial.println(); 
 return true;
}

void ProcessMotor(String sMotor, String sCommand)
{ 
 if (sMotor == "01"){
   for(int i = 0; i < 3; i++){
       motor1.write(sCommand[i]);  
     } 
   return;
 }

 if(sMotor == "02"){
   Serial.println("writing to motor 2"); 
   motor2.print(sCommand);  
   return;
 }
}

void loop() {
 if(GetCommand(sCommand, sMotor)){
  ProcessMotor(sMotor, sCommand);
 }
}

