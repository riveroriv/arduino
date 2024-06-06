#include <Servo.h>

int pos = 0;

Servo servo_9, servo_10;

const int trigPin = 4;
const int echoPin = 5;
const int led = 2;

long duration;
int distanceCm, distanceInch;

void setup() {
  Serial.begin(9600);
  servo_9.attach(9, 500, 2500);
  servo_10.attach(10, 500, 2500);
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;
  Serial.print(duration);
  Serial.print(" -- ");
  Serial.println(distanceCm);
  if (distanceCm < 20) {
    digitalWrite(led, HIGH);
  Serial.print(2);
  for (pos = 90; pos >=0 ; pos -= 3) {
    servo_10.write(pos);
    delay(200);
  }
    Serial.print(1);
  for (pos = 90; pos >=15 ; pos -= 3) {
    servo_9.write(pos);
    delay(200);
  }
  
  Serial.print(4);
  for (pos = 0; pos <= 90; pos += 3) {
    servo_10.write(pos);
    delay(200);
  }
  Serial.print(3);
  for (pos = 15; pos <= 90; pos += 3) {
    servo_9.write(pos);
    delay(200);
  } 
  
  delay(2000);
  } else {
    digitalWrite(led, LOW);
  }
  delay(100);
}