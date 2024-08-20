#include "pyd_stepper.h"

void PYD_Stepper::begin() {
    mStepper = mEngine->stepperConnectToPin(mPinStep);
    mStepper->setDirectionPin(mPinDir, mDirectionReverse);
    mStepper->setEnablePin(mPinEn);
    mStepper->setAutoEnable(true);
    pinMode(mPinEndstop, INPUT);
}

void PYD_Stepper::end() {

}

FastAccelStepper* PYD_Stepper::getFastAccelStepper() {
    return mStepper;
}

void PYD_Stepper::setDynamics(int speed_in_hertz, int acceleration) {
    mStepper->setSpeedInHz(speed_in_hertz);
    mStepper->setAcceleration(acceleration);
}

int PYD_Stepper::readEndstop() {
    return digitalRead(mPinEndstop) ^ mEndstopActiveLow;
}

void PYD_Stepper::home() {
    mStepper->runBackward();
    while (!readEndstop()) {}
    mStepper->forceStopAndNewPosition(0);
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