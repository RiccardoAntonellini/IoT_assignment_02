#include "DisplayTask.h"
#include "../../config.h"
#include <stdio.h>

DisplayTask::DisplayTask(Context* ctx, Display* display) : Task(DISPLAY_PERIOD) {
    this->ctx = ctx;
    this->display = display;
    this->state = DISPLAY_OFF;
    this->lastState = IDLE;
    this->lastSector = -1;
    this->lastFound = false;
    this->lastDistance = -1;
}

const char* DisplayTask::stateToString(SystemState s) {
    if (s == IDLE)     return "IDLE";
    if (s == WORKING)  return "WORKING";
    if (s == PREALARM) return "PRE-ALARM";
    if (s == ALARM)    return "ALARM";
    return "UNKNOWN";
}

void DisplayTask::tick() {
    if (state == DISPLAY_OFF) {
        if (ctx->state != IDLE) {
            display->backLightOn();
            lastState = IDLE;      // forza la prima scrittura
            lastSector = -1;
            state = DISPLAY_ON;
        }
    }
    else { // DISPLAY_ON
        if (ctx->state == IDLE) {
            display->clear();
            display->backLightOff();
            state = DISPLAY_OFF;
        }
        else if (ctx->state != lastState ||
                 ctx->sector != lastSector ||
                 ctx->foundObject != lastFound ||
                 ctx->state == ALARM) {

            // riga 1: stato del sistema
            display->printLine(0, stateToString(ctx->state));

            // riga 2: settore (1..N) e oggetto
            char line[17];
            if (ctx->state == ALARM) {
                // in alarm mostro l'angolo manuale del radar
                snprintf(line, sizeof(line), "Angolo: %d", ctx->manualAngle);
            } else if (ctx->foundObject) {
                // distanza in centimetri, intera (snprintf non supporta %f su AVR)
                snprintf(line, sizeof(line), "S%d/%d Obj %dcm",
                         ctx->sector + 1, N_SECTORS, (int)(ctx->distance * 100));
            } else {
                snprintf(line, sizeof(line), "S%d/%d --",
                         ctx->sector + 1, N_SECTORS);
            }
            display->printLine(1, line);

            lastState = ctx->state;
            lastSector = ctx->sector;
            lastFound = ctx->foundObject;
        }
    }
}