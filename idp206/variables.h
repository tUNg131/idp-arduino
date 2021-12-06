/*
IDP Group M206 (Michaelmas 2021)

Variables: containing all the global variables.

*/

#ifndef VARIABLES_H
#define VARIABLES_H

// Pins
const int frontLeftPin = A3;
const int frontRightPin = A2;
const int backRightPin = A1;
const int backLeftPin = A0;
const int IRDistancePin = A4;
const int IRDistancePin2 = A5;

const int leftEncoderPin = 2;   // Interrupts can only be on pin2/3
const int rightEncoderPin = 3;
const int leftIRPhototransitorPin = 4;
const int rightIRPhototransitorPin = 5;
const int ultraSonicPingPin = 6;
const int ultraSonicEchoPin = 7;
const int redLEDPin = 8;
const int grabberServoPin = 9; // Servos can only be pin 9/10
const int lifterServoPin = 10;
const int amberLEDPin = 11;
const int greenLEDPin = 12;
const int startButtonPin = 13;

// PID
int KP = 50;
int KI = 1;
int KD = 2;
const int tuningFactor = 1000;

// Line follower
int offset = 0;

// Simple Controller
int rotateDelay = 150;

// Motors
int averagePower = 230;
int defaultDelay = 0;
const byte leftMotorChannel = 4;
const byte rightMotorChannel = 3;

const byte STOP = 0;
const byte CLOCKWISE = 1;
const byte ANTICLOCKWISE = 2;

// Line sensors
const int WHITE = 150;
const int WHITEFRONT = 100;
const int WHITEBACK = 450;
const int BLACK = 750;
const int THRESHOLD = 20;

struct LightValues {
  int front_left;
  int front_right;
  int back_left;
  int back_right;
} current_l_value, last_l_value;

const unsigned long OFF_LINE_TIMEOUT = 3000;

// Dummies
const byte WHITE_DUMMY = 0;
const byte RED_DUMMY = 1;
const byte BLUE_DUMMY = 2;
const byte NO_DUMMY = 3;
byte last_dummy_found = NO_DUMMY;

// Phototransitor
unsigned long PULSE_LENGTH = 6000;

// IR Distance Sensor GP2Y0A21YK0F
#define IRDistanceSensorModel 1080
/* Model :
  GP2Y0A02YK0F --> 20150
  GP2Y0A21YK0F --> 1080
  GP2Y0A710K0F --> 100500
  GP2YA41SK0F --> 430
*/
int IRDistance_cm = 0;

// Encoders
int leftEncoderCount = 0;
int rightEncoderCount = 0;

// Global
bool moving;
unsigned long last_on_line_front;

#endif
