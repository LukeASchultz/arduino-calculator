#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define I2C_ADDR 0x27  // Define I2C Address for controller
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

#define LED_OFF 0
#define LED_ON 1
LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin, BACKLIGHT_PIN, POSITIVE);

const int buttonPin = A0; // the number of the pushbutton pin

int pin0[] = {0, 1, 2, 3, 4};
int pin1[] = {0, 1, 2, 3, 4};
int pin2[] = {0, 1, 2, 3, 4};
int pin3[] = {0, 1, 2, 3, 4};

int pin0Range[] = {[75, 100], [480, 550], [750, 830], [35, 55], [160, 280]}
 
const int BUTTON1LOW = 75;
const int BUTTON1HIGH = 100;
const int BUTTON2LOW = 480;
const int BUTTON2HIGH = 550;
const int BUTTON3LOW = 750;
const int BUTTON3HIGH = 830;
const int BUTTON4LOW = 35;
const int BUTTON4HIGH = 55;
const int BUTTON5LOW = 160;
const int BUTTON5HIGH = 280;
 
// Variables will change:
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

String topLine = "";
String bottomLine = "";
bool buttonDown = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(13, INPUT);
  lcd.begin (16,2);  // initialize the lcd
  Serial.begin(9600);
}

void loop() {
  lcd.backlight();  
  lcd.setCursor(0,0); 
  lcd.print(topLine);
  lcd.setCursor(0, 1);
  lcd.print(bottomLine);
  
  // read the state of the switch into a local variable:
  int reading = analogRead(buttonPin);
  Serial.println(digitalRead(13));
   
  int tmpButtonState = LOW; // the current reading from the input pin


   
  if (reading > BUTTON5LOW && reading < BUTTON5HIGH && !buttonDown) {
    //Read switch 5
    tmpButtonState = BUTTON5;
  } else if (reading > BUTTON4LOW && reading < BUTTON4HIGH && !buttonDown) {
    //Read switch 4
    tmpButtonState = BUTTON4;
  } else if (reading > BUTTON3LOW && reading < BUTTON3HIGH && !buttonDown) {
    //Read switch 3
    tmpButtonState = BUTTON3;
  } else if (reading > BUTTON2LOW && reading < BUTTON2HIGH && !buttonDown) {
    //Read switch 2
    tmpButtonState = BUTTON2;
  } else if (reading > BUTTON1LOW && reading < BUTTON1HIGH && !buttonDown) {
    //Read switch 1
    tmpButtonState = BUTTON1;
  } else {
    //No button is pressed;
    tmpButtonState = LOW;
    buttonDown = false;
  }

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to a buttonState),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (tmpButtonState != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    buttonState = tmpButtonState;
    //Serial.println(buttonState);
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = tmpButtonState;
   
  // set the LED using the state of the button for testing:
  switch(buttonState){
    case BUTTON1:
      if (!buttonDown) {
        if (topLine.length() < 16) {
          topLine += "1";
        } else if (bottomLine.length() < 16) {
          bottomLine += "1";
        }
        
        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
    case BUTTON2:
      if (!buttonDown) {
        topLine = "";
        bottomLine = "";
        lcd.clear();
        buttonDown = true;
        buttonState = LOW;

        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
    case BUTTON3:
      if (!buttonDown) {
        if (topLine.length() < 16) {
          topLine += "3";
        } else if (bottomLine.length() < 16) {
          bottomLine += "3";
        }

        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
    case BUTTON4:
      if (!buttonDown) {
        if (topLine.length() < 16) {
          topLine += "4";
        } else if (bottomLine.length() < 16) {
          bottomLine += "4";
        }

        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
    case BUTTON5:
      if (!buttonDown) {
        if (topLine.length() < 16) {
          topLine += "5";
        } else if (bottomLine.length() < 16) {
          bottomLine += "5";
        }

        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
  } 
}


