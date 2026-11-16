#pragma once

#include <Arduino.h>

class TempSensor {
    public:
        explicit TempSensor(uint8_t pin);
        void init();
        float readCelsius() const; // temperatura mediata su campioni letture
        float speedCalc(float celsius) const; // velocità del suono a quella temperatura

    private:
        uint8_t pin;
};