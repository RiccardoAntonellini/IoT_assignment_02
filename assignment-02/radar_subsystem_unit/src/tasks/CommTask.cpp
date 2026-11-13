#include "CommTask.h"
#include "../config.h"
#include <Arduino.h>

CommTask::CommTask(Context* ctx) : Task(COMM_TIME) {
    this->ctx = ctx;
    this->lastState = IDLE;
    this->lastSector = -1;
    this->firstSend = true;
}

const char* stateToString(SystemState s) {
    if(s == IDLE) {
        return "IDLE";
    }
    else if(s == WORKING) {
        return "WORKING";
    }
    else if(s == PREALARM) {
        return "PREALARM";
    }
    else if(s == ALARM) {
        return "ALARM";
    }
    else 
        return "UNKWNOWN";
}

void CommTask::tick() {
    if(this->ctx->state != lastState || firstSend) {
        Serial.print("STATE:");
        Serial.println(stateToString(ctx->state));
        lastState = ctx->state;
        lastSector = -1;
        firstSend = false;
    }

    if(ctx->state == WORKING || ctx->state == PREALARM || ctx->state == ALARM) {
        if(ctx->sector != lastSector) {
            Serial.print("SCANNING THIS SECTOR: ");
            Serial.print(ctx->sector);
            Serial.println(ctx->foundObject ? "Found" : "Not Found");
            Serial.print("At " + String(ctx->distance) + "distance");
            lastSector = ctx->sector;
        }
    }
}