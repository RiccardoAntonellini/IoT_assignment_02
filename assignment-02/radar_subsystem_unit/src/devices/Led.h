#pragma once

#include <Arduino.h>

class Led {
    public:
        explicit Led(uint8_t pin);
        void init();
        void switchON();
        void switchOFF();
        void toggle(); // inverte lo stato per il lampeggio in ALARM state
        bool isOn() const;

    private:
        uint8_t pin;
        bool state;
};