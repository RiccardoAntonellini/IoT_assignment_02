#include "Led.h"

Led::Led(uint8_t pin) : pin(pin), state(false) {}

void Led::init() {
    pinMode(pin, OUTPUT);
    switchOFF();
}

void Led::switchON() {
    state = true;
    digitalWrite(pin, HIGH);
}

void Led::switchOFF() {
    state = false;
    digitalWrite(pin, LOW);
}

void Led::toggle() {
    if (state) {
        switchOFF();
    } else {
        switchON();
    }
}

bool Led::isOn() const { return state; }