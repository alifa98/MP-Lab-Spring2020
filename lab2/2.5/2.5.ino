/*
 * 
 * Code By Ali Faraji
 * Sep 4, 2020
 * ali.faraji@aut.ac.ir
 * 
 */


#include <LiquidCrystal.h>
#include <Keypad.h>
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

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad

const int rs = 20, en = 19, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

long number1, number2, resultValue, tempNumber;
char op;
boolean number1Turn = true;

boolean number1HasValue = false;
boolean number2HasValue = false;

boolean resultIsReady = false;



void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  tempNumber = 0;
}

void loop() {
  char key = kpd.getKey();
  
  if (key != NO_KEY){
    
    if(key >= '0' && key  <= '9'){
      tempNumber = tempNumber * 10 + (key - '0');
      if(number1Turn){
        number1HasValue = true;
      }else{
        number2HasValue = true;
      }
      updateLCD();
    }
    else if(key == '*' || key =='/' || key =='-' || key =='+'){
      op = key;

      if(number1Turn){
        number1 = tempNumber;
        number1Turn = false;
      }
      updateLCD();
      tempNumber = 0;
    }
    else if(key == 'C'){
      resetValues();
      updateLCD();
    }
    else if(key == '='){
      if(!(number1HasValue && number2HasValue)){
        resetValues();
        lcd.clear();
        lcd.print("Error");
      }else{
        number2 = tempNumber;
        calculate();
        updateLCD();
      }
    }
  }
}

void updateLCD(){
  
  if(resultIsReady){
    char tempString[16];
    sprintf(tempString, "= %ld", resultValue);
    lcd.clear();
    lcd.print(tempString);
    resultIsReady = false;
    
  }
  else if(number2HasValue){
          
    char tempString[16];
    sprintf(tempString, " %ld %c %ld", number1, op, tempNumber );
    lcd.clear();
    lcd.print(tempString);
  }
  else if(number1HasValue){

    if( !(op == '*' || op == '/' || op == '-' || op == '+') )
      op = ' ';
      
    char tempString[16];
    sprintf(tempString, " %ld %c", tempNumber, op );
    lcd.clear();
    lcd.print(tempString);
    
  }
}

void calculate(){
  
  if(op == '*')
    resultValue = number1 * number2;
  if(op == '-')
    resultValue = number1 - number2;
  if(op == '+')
    resultValue = number1 + number2;
  if(op == '/')
    resultValue = number1 / number2;
    
  resultIsReady = true;
  resetValues();
}

void resetValues(){
  number1 = number2 = tempNumber = 0;
  number1Turn = true;
  number1HasValue = false;
  number2HasValue = false;
  op = ' ';
  lcd.clear();
}
