#include "pyd_servo.h"

PYD_Servo::PYD_Servo(int servo_pin) {
  this->servo.attach(servo_pin);
  this->servo.setPeriodHertz(50);
}

void PYD_Servo::test() {
  int pos;
  for (pos = 40; pos <= 60; pos += 1) {
    this->servo.write(pos);
    delay(15);
  }
  for (pos = 60; pos >= 40; pos -= 1) {
    this->servo.write(pos);
    delay(15);
  }
}