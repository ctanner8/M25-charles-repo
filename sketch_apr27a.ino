#include "MecanumRobot.h"
const int trigPin = 7;
const int echoPin = 8;
int turn_count = 0;

MecanumRobot robot(4, 3, 6, 5, 10, 9, 12, 11);

void setup() {
  robot.begin();
  robot.setTurnTime(600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}

void turn_right(int turn_count) {
  robot.left(110 + (turn_count*1));
}

void turn_left(int turn_count) {
  robot.right(110 + (turn_count*5));
}

void loop() {
  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;

  
  if (turn_count != 6) {
    if (distance > 0.5) {
      if (distance < 10) {
        robot.stop();
        if (turn_count < 4) {
          turn_right(turn_count);
          turn_count = turn_count + 1;
        } else {
          turn_left(turn_count);
          turn_count = turn_count + 1;
        }
      } else {
        robot.forwardStart();
      }
    }
  } else {
    robot.forwardStart();
    delay(3600);
    robot.stop();
    robot.right(30);
    for (;;) {delay(50);}

  }
  delay(50);
}

