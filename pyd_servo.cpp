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

void PYD_Servo::test() {
  int pos;
  for (pos = 40; pos <= 60; pos += 1) {
    mServo.write(pos);
    delay(60);
  }
  for (pos = 60; pos >= 40; pos -= 1) {
    mServo.write(pos);
    delay(60);
  }
}