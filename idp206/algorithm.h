/*
IDP Group M206 (Michaelmas 2021)

Algorithms
- rescueLineDummy(): Main code for finding the first dummy
- goSlow(): After detecting dummy with ultrasonic, detect IR signature while going slow
- dropOff(): Move the dummy ot the respective delivery area and drop it off

*/

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Arduino.h"
#include "conditionals.h"
#include "controllers.h"
#include "indicator.h"
#include "servos.h"

namespace algo {
  unsigned long start;

  void toWhite() {
    // Go to white delivery area from the main line
    
    line_follower.run(FORWARD, conditionals::isArrivingJunctionFront);
  }

  void toRedBlueJunction() {
    // Go to the junction next to red and blue delivery area
    
    line_follower.run(FORWARD, conditionals::isArrivingJunctionFront);
    
    start = millis();
    simple_controller.run(BACKWARD, [start](){return millis() - start > 250;});
    
    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);
    
    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack);
  }

  void toRed() {
    // Go to red delivery area from the main line
    
    toRedBlueJunction();

    start = millis();
    simple_controller.rotate(CLOCKWISE, [start](){return millis() - start > 2200;});
  }

  void toBlue() {
    // Go to white delivery area from the main line
    
    toRedBlueJunction();

    start = millis();
    simple_controller.rotate(ANTICLOCKWISE, [start](){return millis() - start > 2200;});
  }

  void toSearchFromWhite() {
    // Go back to the searching area after having dropped a dummy in white delivery area
    
    start = millis();
    simple_controller.run(BACKWARD, [start](){return millis() - start > 250;});

    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);

    start = millis();
    simple_controller.run(FORWARD, [start](){return millis() - start > 2000;});

    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);
  }

  void toSearchFromRed() {
    // Go back to the searching area after having dropped a dummy in red delivery area
    
    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW, 1);
  }

  void toSearchFromBlue() {
    // Go back to the searching area after having dropped a dummy in blue delivery area
    
    simple_controller.rotate(ANTICLOCKWISE, conditionals::foundLineWhileRotateACW, 2);
  }

  void toBaseFromWhite() {
    // Go back to the starting position after having dropped a dummy in white delivery area
    
    start = millis();
    simple_controller.run(BACKWARD, [start](){return millis() - start > 250;});

    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW);

    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 2, [](){delay(500);}); // go further into the box for 500ms
  }
  
  void toBaseFromRed() {
    // Go back to the starting position after having dropped a dummy in red delivery area
    
    simple_controller.rotate(ANTICLOCKWISE, conditionals::foundLineWhileRotateACW, 1);

    line_follower.run(FORWARD, conditionals::isArrivingJunctionFront);
    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 1, [](){delay(500);}); // go further into the box for 500ms
  }

  void toBaseFromBlue() {
    // Go back to the starting position after having dropped a dummy in blue delivery area
    
    simple_controller.rotate(CLOCKWISE, conditionals::foundLineWhileRotateCW, 2);

    line_follower.run(FORWARD, conditionals::isArrivingJunctionFront);
    line_follower.run(FORWARD, conditionals::isArrivingJunctionBack, 1, [](){delay(500);}); // go further into the box for 500ms
  }

  void dropOff(byte dummy, bool returnToBaseAfterwards = false) {
    // Go to the delivery area and drop the dummy based on their signals
    
    switch (dummy) {
      case NO_DUMMY:
      case WHITE_DUMMY:
        toWhite();
        break;
      case RED_DUMMY:
        toRed();
        break;
      case BLUE_DUMMY:
        toBlue();
        break;
    }

    servos::dropOff();

    if (!returnToBaseAfterwards) {
      switch (dummy) {
        case NO_DUMMY:
        case WHITE_DUMMY:
          toSearchFromWhite();
          break;
        case RED_DUMMY:
          toSearchFromRed();
          break;
        case BLUE_DUMMY:
          toSearchFromBlue();
          break;
      }
    } else {
      switch (dummy) {
        case NO_DUMMY:
        case WHITE_DUMMY:
          toBaseFromWhite();
          break;
        case RED_DUMMY:
          toBaseFromRed();
          break;
        case BLUE_DUMMY:
          toBaseFromBlue();
          break;
      }
    }
  }

  void goSlow() {
    // Go slow to identify the dummy
    
    line_follower.run(FORWARD, conditionals::isDummyDetected, 1, [](){}, 100);
  }

  void rescueLineDummy() {
    // Overall algorithm for rescuing the dummy that's on the line
    
    line_follower.run(FORWARD, conditionals::isObjectFound);
    delay(1000);
    
    // identify the dummy
    goSlow();
    indicator::indicate(last_dummy_found);

    // grab the dummy
    servos::pickUp();

    dropOff(last_dummy_found, true); // true means return to base afterwards. false means go to search area.
    
    last_dummy_found = NO_DUMMY;
    indicator::indicate(last_dummy_found);
  }
}
#endif 
