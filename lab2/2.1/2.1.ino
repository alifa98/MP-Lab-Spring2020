#include <LiquidCrystal.h>

const int rs = 20, en = 19, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Ali Faraji");
}

void loop() {
  lcd.setCursor(0, 1);
  
  lcd.print("Hi World!");
}
