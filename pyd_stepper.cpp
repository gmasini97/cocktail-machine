#include "pyd_stepper.h"

PYD_Stepper::PYD_Stepper(FastAccelStepperEngine *engine, int pin_step, int pin_direction, int pin_enable, int pin_endstop, int endstop_active_low, bool direction_reverse)
{
  this->stepper = engine->stepperConnectToPin(pin_step);
  this->stepper->setDirectionPin(pin_direction, direction_reverse);
  this->stepper->setEnablePin(pin_enable);
  this->stepper->setAutoEnable(true);

  this->pin_endstop = pin_endstop;
  this->endstop_active_low = endstop_active_low;
  pinMode(pin_endstop, INPUT);
}

FastAccelStepper *PYD_Stepper::getFastAccelStepper() {
  return this->stepper;
}

void PYD_Stepper::setDynamics(int speed_in_hertz, int acceleration) {
  this->stepper->setSpeedInHz(speed_in_hertz);
  this->stepper->setAcceleration(acceleration);
}

int PYD_Stepper::readEndstop() {
  return digitalRead(this->pin_endstop) ^ this->endstop_active_low;
}

void PYD_Stepper::home() {
  Serial.println("Homing...");
  this->stepper->runBackward();
  while (!this->readEndstop()) {}
  this->stepper->forceStopAndNewPosition(0);
  Serial.println("Homing done.");
}




// #include "FastAccelStepper.h" 
// #include "Configuration.h"


// #include "FastAccelStepper.h"
// #include "AVRStepperPins.h" // Only required for AVR controllers

// #define dirPinStepper    PIN_STEPPER1_DIR
// #define enablePinStepper PIN_STEPPER1_ENABLE
// #define stepPinStepper   PIN_STEPPER1_STEP
// #define homeSwitch       PIN_STEPPER1_HOME

// // If using an AVR device use the definitons provided in AVRStepperPins
// //    stepPinStepper1A
// //
// // or even shorter (for 2560 the correct pin on the chosen timer is selected):
// //    stepPinStepperA

// FastAccelStepperEngine engine = FastAccelStepperEngine();
// FastAccelStepper *stepper = NULL;

// void setup() {
//   Serial.begin(115200);
//    engine.init();
//    stepper = engine.stepperConnectToPin(stepPinStepper);
//    if (stepper) {
//       stepper->setDirectionPin(dirPinStepper);
//       stepper->setEnablePin(enablePinStepper);
//       stepper->setAutoEnable(true);

//       stepper->setSpeedInHz(50);       // 500 steps/s
//       stepper->setAcceleration(100);    // 100 steps/s²
//       stepper->move(2000);
//    }
//    pinMode(PIN_STEPPER1_HOME, INPUT_PULLUP);
// }

// void loop() {
//   Serial.println(digitalRead(PIN_STEPPER1_HOME));
//   delay(200);
// }