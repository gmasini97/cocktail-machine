#include "pyd_stepper.h"

void PYD_Stepper::begin() {
    mStepper = mEngine->stepperConnectToPin(mPinStep);
    mStepper->setDirectionPin(mPinDir, mDirectionReverse);
    mStepper->setEnablePin(mPinEn);
    mStepper->setAutoEnable(true);
    mStepper->setSpeedInHz(mmToSteps(mSpeed));
    mStepper->setAcceleration(mmToSteps(mAcceleration));
    pinMode(mPinEndstop, INPUT);
}

void PYD_Stepper::end() {

}

FastAccelStepper* PYD_Stepper::getFastAccelStepper() {
    return mStepper;
}

int PYD_Stepper::readEndstop() {
    return digitalRead(mPinEndstop) ^ mEndstopActiveLow;
}

int PYD_Stepper::mmToSteps(float mm)
{
    return round(mm * mStepsMM);
}

bool PYD_Stepper::moveToMM(float mm, bool blocking)
{
    if (mm < 0)
        return false;
    if (mMaxTravelMM > 0 && mm > mMaxTravelMM)
        return false;
    mStepper->move(mmToSteps(mm),blocking);
    return true;
}

void PYD_Stepper::home() {
    mStepper->runBackward();
    while (!readEndstop()) {}
    mStepper->forceStopAndNewPosition(0);
}