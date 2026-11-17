#include "CommTask.h"
#include "../config.h"
#include <Arduino.h>

CommTask::CommTask(Context* ctx) : Task(COMM_TIME) {
    this->ctx = ctx;
    this->lastState = IDLE;
    this->lastSector = -1;
    this->firstSend = true;
}

const char* CommTask::stateToString(SystemState s) {
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
        return "UNKNOWN";
}

void CommTask::tick() {
    if(this->ctx->state != lastState || firstSend) {
        Serial.print("STATE:");
        Serial.println(stateToString(ctx->state));
        lastState = ctx->state;
        lastSector = -1;
        firstSend = false;
    }

    bool radarIsScanning = (ctx->state == WORKING || ctx->state == PREALARM || ctx->state == ALARM);

    // invio il settore solo se è cambiato
    if(radarIsScanning && ctx->sector != lastSector) {
        int objectDetected = ctx->foundObject ? 1 : 0;
        int distanceCm = ctx->foundObject ? (int)(ctx->distance * 100) : 0;

        // formato --> SECTOR:*settore*:*oggetto (0/1)*:*distanza (cm)*
        Serial.print("SECTOR:");
        Serial.print(ctx->sector);
        Serial.print(':');
        Serial.print(objectDetected);
        Serial.print(':');
        Serial.println(distanceCm);

        lastSector = ctx->sector;
    }
}