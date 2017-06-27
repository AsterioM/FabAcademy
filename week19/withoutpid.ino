#include <SoftwareSerial.h>

const int rx=0;
const int tx=1;
int i=0;
char buf[12];
SoftwareSerial mySerial(rx,tx);// which analog pin to connect
float temp;

#define PIN_INPUT 7 // THERMO INPUT
#define THERMISTORPIN 7// resistance at 25 degrees C
#define THERMISTORNOMINAL 100000 // temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25 // how many samples to take and average, more takes longer but is more 'smooth'
#define NUMSAMPLES 5// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 4036// the value of the 'other' resistor
#define SERIESRESISTOR 4700    
int samples[NUMSAMPLES];

//buton
const int buttonPin = 8;     // the number of the pushbutton pin
const int RELAY_PIN = 6;
int buttonState = 0;         // variable for reading the pushbutton status

//motor                              
int dirPin = 3;                  // output pin for stepper motor direction
int stepPin = 2;                 // output pin for the pin used to step the motor for your particular motor) 


void setup(void) {
  
  pinMode(rx,INPUT);
  pinMode(tx,OUTPUT);
  mySerial.begin(4800);
 
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  pinMode(dirPin, OUTPUT);       // Assign output mode to pin for direction
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, LOW);// Assign output mode to pin for setp
  digitalWrite(dirPin, LOW);     // Initialize dir pin 
  digitalWrite(stepPin, LOW);    // Initialize step pin

   pinMode(THERMISTORPIN, INPUT); // thermo pin 
} 

void comm(void){
  //mySerial.println("funciona in loop");
  uint8_t i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(THERMISTORPIN);
   delay(10);
  }
 
  // average all the samples out
  average = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
 
  //mySerial.print("Average analog reading "); 
  //mySerial.println(average);
 
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  //mySerial.print("Thermistor resistance "); 
  //mySerial.println(average);
 
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
  temp = steinhart; 
  //mySerial.print("Temperature "); 
  mySerial.println8(steinhart);
 // mySerial.println(" *C");
 
  
  
  }

void loop(void) {
   buttonState = digitalRead(buttonPin);

  if (temp < 200) digitalWrite(RELAY_PIN, HIGH);
  else digitalWrite(RELAY_PIN, LOW);
    
   while (buttonState == LOW)
   {  buttonState = digitalRead(buttonPin);
      
      digitalWrite(stepPin, HIGH);
      digitalWrite(RELAY_PIN, HIGH);
       //comm();
        delay(1);

      digitalWrite(stepPin, LOW); 
      digitalWrite(RELAY_PIN, LOW) ;   
        delay(1);
    }
  comm();
  delay(100);
}
