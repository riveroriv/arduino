#include <Servo.h>

const int ULTRA_TRIGGER = 9;
const int ULTRA_ECHO = 10;
const int LED_RED = 3;
const int LED_GREEN = 6;
const int SERVO_NORTH_PIN = 7;

Servo SERVO_NORTH;

long duration;
int distance, near, far, pos = 0,
    OPEN_DISTANCE = 15, OPEN_NEAR = 10, CLOSE_FAR = 4;
bool  open = false; 

void setup() {
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(ULTRA_TRIGGER, OUTPUT);
  pinMode(ULTRA_ECHO, INPUT);
  pinMode(ULTRA_ECHO, INPUT);
  SERVO_NORTH.attach(SERVO_NORTH_PIN, 500, 2500);
}

void loop() {  
  
  digitalWrite(ULTRA_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_TRIGGER, LOW);
  duration = pulseIn(ULTRA_ECHO, HIGH);
  distance = duration * 0.034 / 2;
  distance = duration * 0.0133 / 2;
  Serial.println(distance);
  if (distance < 10) {
    digitalWrite(LED_RED, HIGH);
    near+=1;
    
  digitalWrite(LED_GREEN, LOW);
  } else {
    digitalWrite(LED_RED, LOW);
    far+=1;
    if (far > CLOSE_FAR) {
      far = 0;
      near = 0;
    }
    
  digitalWrite(LED_GREEN, HIGH);
  }
  Serial.println((String)"Cerca "+near+" - Lejos "+far);
  if (near > OPEN_NEAR) {
    for (pos = 0; pos <= 90; pos += 5) {
    SERVO_NORTH.write(pos);
    delay(100);
    }
      delay(4000);
  for (pos = 90; pos >= 0; pos -= 5) {
    SERVO_NORTH.write(pos);
    delay(100);
  }
  open = true;
  near = 0;
  }


  delay(500);
}