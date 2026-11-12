#include "RadarServo.h"
#include "config.h"

RadarServo::RadarServo(uint8_t pin) : pin(pin), angle(MIN_ANGLE), attached(false) {}

void RadarServo::init() {
    angle = MIN_ANGLE;
    attached = false; // idle, non riceve impulsi
}

void RadarServo::on() {
    if (!attached) {
        servo.attach(pin);
        attached = true;
    }
    servo.write(angle); // riporta il servo all'ultimo angolo noto
}

void RadarServo::off() {
    if (attached) {
        servo.detach();
        attached = false;
    }
}

void RadarServo::setAngle(int newAngle) {
    angle = constrain(newAngle, MIN_ANGLE, MAX_ANGLE);
    if (attached) {
        servo.write(angle);
    }
}

void RadarServo::setSector(int sector) {
    int lastSector = N_SECTORS - 1;
    int validSector = constrain(sector, 0, lastSector);
    // distribuzione lineare: settore 0 = 0° e lastSector = 180°
    setAngle(map(validSector, 0, lastSector, MIN_ANGLE, MAX_ANGLE));
}

int RadarServo::getAngle() const { return angle; }
bool RadarServo::isOn() const { return attached; }