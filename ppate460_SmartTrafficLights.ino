/*

Name: Pratik Patel
Spring 2024 - EXPO on April 19, 2024
NetID: ppate460
UIN: 669224629
Partner Name: Uvaish Bakaliya
NetID: ubaka2
UIN: 657320372
TA Name: Dwij

Project: Smart Traffic Control Management
Description: 
Our project focuses on developing a Smart Traffic Control System using Arduino microcontrollers, 
aiming to optimize urban traffic management. By integrating radar sensors with traffic signals, 
the system dynamically adjusts signal timing based on vehicle presence, reducing congestion and enhancing efficiency.
This system aims to reduce traffic congestion and improve efficiency in urban transportation.
Referances: 
https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
https://projecthub.arduino.cc/stannano/one-digit-7-segment-led-display-819bcd

*/

#include "SevSeg.h"
SevSeg sevseg; 

const int buttonPin = 8;
const int redPin = 9;
const int yellowPin = 10;
const int greenPin = 11;

bool redLEDState = false;
bool greenLEDState = false;
bool buttonState = HIGH;
bool lastButtonState = HIGH;

// defines pins numbers
const int trigPin = 13;
const int echoPin = 12;
// defines variables
long duration;
int distance;

int lessThan20 = 1;

void setup() {

  // initialize the button pin as an input
  pinMode(buttonPin, INPUT_PULLUP);

  // initialize the LEDs pin as an output
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  Serial.begin(9600);        // Starts the serial communication

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

  // controls "OTHER" arduino
  while (Serial.available() > 0) {
    char receivedChar = Serial.read();

    if (receivedChar == 1) {  // Red signal ON on other arduino, perfrom this action ...

      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, LOW);

      // digitalWrite(redPin, HIGH);
      // digitalWrite(yellowPin, HIGH);
      digitalWrite(greenPin, HIGH);
      delay(5000);


      // just for testing
      // delay(200);
      // digitalWrite(greenPin, LOW);
      // delay(200);
      // digitalWrite(greenPin, HIGH);
      // delay(200);
      // digitalWrite(greenPin, LOW);

    } else if (receivedChar == 0) {

      // Now that the signal is red on the other side, we can turn on green signal here

      digitalWrite(redPin, LOW);
      // digitalWrite(yellowPin, LOW);
      // digitalWrite(greenPin, LOW);

      // digitalWrite(redPin, HIGH);
      // digitalWrite(yellowPin, HIGH);
      // digitalWrite(greenPin, HIGH);

      // delay(5000);

      // digitalWrite(redPin, LOW);
      // digitalWrite(yellowPin, LOW);
      // digitalWrite(greenPin, LOW);
    }
  }

// ----------------------------------------------------------------------------------------------------------------------------

 // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // delay(10);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // delay(10);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // NEED TO CHANGE THE CODE, ONLY WORKING ON PRATIK'S MAC
  // AT THE BEGINNING THE LIGHT SHOULD BE GREEN BECAUSE THE OTHER ARDUINO'S LIGHT IS RED.
   if (distance >= 0 ) { // the car approaches and turn green LED ON

    // digitalWrite(redPin, LOW);
    // digitalWrite(yellowPin, LOW);
    // digitalWrite(greenPin, HIGH);
    lessThan20 = !lessThan20;
    
  } else { // Otherwise keep green OFF and animate; yellow -> red

    if (lessThan20 == 10) {
  
      // digitalWrite(redPin, LOW);
      // digitalWrite(yellowPin, LOW);
      // digitalWrite(greenPin, LOW);
      // // delay(200);
      // digitalWrite(yellowPin, HIGH);
      // delay(2000);
      // digitalWrite(yellowPin, LOW);
      // delay(200);
      lessThan20 = !lessThan20;
    }
    // digitalWrite(greenPin, LOW);
    // digitalWrite(redPin, HIGH);
  }


// ----------------------------------------------------------------------------------------------------------------------------
  int val;
  int val2;

  val = digitalRead(buttonPin);
  if (val != lastButtonState) {
    delay(10);
    val2 = digitalRead(buttonPin);


    // controls "THIS" arduino
    if (val == val2) {
      buttonState = val;

      if (buttonState == LOW) {  // When the button is not pressed (also initial setup when arduino starts)

        // redLEDState = !redLEDState;

        // Serial.write(redLEDState);

        // my green signal is ON in the beginning
        digitalWrite(redPin, LOW);

        // digitalWrite(redPin, HIGH);
        // digitalWrite(yellowPin, HIGH);
        digitalWrite(greenPin, HIGH);

        greenLEDState = false;
        Serial.write(greenLEDState);  // write red or green led state depending

      } else {  // The button is pressed on "THIS" arduino

        digitalWrite(greenPin, LOW);

        delay(200);  // delay to switch the LED
        digitalWrite(yellowPin, HIGH);
        delay(2000);  // delay to keep Yellow LED ON for 2 seconds

        digitalWrite(yellowPin, LOW);
        delay(200);  // delay to switch the LED
        digitalWrite(redPin, HIGH);

        displayTime();

        redLEDState = true;
        Serial.write(redLEDState);  // write red or green led state depending
        redLEDState = !redLEDState;

        delay(6500);  // time for pedestrian to cross the road
        digitalWrite(redPin, LOW);

        // redLEDState = false;

        // Serial.write(redLEDState); // write red or green led state depending
      }
    }
  }

  lastButtonState = val;

  // // controls "OTHER" arduino
  // while (Serial.available() > 0) {
  //   char receivedChar = Serial.read();

  //   if (receivedChar == 1) { // Is the red signal ON on other arduino? then perfrom this action ...

  //     // digitalWrite(redPin, LOW);
  //     // digitalWrite(yellowPin, LOW);
  //     // digitalWrite(greenPin, LOW);

  //     // digitalWrite(redPin, HIGH);
  //     // digitalWrite(yellowPin, HIGH);
  //     // digitalWrite(greenPin, HIGH);

  //     // just for testing
  //     // delay(200);
  //     // digitalWrite(greenPin, LOW);
  //     // delay(200);
  //     // digitalWrite(greenPin, HIGH);
  //     // delay(200);
  //     // digitalWrite(greenPin, LOW);

  //   } else if (receivedChar == 0) {

  //     // Now that the signal is red on the other side, we can turn on green signal here

  //     digitalWrite(redPin, LOW);
  //     // digitalWrite(yellowPin, LOW);
  //     // digitalWrite(greenPin, LOW);

  //     // digitalWrite(redPin, HIGH);
  //     // digitalWrite(yellowPin, HIGH);
  //     // digitalWrite(greenPin, HIGH);

  //     // delay(5000);

  //     // digitalWrite(redPin, LOW);
  //     // digitalWrite(yellowPin, LOW);
  //     // digitalWrite(greenPin, LOW);

  //   }
  // }

}  // end of loop()


void displayTime() {

  for(int i = 10; i > -1; i--){
    sevseg.setNumber(i, i%2);
    delay(1000);
    sevseg.refreshDisplay(); 
  }

} // end of displayTime()

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------


#include <Servo.h>. 

const int buttonPin = 8;      
const int redPin = 9;       
const int  yellowPin = 10;
const int greenPin = 11;

bool redLEDState = false;       
bool buttonState = HIGH;     
bool lastButtonState = HIGH; 

// Defines Tirg  and Echo pins of the Ultrasonic Sensor
const int trigPin = 13;
const int echoPin  = 12;
// Variables for the duration and the distance
long duration;
int  distance;

int lessThan20 = 1;

Servo myServo; // Creates a servo object for controlling the servo motor

void setup() {å
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);         
  pinMode(yellowPin, OUTPUT);          
  pinMode(greenPin, OUTPUT);          

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
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

  // READ LED LIGHT STATE HERE OF THE OTHER ARDUINO AND THEN TURN ON GREEN HERE.

  // control "OTHER" arduino
  while (Serial.available() > 0) {
    char receivedChar = Serial.read();
   
    if (receivedChar == 1) { // This means the RED is ON on another side

      // going from red -> green
      delay(200);
      digitalWrite(redPin, LOW);
      delay(200);
      digitalWrite(greenPin, HIGH);
      delay(3000);
      digitalWrite(greenPin, LOW);
      delay(200);
      digitalWrite(yellowPin, HIGH);
      delay(2000);
      digitalWrite(yellowPin, LOW);
      delay(200);

      // digitalWrite(redPin, LOW);
      // digitalWrite(yellowPin, LOW);
      // digitalWrite(greenPin, LOW);

      // digitalWrite(redPin, HIGH);
      // digitalWrite(yellowPin, HIGH);
      // digitalWrite(greenPin, HIGH);
  
      
    } else if (receivedChar == 0) { // This means the green is ON on the other side

      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, LOW);

      digitalWrite(redPin, HIGH);

    }
  }

// ------------------------------------------------------------------------------------------------------

// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // delay(10);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // delay(10);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 15 ) { // the car approaches and turn green LED ON

    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH);
    lessThan20 = !lessThan20;
    
  } else { // Otherwise keep green OFF and animate; yellow -> red

    if (lessThan20 != 1) {
    
      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, LOW);
      // delay(200);
      digitalWrite(yellowPin, HIGH);
      delay(2000);
      digitalWrite(yellowPin, LOW);
      // delay(200);
      lessThan20 = !lessThan20;
    }
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    // lessThan20 = !lessThan20;
  }

// -------------------------------------------------------------------------------------------------------------

  int val; 
  int val2;
  
  val = digitalRead(buttonPin); 
  if (val != lastButtonState) {
    delay(10);
    val2 = digitalRead(buttonPin); 
    
    // controls "THIS" arduino
    if (val == val2) {
      buttonState = val;
    
      if (buttonState == LOW) { // when the button is not pressed (initial setup)

        // redLEDState = !redLEDState;

        // My red signal is ON in the beginning

        // digitalWrite(redPin, LOW);
        // digitalWrite(yellowPin, LOW);
        digitalWrite(greenPin, LOW);

        digitalWrite(redPin, HIGH);
        // digitalWrite(yellowPin, HIGH);
        // digitalWrite(greenPin, HIGH);

        redLEDState = true;
        Serial.write(redLEDState); // sending a signal that my red led is high

      } else { // when the button is pressed then performing this task...

        // because the signal is already red, pedestrian is good to cross the road.
        // digitalWrite(redPin, LOW);
        // delay(200);
        // digitalWrite(yellowPin, HIGH);
        // delay(2500);
        // digitalWrite(yellowPin, LOW);
        // delay(200);
        // digitalWrite(greenPin, HIGH);
        // delay(5000);

      }
    }
  }
  
  lastButtonState = val;

  // // control "OTHER" arduino
  // while (Serial.available() > 0) {
  //   char receivedChar = Serial.read();
   
  //   if (receivedChar == 1) {

  //     // digitalWrite(redPin, LOW);
  //     // digitalWrite(yellowPin, LOW);
  //     // digitalWrite(greenPin, LOW);

  //     // digitalWrite(redPin, HIGH);
  //     // digitalWrite(yellowPin, HIGH);
  //     // digitalWrite(greenPin, HIGH);
  
      
  //   } else if (receivedChar == 0) {

  //     // digitalWrite(redPin, LOW);
  //     // digitalWrite(yellowPin, LOW);
  //     // digitalWrite(greenPin, LOW);

  //     // digitalWrite(redPin, HIGH);
  //     // digitalWrite(yellowPin, HIGH);
  //     // digitalWrite(greenPin, HIGH); 

  //   }
  // }

} //end of loop

// Function for calculating the distance measured by the Ultrasonic sensor
// int calculateDistance(){ 
  
//   digitalWrite(trigPin, LOW); 
//   delayMicroseconds(2);
//   // Sets the trigPin on HIGH state for 10 micro seconds
//   digitalWrite(trigPin, HIGH); 
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
//   duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
//   distance= duration*0.034/2;
//   return distance;
// }
