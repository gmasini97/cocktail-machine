#include "pyd_servo.h"

void PYD_Servo::begin() {
  mServo.attach(mServoPin);
  mServo.setPeriodHertz(50);
}

void PYD_Servo::end() {
  mServo.detach();
}

bool PYD_Servo::move(int pos) {
  if (pos < 0 || pos > 180)
    return false;
  mServo.write(pos);
  return true;
}

int PYD_Servo::position() {
  return mServo.read();
}