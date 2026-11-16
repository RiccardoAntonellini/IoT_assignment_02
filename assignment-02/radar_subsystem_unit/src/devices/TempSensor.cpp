#include "TempSensor.h"
#include "config.h"

TempSensor::TempSensor(uint8_t pin) : pin(pin) {}

void TempSensor::init() {
    pinMode(pin, INPUT);
}

float TempSensor::readCelsius() const {
    // media di più letture
    unsigned int sum = 0;
    for (uint8_t i = 0; i < CAMPIONI_PER_MEDIA_RUMORE_TS; i++) {
        sum += analogRead(pin);
    }

    float raw = (float)sum / CAMPIONI_PER_MEDIA_RUMORE_TS;

    // da livelli a volt
    float voltage = raw * TENSIONE_RIFERIMENTO_TS / LIVELLI_CONVERTITORE_TS;

    // da volt a °C
    return (voltage - TENSIONE_USCITA_0C_TS) / TENSIONE_PER_GRADOC_TS;
}



float TempSensor::speedCalc(float celsius) const {
  return 331.3f + 0.606f * celsius;
}