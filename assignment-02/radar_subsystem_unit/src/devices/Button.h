#pragma once

#include <Arduino.h>

class Button {
    public:
        explicit Button(uint8_t pin); // mi obbligo ad esplicitare la creazione di un Button
        void init();
        void update();
        bool isPressed() const;
        bool justPressed() const;

    private:
        uint8_t pin;
        bool rawState;
        bool stableState;
        bool pressedEvent;
        unsigned long lastChangeTime;
};