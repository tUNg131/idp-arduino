/*
IDP Group M206 (Michaelmas 2021)

Servo: containing functions that controll the grabber
- openGrabber: open the grabber
- closeGrabber: close the grabber
- ascendLifter: Lifting the grabber
- descendLifter: Lowering the grabber

*/

#include <Servo.h>
#include "Arduino.h"
#include "variables.h"

Servo grabberServo;  
Servo lifterServo;

namespace servos {
  int upPos = 95;
  int downPos = 20;
  int openPos = 110;
  int closePos = 20;
  int posSpeed = 1;
  
  void openGrabber(){
    for (int pos = closePos; pos <= openPos; pos += posSpeed) { 
      grabberServo.write(pos);              
        delay(30);                      
    }
  }

  void closeGrabber(){
    for (int pos = openPos; pos >= closePos; pos -= posSpeed) {
      grabberServo.write(pos);              
      delay(30);                       
    }
  }

  void ascendLifter(){
    for (int pos = downPos; pos <= upPos; pos += posSpeed) {
      lifterServo.write(pos);              
      delay(30);                       
    }
  }

  void descendLifter(){
    for (int pos = upPos; pos >= downPos; pos -= posSpeed) { 
      lifterServo.write(pos);              
      delay(30);                       
    }
  }

  void pickUp() {
    descendLifter();
    delay(1000);
    closeGrabber();
    delay(1000);
    ascendLifter();
  }

  void dropOff() {
    descendLifter();
    delay(1000);
    openGrabber();
    delay(1000);
    ascendLifter();
  }

  void begin() {
    grabberServo.attach(grabberServoPin);
    lifterServo.attach(lifterServoPin);
    lifterServo.write(upPos);
    grabberServo.write(openPos);
  }
}
