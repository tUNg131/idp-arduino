/*
IDP Group M206 (Michaelmas 2021)

Debug: containing functions used in debugging
- plotLightValues: plot line sensors raw readings to Serial Plotter
- plotLightValueDerivates: plot derivatives of line sensors raw readings to Serial Plotter
- plotDistanceUltraSonic: prints distance got from UltraSonic readings 
- findDummy: prints type of dummy in front of the robot

*/

#ifndef DEBUG_H
#define DEBUG_H

#include "sensors.h"
#include "indicator.h"


namespace debug {
  void plotLightValues() {
    
    Serial.println("FL\tFR\tBL\tBR");

    while(true) {
      LightValues l_value = sensors::getLightValues();

      
      Serial.print(l_value.front_left);
      Serial.print('\t');
      Serial.print(l_value.front_right);
      Serial.print('\t');
      Serial.print(l_value.back_left);
      Serial.print('\t');
      Serial.println(l_value.back_right);

      delay(50);
    }
  }

  void plotLightValuesDerivative() {
    Serial.println("FL\tFR\tBR\tBL");

    while(true) {
      LightValues l_value = sensors::getLightValuesDerivative();

      Serial.print(l_value.front_left);
      Serial.print('\t');
      Serial.print(l_value.front_right);
      Serial.print('\t');
      Serial.print(l_value.back_right);
      Serial.print('\t');
      Serial.println(l_value.back_left);
      
      delay(50);
    }
  }

  void plotDistanceUltraSonic() {
    while(true) {
      Serial.println(sensors::getDistanceUltraSonic());
      delay(50);
    }
  }

  void plotIRPhototransitorCounts(int period = 100) {
    Serial.println("Left\tRight");

    while(true) {
      Serial.print(sensors::getIRPhototransitorCounts(leftIRPhototransitorPin, period));
      Serial.print("\t");
      Serial.println(sensors::getIRPhototransitorCounts(rightIRPhototransitorPin, period));

      delay(50);
    }
  }

  void plotIRPhototransitorCountsPeriod(int periods = 10) {
    Serial.println("Left\tRight");

    while(true) {
      Serial.print(sensors::getIRPhototransitorCountsPeriods(leftIRPhototransitorPin, periods));
      Serial.print("\t");
      Serial.println(sensors::getIRPhototransitorCountsPeriods(rightIRPhototransitorPin, periods));

      delay(50);
    }
  }

  void findDummy() {
    while(true) {
      byte flag = sensors::findDummy();
      Serial.println(last_dummy_found);
      switch (flag) {
        case WHITE_DUMMY:
          Serial.println("White dummy");
          break;
        case RED_DUMMY:
          Serial.println("Red dummy");
          break;
        case BLUE_DUMMY:
          Serial.println("Blue dummy");
          break;
        case NO_DUMMY:
          Serial.println("No dummy");
      }
      delay(50);
    }
  }

  void indicatorTest() {
    while(true){
      indicator::moving();
      Serial.println("MOVING");
      delay(2000);
      indicator::indicate(WHITE_DUMMY);
      Serial.println("White Dummy");
      delay(2000);
      indicator::indicate(RED_DUMMY);
      Serial.println("Red Dummy");
      delay(2000);
      indicator::indicate(BLUE_DUMMY);
      Serial.println("Blue Dummy");
      delay(2000);
      indicator::indicate(NO_DUMMY);
      Serial.println("No Dummy");
      delay(2000);
      indicator::stopped();
      Serial.println("STOPPED");
      delay(2000);
    }
  }

  void getDistanceIRTest() {
    while(true) {
      Serial.print("Distance in cm: ");
      Serial.println(sensors::getDistanceIR());
      delay(100);
    }
  }

  void trackEncoderCountTest() {
    //https://forum.arduino.cc/t/using-interrupts-with-uno-wifi-rev2/569016/2
    while(true) {
      Serial.print("Left Encoder: ");
      Serial.print(leftEncoderCount);
      Serial.print('\t');
      Serial.print("Right Encoder: ");
      Serial.println(rightEncoderCount);
      delay(100);
    }  
  }

  void servoTest() {
    while(true) {
      servos::pickUp();
      delay(2000);
      servos::dropOff();
      delay(2000);
    }
  
  }
  
}

#endif
