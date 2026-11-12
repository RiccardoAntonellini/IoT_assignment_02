#pragma once

#include <Arduino.h>

class Potentiometer {
    public:
        explicit Potentiometer(uint8_t pin);
        void init();
        int readRaw() const; // valore grezzo tra 0 e 1023
        int getAngle() const; // valore convertito in gradi tra min e max

    private:
        uint8_t pin;
};