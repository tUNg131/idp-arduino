/*
IDP Group M206 (Michaelmas 2021)

Indicator: containing functions controlling the LEDs
- indicate: indicates the type of dummy using LEDs (red & green LEDs)
- moving: indicates the robot is moving (amber LED)
- stopped: stops indicating the robot is moving (amber LED)

*/

#ifndef INDICATOR_H
#define INDICATOR_H

#include "Arduino.h"
#include "variables.h"

namespace indicator {
  void indicate(byte flag) {
    switch (flag) {
      case WHITE_DUMMY:
        digitalWrite(redLEDPin, HIGH);
        digitalWrite(greenLEDPin, HIGH);
        break;
      case RED_DUMMY:
        digitalWrite(redLEDPin, HIGH);
        digitalWrite(greenLEDPin, LOW);
        break;
      case BLUE_DUMMY:
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, HIGH);
        break;
      case NO_DUMMY:
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, LOW);
        break;
    }
  }

  void moving() {
    digitalWrite(amberLEDPin, HIGH);
  }

  void stopped() {
    digitalWrite(amberLEDPin, LOW);
  }

  void begin() {
    Serial.println("Initializing Indicators... ");
    pinMode(amberLEDPin, OUTPUT);
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);
  }
  
}

#endif
