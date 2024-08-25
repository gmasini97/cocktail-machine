#ifndef PYD_MACHINE_H
#define PYD_MACHINE_H

#include "config.h"
#include "pyd_preferences.h"
#include "pyd_stepper.h"
#include "pyd_servo.h"

class PYD_Machine
{
    public:
        PYD_Machine(
            PYD_Preferences *prefs,
            FastAccelStepperEngine *stepperEngine,
            PYD_Stepper* stepper,
            PYD_Servo* servo
        )
        : mPrefs(prefs),
          mStepperEngine(stepperEngine),
          mStepper(stepper),
          mServo(servo)
        {
        }
        
        void begin();
        void end();

        bool moveAxis(float mm, bool blocking = false);
        void moveServo(int angle, bool blocking = false);

        void home();
        void servoTest();
    
    private:
        bool mHomed = false;
        PYD_Preferences *mPrefs;
        FastAccelStepperEngine *mStepperEngine;
        PYD_Stepper* mStepper;
        PYD_Servo* mServo;
};

extern PYD_Machine Machine;

#endif /* PYD_MACHINE_H */