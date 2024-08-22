#include "pyd_stepper.h"

void PYD_Stepper::begin() {
    mStepper = mEngine->stepperConnectToPin(mPinStep);
    mStepper->setDirectionPin(mPinDir, mDirectionReverse);
    mStepper->setAutoEnable(true);
    if (mPinEn >= 0)
        mStepper->setEnablePin(mPinEn);
    if (mSpeed > 0)
        mStepper->setSpeedInHz(mmToSteps(mSpeed));
    if (mAcceleration > 0)
        mStepper->setAcceleration(mmToSteps(mAcceleration));
    if (mPinEndstop >= 0)
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
    mStepper->moveTo(mmToSteps(mm),blocking);
    return true;
}

void PYD_Stepper::home() {
    if (mPinEndstop < 0)
        return;
    if (mSpeedHoming > 0)
        mStepper->setSpeedInHz(mmToSteps(mSpeedHoming));
    mStepper->runBackward();
    while (!readEndstop()) {}
    mStepper->forceStopAndNewPosition(0);
    if (mSpeed > 0)
        mStepper->setSpeedInHz(mmToSteps(mSpeed));
}