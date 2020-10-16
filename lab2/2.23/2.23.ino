#include <LiquidCrystal.h>

String text = "Ali Faraji";

const int rs = 20, en = 19, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(text);

  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    
    lcd.scrollDisplayRight();
 
    delay(150);
  }

  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(text);

  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    
    lcd.scrollDisplayRight();
 
    delay(150);
  }
  
  delay(1000);

}
