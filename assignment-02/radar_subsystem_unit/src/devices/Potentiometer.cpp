#include "Potentiometer.h"
#include "config.h"

Potentiometer::Potentiometer(uint8_t pin) : pin(pin) {}

void Potentiometer::init() {
    pinMode(pin, INPUT);
}

int Potentiometer::readRaw() const {
    return analogRead(pin); //conversione a 10 bit
}

int Potentiometer::getAngle() const {
    // map non satura da sola, garantisco l'intervallo usando constrain
    int angle = map(readRaw(), 0, 1023, MIN_ANGLE, MAX_ANGLE);
    return constrain(angle, MIN_ANGLE, MAX_ANGLE);
}