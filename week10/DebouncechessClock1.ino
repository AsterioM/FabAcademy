
#include <LiquidCrystal.h>
LiquidCrystal lcd (7, 8, 9, 10, 11, 12);


int aWhite = 9;
int bWhite = 5;
int cWhite = 9;
//int dWhite = 9;
long nWhite = 0;

int aBlack = 9;
int bBlack = 5;
int cBlack = 9;
//int dBlack = 9;
long nBlack = 0;
// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
  lcd.begin(16,2);
  lcd.print("  White  Black");
  lcd.setCursor(3,1);
  lcd.print(":");
  //lcd.setCursor(5,1);
  //lcd.print(":");
  lcd.setCursor(11,1);
  lcd.print(":");
  //lcd.setCursor(13,1);
  //lcd.print(":");
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);
  if(ledState){
    printWhite(); 
  }
  else{
    printBlack();
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
} // end loop

void printWhite(){
  lcd.setCursor(2,1);
  lcd.print(aWhite);
  lcd.setCursor(4,1);
  lcd.print(bWhite);
  lcd.setCursor(5,1);
  lcd.print(cWhite);
  //lcd.setCursor(7,1);
  //lcd.print(dWhite); 
  nWhite = millis();
  if(nWhite % 500 == 0){
    cWhite--;
    //dWhite--;
    //if(dWhite == 0){
    //  dWhite = 9;
    //  cWhite--;
   }
   if(cWhite <= -1){
     cWhite = 9;
     bWhite--;
   }
   if(bWhite <= -1){
     bWhite = 5;
     aWhite--;
   }
   if(aWhite <= -1){
     aWhite = 9;
   }
 } // end printWait
  
void printBlack(){
  lcd.setCursor(10,1);
  lcd.print(aBlack);
  lcd.setCursor(12,1);
  lcd.print(bBlack);
  lcd.setCursor(13,1);
  lcd.print(cBlack);
  //lcd.setCursor(15,1);
  //lcd.print(dBlack); 
  nBlack = millis();
  if(nBlack % 1000 == 0){
    cBlack--;
    //dBlack--;
    //if(dBlack == 0){
    //dBlack = 9;
    //cBlack--;
    }
   if(cBlack <= -1){
     cBlack = 9;
     bBlack--;
   }
   if(bBlack <= -1){
     bBlack = 5;
     aBlack--;
   }
   if(aBlack <= -1){
     aBlack = 9;
   }
 }//end printBlank
  

