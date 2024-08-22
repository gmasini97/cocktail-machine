#ifndef PYD_STEPPER_H
#define PYD_STEPPER_H

#include "FastAccelStepper.h"
#ifdef __AVR_ARCH__
    #include "AVRStepperPins.h"
#endif

class PYD_Stepper {
    public:
        PYD_Stepper(
            FastAccelStepperEngine *engine,
            int pinStep,
            int pinDir,
            int pinEn = -1,
            int pinEndstop = -1,
            int endstopActiveLow = 0,
            bool directionReverse = false,
            float stepsMM = 0,
            float maxTravelMM = 0,
            float speed = 0,
            float acceleration = 0
        ) : mEngine(engine),
            mPinStep(pinStep),
            mPinDir(pinDir),
            mPinEn(pinEn),
            mPinEndstop(pinEndstop),
            mEndstopActiveLow(endstopActiveLow),
            mDirectionReverse(directionReverse),
            mStepsMM(stepsMM),
            mMaxTravelMM(maxTravelMM),
            mSpeed(speed),
            mAcceleration(acceleration)
        {
        }

        void begin();
        void end();

        FastAccelStepper *getFastAccelStepper();

        int readEndstop();
        int mmToSteps(float mm);
        bool moveToMM(float mm, bool blocking = false);
        void home();
        
    private:
        int mPinStep, mPinDir, mPinEn, mPinEndstop;
        int mEndstopActiveLow;
        bool mDirectionReverse;
        float mStepsMM, mMaxTravelMM, mSpeed, mAcceleration;
        FastAccelStepper *mStepper = NULL;
        FastAccelStepperEngine *mEngine = NULL;
};

#endif