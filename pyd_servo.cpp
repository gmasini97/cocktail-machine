#include "pyd_servo.h"

PYD_Servo::PYD_Servo(int servo_pin) {
  mServo.attach(servo_pin);
  mServo.setPeriodHertz(50);
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