#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}

};
byte rowPins[ROWS] = { 22, 23, 24, 25 };
byte colPins[COLS] = { 26, 27, 28 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad


const int rs = 20, en = 19, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);

const int servoMotorPin = 13;
const int servoMotorLockValue = 180;
const int servoMotorOpenValue = 0;
Servo servoMotor;

const int buzzerPin = 53;
const int buzzerFrequence = 1000;

int redLedPin = 11;
int greenLedPin = 12;

int pinCode; // holds pin code
int lockPeriod; // timer for lock door periodicly

//temp variables to hold temporary runtime values
int tempInput = 0; // hold input
int counter = 0; // counter for lock period
boolean isSetting = false; // when setting mod starts this be changed to true
boolean isOpen = false; // shows door is open or not
unsigned long lastCpuTime; // holds last cpu uptime for calculate passed time.
char message[16*4] = ""; //this message shows on screen always
boolean isDirtyLCD = true; //when this is true, updateLcd func redraw lcd.
boolean wasWrong = false; //if password entered wrong this flash shows that.
boolean step1InSetting = false; // step 1 means step of entring value.
boolean step2InSetting = false; // step 2 means step of entring confirmation password to finilize setting.
int temporarySettingValue = 0;
int settingThread = 0; // 1 for changeing pinCode, 2 for changing timer,3 for lock


void setup() {
  pinCode = 1234; //default pin code
  lockPeriod = 5;   //default is 10 second

  
  lcd.begin(16, 4);
  
  servoMotor.attach(servoMotorPin);
  
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  
  counter = lockPeriod;
  lastCpuTime = millis ();
  closeDoor();
  
  lcd.setCursor(0,0);
  lcd.print("Welcome");
  delay(1000);
  lcd.clear();
}

void loop() {
  char pressedKey = keypad.getKey();
  if (pressedKey != NO_KEY){
    switch(pressedKey){
      case '*':
        submit();
        break;
      case '#':
        cancelOrMenu();
        break;
      default:
        captureInputToTempInput(pressedKey);
        break;
    }
    isDirtyLCD = true;
  }
  updateCounter();
  updateScreen();
}

void captureInputToTempInput(char key){
  if(key >= '0' && key  <= '9'){
      tempInput = tempInput * 10 + (key - '0');
    }
}

void submit(){
  if(! isSetting){
    if(tempInput == pinCode){
      openDoor();
    }else{
      wasWrong = true;
    }
  }else{
    if(step1InSetting){
      temporarySettingValue = tempInput;
      tempInput=0;
      step1InSetting = false;
      step2InSetting = true;
      
    }else if(step2InSetting){
      if(tempInput == pinCode){
        step2InSetting = false;
        if(settingThread == 1){
          // change password
          pinCode = temporarySettingValue;
        }else if(settingThread == 2){
          //change timer
          lockPeriod = temporarySettingValue;
        }
        cancelOrMenu();
      }else{
        tempInput = 0;
        wasWrong = true;
      }
    }else{
      // setting menu but no step 1 and no step 2
      settingThread = tempInput;
      temporarySettingValue=0;
      tempInput=0;
      if(settingThread == 3){
        cancelOrMenu();
        closeDoor();
      }else if(settingThread == 1 || settingThread == 2){
        step1InSetting = true;
      }else{
        cancelOrMenu();
      }
    }
  }
}

void cancelOrMenu(){
  resetInputBuffer();
  isSetting = !isSetting; //toggle state (view "if" on this var in updateLCD )
}

void beep(){
  tone(buzzerPin, buzzerFrequence);
  delay(500);
  noTone(buzzerPin);
}
void resetInputBuffer(){
  tempInput = 0;
  temporarySettingValue=0;
  settingThread=0;
}

void openDoor(){
  beep();
  turnGreenLedOn();
  turnRedLedOff();
  servoMotor.write(servoMotorOpenValue);
  isOpen = true;
  restartCounter();
}

void closeDoor(){
  beep();
  turnRedLedOn();
  turnGreenLedOff();
  servoMotor.write(servoMotorLockValue);
  isOpen = false;
}

void turnGreenLedOn(){
  digitalWrite(greenLedPin, HIGH); 
}
void turnGreenLedOff(){
  digitalWrite(greenLedPin, LOW); 
}
void turnRedLedOn(){
  digitalWrite(redLedPin, HIGH); 
}
void turnRedLedOff(){
  digitalWrite(redLedPin, LOW); 
}

void restartCounter(){
  lastCpuTime = millis();
  counter = lockPeriod;
}
void updateCounter(){
  if(millis() - lastCpuTime >= 1000){
    if(counter > 0){
      counter--;
    }else{
      // count down ended:
      counter = lockPeriod;
      if(isOpen){
        closeDoor();
      }
    }
    lastCpuTime = millis();
    isDirtyLCD = true;
  }
}

void updateScreen(){
  if(isDirtyLCD){
    lcd.clear();
    lcd.setCursor(0,0);
    if(!isSetting){
      if(isOpen){
        sprintf(message, "Correct-OPEN for %d s", counter);
      }else{
        if(wasWrong){
          wasWrong = false;
          sprintf(message, "Wrong Pass.");
        }else{
          sprintf(message, "Closed");
        }
      }
    }else{
     if(wasWrong){
        wasWrong = false;
        sprintf(message, "Wrong Pass.");
     }else if(step1InSetting){
        sprintf(message, "Enter Value. press *");
     }else if(step2InSetting){
        sprintf(message, "Enter pass. press *");
     }else{
        sprintf(message, "1=CP,2=CT,3=L?%d",tempInput);
     }
    }
    lcd.print(message);
    isDirtyLCD = false;
  }
}
