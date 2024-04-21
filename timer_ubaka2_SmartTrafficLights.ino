
#include "SevSeg.h"
SevSeg sevseg; 

const int buttonPin = 8;  // the pin that the pushbutton is attached to
const int redLEDPin = 9;      // the pin that the LED is attached to
const int yellowLEDPin = 10;      // the pin that the LED is attached to
const int greenLEDPin = 11;      // the pin that the LED is attached to

const int trigPin = 13;
const int echoPin = 12;

int buttonState = 0;       // current state of the button
int lastButtonState = 0;   // previous state of the button
int ledState = HIGH;        // current state of the LED

long duration;
int distance;

void setup() {

  // initialize the LEDs pin as an output
  pinMode(redLEDPin, OUTPUT);    
  pinMode(yellowLEDPin, OUTPUT);  
  pinMode(greenLEDPin, OUTPUT);  

  // initialize the button pin as an input
  pinMode(buttonPin, INPUT);   

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600);  // initialize serial communication

  byte numDigits = 1;
  byte digitPins[] = {};
  //                    A, B, C,  D, E, F, G, DP(light)  
  byte segmentPins[] = {5, 4, A5, 2, 3, 6, 7, A4};
  bool resistorsOnSegments = true;

  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

}

void loop() {
  buttonState = digitalRead(buttonPin);  // read the state of the button

  digitalWrite(greenLEDPin, HIGH);
  // if the button state has changed
  // if (buttonState != lastButtonState) {

    if (buttonState == 1) {  // if the button is pressed

      // send the new LED state to the other Arduino via serial communication
      // Serial.print("LED State: ");
      // Serial.println(ledState);

      pedestrianCrossing();

      // digitalWrite(redLEDPin, ledState);  // Update the LED state
      // delay(2000);
      // digitalWrite(redLEDPin, !ledState);  // Update the LED state
      
    }
    buttonState = !buttonState;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  delay(100);  // debounce delay
}

void pedestrianCrossing() {

  delay(1000);
  digitalWrite(greenLEDPin, LOW);
  delay(500);
  digitalWrite(yellowLEDPin, HIGH);
  delay(3000);
  digitalWrite(yellowLEDPin, LOW);
  delay(500);
  digitalWrite(redLEDPin, HIGH);
  displayTime();    // have 10 seconds to cross the road
  delay(1000);
  digitalWrite(redLEDPin, LOW);
  delay(400);
  digitalWrite(redLEDPin, HIGH);
  delay(400);
  digitalWrite(redLEDPin, LOW);
  delay(400);
  digitalWrite(redLEDPin, HIGH);
  delay(400);
  digitalWrite(redLEDPin, LOW);
  digitalWrite(greenLEDPin, HIGH);

} // end of pedestrianCrossing()

void displayTime() {

  for(int i = 10; i > -1; i--){
    sevseg.setNumber(i, i%2);
    delay(1000);
    sevseg.refreshDisplay(); 
  }

} // end of displayTime()


// ---------------------------------------------------------------------------------------------
