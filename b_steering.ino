#include <Servo.h>

Servo steeringServo;

#define SERVO_PIN 3
byte offset = 2; // for alignment

void steering(int steeringAngle) {
  steeringServo.write(steeringAngle);
}
