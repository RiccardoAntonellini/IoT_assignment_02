#include "Sonar.h"
#include "config.h"

Sonar::Sonar(uint8_t trigPin, uint8_t echoPin) : trigPin(trigPin), echoPin(echoPin) {}

void Sonar::init() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW);
}

float Sonar::measure(float soundSpeed) {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // timeout = tempo di andata e ritorno alla portata massima
    unsigned long timeoutMicroseconds = (unsigned long)(2.0f * SONAR_MAX_DISTANCE / soundSpeed * 1000000.0f);

    // durata dell'eco
    unsigned long echoMicroseconds = pulseIn(echoPin, HIGH, timeoutMicroseconds);
    if (echoMicroseconds == 0) {
        return SONAR_NO_OBJECT;
    }

    // distanza = velocità * tempo / 2 (andata e ritorno)
    float distance = echoMicroseconds * soundSpeed / 2000000.0f;
    if (distance > SONAR_MAX_DISTANCE) { // scarto l'echo al limite
        return SONAR_NO_OBJECT;
    }

    return distance;
}