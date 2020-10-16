#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'C','0','=','+'}

};

byte rowPins[ROWS] = { 22, 23, 24, 25 };
byte colPins[COLS] = { 26, 27, 28, 29 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad


const int rs = 20, en = 19, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int servoMotorPin = 13;
Servo myservo;

int tempNumber = 0;

void setup() {
   lcd.begin(16, 2);
  myservo.attach(servoMotorPin);
}

void loop() {
  char key = keypad.getKey();
  
  if (key != NO_KEY){
    if(key >= '0' && key  <= '9'){
      tempNumber = tempNumber * 10 + (key - '0');
    }
    else if(key == '='){
      if(tempNumber >= 0 && tempNumber <= 180){
        myservo.write(tempNumber);
      }
      tempNumber = 0;
      lcd.clear();
      lcd.setCursor(0,0);
    }
    lcd.print(key);
  }
}
