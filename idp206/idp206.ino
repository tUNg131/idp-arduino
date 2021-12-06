/*
IDP Group M206 (Michaelmas 2021)

Main code;
- Sets up all the sensors and actuaotors
- Runs the selected program from algorithm.h

*/


#include "algorithm.h"
#include "debug.h"

void setup() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Starting M206 Dummy Picker");
  
  motors::begin();
  sensors::begin();
  indicator::begin();
  servos::begin();
  
  Serial.println("Awaiting Push Button Activiation...");
  Serial.println("");
}

void loop() {
  if (conditionals::isStartButtonPressed()) {
    Serial.println("Starting...");
    algo::rescueLineDummy();
  }
}
