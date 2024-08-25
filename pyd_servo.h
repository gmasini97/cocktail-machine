#ifndef PYD_SERVO_H
#define PYD_SERVO_H

#include <ESP32Servo.h>

class PYD_Servo {
  public:
        PYD_Servo(int servoPin) : mServoPin(servoPin) {};

        void begin();
        void end();

    bool move(int pos);
    void test();
    
  private:
        int mServoPin;
    Servo mServo;
};

#endif