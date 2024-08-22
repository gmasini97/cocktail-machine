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