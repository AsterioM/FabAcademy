
#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 2); // RX, TX

int sensorPin = A3;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor


void setup() {

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);

}

void loop() { // run over and over
  sensorValue = analogRead(sensorPin);
  mySerial.print(sensorValue, DEC);
  mySerial.print("\n");
}

