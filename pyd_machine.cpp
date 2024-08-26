
#include "pyd_machine.h"

FastAccelStepperEngine MachineStepperEngine;
PYD_Stepper MachineStepper(
    &MachineStepperEngine,
    STEPPER1_PIN_STEP,
    STEPPER1_PIN_DIRECTION,
    STEPPER1_PIN_ENABLE,
    STEPPER1_PIN_ENDSTOP,
    STEPPER1_ENDSTOP_ACTIVE_LOW,
    STEPPER1_REVERSE_DIRECTION,
    STEPPER1_STEPS_MM,
    STEPPER1_MAX_TRAVEL_MM,
    STEPPER1_SPEED,
    STEPPER1_SPEED_HOMING,
    STEPPER1_ACCELERATION
);
PYD_Servo MachineServo(SERVO1_PIN);
PYD_Machine Machine(&Prefs, &MachineStepperEngine, &MachineStepper, &MachineServo);

void PYD_Machine::begin()
{
    mStepperEngine->init();
    mStepper->begin();
    mServo->begin();
}

void PYD_Machine::end()
{
    mStepper->end();
}

bool PYD_Machine::moveAxis(float mm, bool blocking)
{
    // Check if the stepper is homed
    if (!mHomed)
        return false;
    // Check if servo is not at idle position
    if (mServo->position() != mPrefs->servoIdleAngle)
    {
        // Move the servo to the idle position
        moveServo(mPrefs->servoIdleAngle, blocking);
    }
    // Move the stepper to the given position
    mStepper->moveToMM(mm, blocking);
    return true;
}

void PYD_Machine::moveServo(int angle, bool blocking)
{
    if (mServo->position() == angle)
        return;
    mServo->move(angle);
    if (blocking)
        delay(mPrefs->servoIdleTime);
}

void PYD_Machine::home()
{
    // Move servo to safe idle position
    moveServo(mPrefs->servoIdleAngle, true);
    // Home the stepper motor
    mStepper->home();
    // Move the carriage to the glass access position
    mStepper->moveToMM(mPrefs->glassAccessPosition, true);
    // Set the homed flag
    mHomed = true;
}

void PYD_Machine::servoTest()
{
    // Move the servo to the pour angle
    mServo->move(mPrefs->servoPourAngle);
    delay(mPrefs->servoIdleTime);
    // Move the servo to the idle angle
    mServo->move(mPrefs->servoIdleAngle);
    delay(mPrefs->servoIdleTime);
}