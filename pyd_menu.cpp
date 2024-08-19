#include "pyd_menu.h"

PYD_RotaryEncoder* PYD_RotaryEncoder::mEncoder = nullptr;

void PYD_RotaryEncoder::begin()
{
    mQDecoder.begin();
    attachInterrupt(digitalPinToInterrupt(mPinA), isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(mPinB), isr, CHANGE);
    pinMode(mPinButton, INPUT_PULLUP);
    PYD_RotaryEncoder::mEncoder = this;
}

void PYD_RotaryEncoder::end()
{
    mQDecoder.end();
    detachInterrupt(digitalPinToInterrupt(mPinA));
    detachInterrupt(digitalPinToInterrupt(mPinB));
    pinMode(mPinButton, INPUT);
    PYD_RotaryEncoder::mEncoder = nullptr;
}

void PYD_RotaryEncoder::isr()
{
    if (PYD_RotaryEncoder::mEncoder == nullptr)
        return;
    SimpleHacks::QDECODER_EVENT event = PYD_RotaryEncoder::mEncoder->mQDecoder.update();
    if (event & SimpleHacks::QDECODER_EVENT_CW) {
        PYD_RotaryEncoder::mEncoder->rotaryEventIn.registerEvent(Menu::RotaryEventIn::EventType::ROTARY_CW);
    } else if (event & SimpleHacks::QDECODER_EVENT_CCW) {
        PYD_RotaryEncoder::mEncoder->rotaryEventIn.registerEvent(Menu::RotaryEventIn::EventType::ROTARY_CCW);
    }
}
