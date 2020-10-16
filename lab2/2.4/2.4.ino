#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'*','0','#','+'}

};

byte rowPins[ROWS] = { 22, 23, 24, 25 };
byte colPins[COLS] = { 26, 27, 28, 29 };

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad

const int rs = 20, en = 19, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String password = "1288";
void setup() {
  lcd.begin(16, 2);
}  
void loop(){

  lcd.clear();
  lcd.setCursor(0,0);
  String entredPass = "";
  
  for(int count = 0; count < 4; ++count ){
    char key = keypad.waitForKey();
    lcd.print(key);
    entredPass.concat(key);
  }

   if(keypad.waitForKey() == '*'){
      lcd.clear();
      if(password.equals(entredPass)){
        lcd.print("Correct Password");
      }else{
        lcd.print("Wrong Password");
      }
      delay(10000);
  }
}
