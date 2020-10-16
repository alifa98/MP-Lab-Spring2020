#include <Servo.h>

Servo myservo;

int potpin = 0;

void setup() {
  myservo.attach(6);
}

void loop() {
  int value = analogRead(potpin);
  value = map(value, 0, 1023, 0, 180);
  myservo.write(value);
  delay(15);
}
