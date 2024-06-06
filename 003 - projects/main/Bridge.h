#ifndef BRIDGE_H
#define BRIDGE_H

#include <Servo.h>

class Bridge {
  private:
    Servo servoNorth;
    Servo servoSouth;
    int trigPin;
    int echoPin;
    int ledGreen;
    int ledRed;
    long duration;
    int distance;
    
  public:
    Bridge(int northPin, int southPin, int trigPin, int echoPin, int ledGreen, int ledRed);
    void begin();
    void checkDistance();
    void openBridge();
    void closeBridge();
    void blinkLED(int pin, int times);
};

#endif
