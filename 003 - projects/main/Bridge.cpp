#include "Bridge.h"
#include <Arduino.h>

Bridge::Bridge(int northPin, int southPin, int tPin, int ePin, int lGreen, int lRed) {
  servoNorth.attach(northPin, 500, 2500);
  servoSouth.attach(southPin, 500, 2500);
  trigPin = tPin;
  echoPin = ePin;
  ledGreen = lGreen;
  ledRed = lRed;
}
int pos = 0, step = 3;

void Bridge::begin() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  servoNorth.write(0);
  servoSouth.write(0);
}

void Bridge::checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  if (distance < 30) {
    Serial.println("aaaaa");
    openBridge();
    delay(5000);
    closeBridge();
  }
}

void Bridge::openBridge() {
  blinkLED(ledRed, 3);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, HIGH);

  Serial.print(1);
  for (pos = 90; pos >=0 ; pos -= step) {
    servoNorth.write(pos);
    delay(200);
  }
  Serial.print(2);
  for (pos = 90; pos >=0 ; pos -= step) {
    servoSouth.write(pos);
    delay(200);
  }

}

void Bridge::closeBridge() {
  blinkLED(ledGreen, 3);

  Serial.print(3);
  for (pos = 0; pos <= 90; pos += step) {
    servoNorth.write(pos);
    delay(200);
  } 
  
  Serial.print(4);
  for (pos = 0; pos <= 90; pos += step) {
    servoSouth.write(pos);
    delay(200);
  }

  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, HIGH);
}

void Bridge::blinkLED(int pin, int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
    delay(500);
  }
}
