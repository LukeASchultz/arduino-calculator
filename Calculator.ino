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

int pins[] = {A0, A1, A2, A3};

int pin0[] = {0, 1, 2, 3, 4};
int pin1[] = {0, 1, 2, 3, 4};
int pin2[] = {0, 1, 2, 3, 4};
int pin3[] = {0, 1, 2, 3, 4};

int buttons[4][5] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}};

int pin0Range[5][2] = {{5, 100}, {480, 550}, {750, 830}, {35, 55}, {160, 280}};
int pin1Range[5][2] = {{5, 100}, {480, 550}, {750, 830}, {35, 55}, {160, 280}};
int pin2Range[5][2] = {{5, 100}, {480, 550}, {750, 830}, {35, 55}, {160, 280}};
int pin3Range[5][2] = {{5, 100}, {480, 550}, {750, 830}, {35, 55}, {160, 280}};

int pinRanges[4][5][2] = {{{90, 130}, {550, 610}, {750, 830}, {35, 55}, {160, 280}}, {{60, 110}, {480, 550}, {750, 830}, {35, 55}, {160, 280}}, {{5, 100}, {480, 550}, {750, 830}, {35, 55}, {160, 280}}, {{5, 100}, {480, 550}, {750, 830}, {35, 55}, {160, 280}}};
 
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
  for (int i = 0; i < 4; i++) {
    pinMode(i, INPUT); 
  }
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
  int reading0 = analogRead(pins[0]);
  int reading1 = analogRead(pins[1]);
  int reading2 = analogRead(pins[2]);
  int reading3 = analogRead(pins[3]);
  //Serial.println(reading[0]);
   
  int tmpButtonState = LOW; // the current reading from the input pin

  for (int j = 0; j < 4; j++) {
    if (reading0 > pinRanges[j][4][0] && reading0 < pinRanges[j][4][1] && !buttonDown) {
      //Read switch 5
      tmpButtonState = buttons[j][4];
    } else if (reading0 > pinRanges[j][3][0] && reading0 < pinRanges[j][3][1] && !buttonDown) {
      //Read switch 4
      tmpButtonState = buttons[j][3];
    } else if (reading0 > pinRanges[j][2][0] && reading0 < pinRanges[j][2][1] && !buttonDown) {
      //Read switch 3
      tmpButtonState = buttons[j][2];
    } else if (reading0 > pinRanges[j][1][0] && reading0 < pinRanges[j][1][1] && !buttonDown) {
      //Read switch 2
      tmpButtonState = buttons[j][1];
    } else if (reading0 > pinRanges[j][0][0] && reading0 < pinRanges[j][0][1] && !buttonDown) {
      //Read switch 1
      tmpButtonState = buttons[j][0];
    } else {
      //No button is pressed;
      tmpButtonState = LOW;
      buttonDown = false;
    }
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
    Serial.println(buttonState);
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = tmpButtonState;
   
  // set the LED using the state of the button for testing:
  switch(buttonState){
    case 1:
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
    case 2:
      if (!buttonDown) {
        topLine = "";
        bottomLine = "";
        lcd.clear();
        buttonDown = true;
        buttonState = LOW;
        Serial.print("Yes");

        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
    case 3:
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
    case 4:
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
    case 5:
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
    case 6:
      if (!buttonDown) {
        if (topLine.length() < 16) {
          topLine += "6";
        } else if (bottomLine.length() < 16) {
          bottomLine += "6";
        }

        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
    case 7:
      if (!buttonDown) {
        if (topLine.length() < 16) {
          topLine += "7";
        } else if (bottomLine.length() < 16) {
          bottomLine += "7";
        }

        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
    case 8:
      if (!buttonDown) {
        if (topLine.length() < 16) {
          topLine += "8";
        } else if (bottomLine.length() < 16) {
          bottomLine += "8";
        }

        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
    case 9:
      if (!buttonDown) {
        if (topLine.length() < 16) {
          topLine += "9";
        } else if (bottomLine.length() < 16) {
          bottomLine += "9";
        }

        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
    case 10:
      if (!buttonDown) {
        if (topLine.length() < 16) {
          topLine += "10";
        } else if (bottomLine.length() < 16) {
          bottomLine += "10";
        }

        if (digitalRead(13) == HIGH) {
          buttonDown = true;
        }
      }
    break;
  } 
}


