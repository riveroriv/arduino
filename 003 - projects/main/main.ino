#include <Arduino.h>
#include "Bridge.h"

const int servoNorthPin = 9;
const int servoSouthPin = 10;
const int trigPin = 2;
const int echoPin = 3;
const int ledGreenPin = 4;
const int ledRedPin = 5;

Bridge bridge(servoNorthPin, servoSouthPin, trigPin, echoPin, ledGreenPin, ledRedPin);

void setup() {
  Serial.begin(9600);
  bridge.begin();
}

void loop() {
  bridge.checkDistance();
  delay(500);
}
