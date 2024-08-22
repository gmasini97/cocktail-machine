#ifndef PYD_SERVO_H
#define PYD_SERVO_H

#include <ESP32Servo.h>

class PYD_Servo {
  public:
    PYD_Servo(int servo_pin);
    bool move(int pos);
    void test();
    
  private:
    Servo mServo;
};

#endif