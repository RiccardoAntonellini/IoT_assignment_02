#include "TempTask.h"
#include "../config.h"

TempTask::TempTask(Context* ctx, TempSensor* sensor) : Task(TEMP_PERIOD) {
    this->ctx = ctx;
    this->sensor = sensor;
}

void TempTask::tick() {
    float celsius = sensor->readCelsius();
    ctx->temperature = celsius;
    ctx->soundSpeed = sensor->speedCalc(celsius);
}
