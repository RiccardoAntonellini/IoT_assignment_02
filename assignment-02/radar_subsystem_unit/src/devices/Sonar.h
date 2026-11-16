#pragma once

#include <Arduino.h>

const float SONAR_NO_OBJECT =  -1.0f;

class Sonar {
    public:
        Sonar(uint8_t trigPin, uint8_t echoPin);
        void init();
        float measure(float soundSpeed); // in metri

    private:
        uint8_t trigPin;
        uint8_t echoPin;
};