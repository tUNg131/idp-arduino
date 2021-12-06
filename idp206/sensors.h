/*
IDP Group M206 (Michaelmas 2021)

Sensors: containing functions that reads data from sensors
- getDistanceUltraSonic: returns the distance got from Ultrasonic sensor
- findDummy: returns the type of dummy in front of the robot
- getLightValues: returns reading from 4 line sensors

*/

#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"
#include "variables.h"
#include <SharpIR.h>

// IR Distance
SharpIR IRDistanceSensor = SharpIR(IRDistancePin, IRDistanceSensorModel);

namespace sensors {
  int analogReadAverage(int pin, int times = 3) {
    int sum = 0;
    for (int i=0; i<times; i++) {
      sum += analogRead(pin);
    }
    return sum / times;
  }

  int getDistanceUltraSonic() {
    long duration, mm;
    digitalWrite(ultraSonicPingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultraSonicPingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultraSonicPingPin, LOW);
    duration = pulseIn(ultraSonicEchoPin, HIGH);
    mm = 10 * duration / 29 / 2;
    return mm;
  }

  int getDistanceIR(byte flag = 0) {
    IRDistance_cm = IRDistanceSensor.distance();
    return IRDistance_cm;
    
  }

  int getIRPhototransitorCountsPeriods(int pin, int periods = 10) {
    unsigned long timeout = PULSE_LENGTH * periods;
    int count = 0;
    unsigned long start = micros();
    bool current_state;
    
    bool last_state = digitalRead(pin);
    while (micros() - start < timeout) {
      current_state = digitalRead(pin);
      if (!current_state && last_state) {
        count++;
      }
      last_state = current_state;
    }
    return count;
  }

  int getIRPhototransitorCounts(int pin, int period = 100) {
    int count = 0;
    unsigned long start = millis();
    bool state = false;
    bool reading;
    while (millis() - start <= period){ // rollover issue to solve
      reading = digitalRead(pin);
      if (reading && !state){
        // Reading is high, state is LOW
        state = true;
      }
      if (!reading && state){
        // Reading is low; state is HIGH
        state = false;
        count += 1;  
      }
    }
    return count;
  }

  byte _findDummyPin(int pin, int repeat = 3) {
    int sum = 0;
    for (int i = 0; i < repeat; i++) {
      sum += sensors::getIRPhototransitorCounts(pin);// todo
    }
    
    int average = sum / repeat;
    // last_dummy_found will not be updated if NO_DUMMY is found
    if (average > 300 && average < 400) {
      return WHITE_DUMMY;
    } else if (average > 5 && average < 30) {
      return RED_DUMMY;
    } else if (average > 140 && average < 260) {
      return BLUE_DUMMY;
    }
    return NO_DUMMY;
  }

  byte findDummy() {
    int left_count = sensors::getIRPhototransitorCounts(leftIRPhototransitorPin);
    int right_count = sensors::getIRPhototransitorCounts(rightIRPhototransitorPin);

    int count; // get the higher counts
    if (left_count > right_count) {
      count = left_count;
    } else {
      count = right_count;
    }

    if (count > 300 && count < 400) {
      last_dummy_found = WHITE_DUMMY;
    } else if (count > 5 && count < 30) {
      last_dummy_found = RED_DUMMY;
    } else if (count > 140 && count < 260) {
      last_dummy_found = BLUE_DUMMY;
    }
    return last_dummy_found;
  }

  bool isWhite(int value) {
    if (value - WHITE < THRESHOLD) {
      return true;
    }
    return false;
  }

  bool isWhiteFront(int value) {
    if (value - WHITEFRONT < THRESHOLD) {
      return true;
    }
    return false;
  }
  bool isWhiteBack(int value) {
    if (value - WHITEBACK < THRESHOLD) {
      return true;
    }
    return false;
  }
  
  bool isBlack(int value) {
    if (BLACK - value < THRESHOLD) {
      return true;
    }
    return false;
  }
  
  LightValues getLightValues() {
    last_l_value = current_l_value;
    current_l_value.front_left = analogReadAverage(frontLeftPin);
    current_l_value.front_right = analogReadAverage(frontRightPin);
   
    current_l_value.back_right = analogReadAverage(backRightPin);
    current_l_value.back_left = analogReadAverage(backLeftPin);
    return current_l_value;
  } 

  LightValues getLightValuesDerivative() {
    LightValues l_derivative = LightValues();
    LightValues l_value = getLightValues();

    l_derivative.front_left = l_value.front_left - last_l_value.front_left;
    l_derivative.front_right = l_value.front_right - last_l_value.front_right;
    l_derivative.back_left = l_value.back_left - last_l_value.back_left;
    l_derivative.back_right = l_value.back_right - last_l_value.back_right;

    return l_derivative;
  }
  
  void encoderLeft() {
    leftEncoderCount += 1;
  }
  void encoderRight() {
    rightEncoderCount += 1;
  }

  void begin() {
    Serial.println("Initializing Sensors... ");
    pinMode(frontLeftPin, INPUT);
    pinMode(frontRightPin, INPUT);
    pinMode(backRightPin, INPUT);
    pinMode(backLeftPin, INPUT);
    pinMode(ultraSonicPingPin, OUTPUT);
    pinMode(ultraSonicEchoPin, INPUT);
    pinMode(startButtonPin, INPUT_PULLUP);
    pinMode(IRDistancePin, INPUT);

    attachInterrupt(digitalPinToInterrupt(2), encoderLeft, CHANGE);
    attachInterrupt(digitalPinToInterrupt(3), encoderRight, CHANGE);
  }
}
#endif
