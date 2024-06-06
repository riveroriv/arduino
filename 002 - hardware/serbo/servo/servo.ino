#include <Servo.h>

int pos = 0;

Servo servo_9;

void setup()
{
  Serial.begin(9600);
  servo_9.attach(10, 500, 2500);
}

void loop()
{
  // for (pos = 180; pos >=0 ; pos -= 10) {
  //   servo_9.write(pos);
  //   delay(100);
  // }
  
  // for (pos = 0; pos <= 180; pos += 10) {
  //   servo_9.write(pos);
  //   delay(100);
  // }
  servo_9.write(0);
  delay(2000);
  servo_9.write(180);
  delay(2000);
}