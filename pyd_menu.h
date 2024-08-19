#ifndef PYD_MENU_H
#define PYD_MENU_H

#include <Arduino.h>
#include <menu.h>
#include <menuIO/rotaryEventIn.h>
#include <menuIO/keyIn.h>
#include <qdec.h>

// Supports only one encoder.
// In order to support more than one encoder transform mEncoder in a list and iterate them in isr().
class PYD_RotaryEncoder
{
    public:
        Menu::keyIn<1> keyIn;
        Menu::RotaryEventIn rotaryEventIn;

        PYD_RotaryEncoder(int pinA, int pinB, int pinButton) :
            mPinA(pinA), mPinB(pinB), mPinButton(pinButton),
            mQDecoder(pinA, pinB, true),
            rotaryEventIn(
                Menu::RotaryEventIn::EventType::ROTARY_CCW |
                Menu::RotaryEventIn::EventType::ROTARY_CW),
            mKeyMap({{-pinButton, Menu::defaultNavCodes[Menu::enterCmd].ch}}),
            keyIn(mKeyMap)
        {
        }
        
        void begin();
        void end();

    private:
        int mPinA, mPinB, mPinButton;
        Menu::keyMap mKeyMap[1];
        SimpleHacks::QDecoder mQDecoder;

        static PYD_RotaryEncoder* mEncoder;

        static void isr();
};

#endif /* PYD_MENU_H */