#ifndef PYD_STEPPER_H
#define PYD_STEPPER_H

#include "FastAccelStepper.h"
#include "AVRStepperPins.h" // Only required for AVR controllers

class PYD_Stepper {
    public:
        PYD_Stepper(
            FastAccelStepperEngine *engine,
            int pinStep,
            int pinDir,
            int pinEn,
            int pinEndstop = -1,
            int endstopActiveLow = 0,
            bool directionReverse = false
        ) : mEngine(engine),
            mPinStep(pinStep),
            mPinDir(pinDir),
            mPinEn(pinEn),
            mPinEndstop(pinEndstop),
            mEndstopActiveLow(endstopActiveLow),
            mDirectionReverse(directionReverse)
        {
        }

        void begin();
        void end();

        FastAccelStepper *getFastAccelStepper();
        void setDynamics(int speed_in_hertz, int acceleration);

        int readEndstop();
        void move(int amount);
        void home();
        
    private:
        int mPinStep, mPinDir, mPinEn, mPinEndstop;
        int mEndstopActiveLow;
        bool mDirectionReverse;
        FastAccelStepper *mStepper = NULL;
        FastAccelStepperEngine *mEngine;
};

#endif