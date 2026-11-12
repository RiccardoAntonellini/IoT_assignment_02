#pragma once

#include <Arduino.h>
#include <Servo.h>

class RadarServo {
    public:
        explicit RadarServo(uint8_t pin);
        void init();
        void on();
        void off();
        void setAngle(int angle);
        void setSector(int sector);
        int getAngle() const; // ultimo angolo comandato
        bool isOn() const;

    private:
        uint8_t pin;
        Servo servo;
        int angle; // ultimo angolo comandato
        bool attached;
};