#include <Servo.h>

Servo myservo;
int servoPosition = 0;

void setup() {
  myservo.attach(6);
}

void loop() {
  for (servoPosition = 0; servoPosition <= 180; servoPosition += 1) {
    myservo.write(servoPosition);
    delay(15);
  }
  for (servoPosition = 180; servoPosition >= 0; servoPosition -= 1) { 
    myservo.write(servoPosition);
    delay(15);
  }
}
