#ifndef PYD_SERVO_H
#define PYD_SERVO_H

#include <ESP32Servo.h>

class PYD_Servo {
  public:
    PYD_Servo(int servo_pin);
    void test();
  private:
    Servo servo;
};

#endif