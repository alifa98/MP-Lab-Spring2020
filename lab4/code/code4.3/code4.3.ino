#include <Servo.h>

Servo myservo;

int potpin = 0;

int tempNumber = 0;

void setup() {
  myservo.attach(6);
  Serial3.begin(9600);
}

void loop() {

  if(Serial3.available() > 0){
    int incomingByte = Serial3.read();
  
    if(incomingByte >= '0' && incomingByte  <= '9'){
      tempNumber = tempNumber * 10 + (incomingByte - '0');
    }
    else if(incomingByte == ' '){
      if(tempNumber >= 0 && tempNumber <= 180){
        myservo.write(tempNumber);
        Serial3.print("Servo Setted On: ");
        Serial3.println(tempNumber, DEC);
      }else{
        Serial3.print("Invalid Value");
      }
        tempNumber = 0;   
    }
  }
}
