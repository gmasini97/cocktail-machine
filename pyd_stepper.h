#ifndef PYD_STEPPER_H
#define PYD_STEPPER_H

#include "FastAccelStepper.h"
#include "AVRStepperPins.h" // Only required for AVR controllers

class PYD_Stepper {
  public:
    PYD_Stepper(FastAccelStepperEngine *engine, int pin_step, int pin_direction, int pin_enable, int pin_endstop, int endstop_active_low, bool direction_reverse);

    FastAccelStepper *getFastAccelStepper();
    void setDynamics(int speed_in_hertz, int acceleration);

    int readEndstop();
    void move(int amount);
    void home();
  private:
    FastAccelStepper *stepper = NULL;
    int pin_endstop = -1;
    int endstop_active_low = 0;
};

#endif