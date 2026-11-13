#include "../config.h"
#include "SystemTask.h"

SystemTask::SystemTask(Context* ctx, Led* greenLed):Task(BASE_PERIOD) {
    this->ctx = ctx;
    this->greenLed = greenLed;
}

void SystemTask::tick() {
    if(ctx->state == IDLE) {
        if(ctx->startPressed) {
            ctx->state = WORKING;
            ctx->distance = -1;
            ctx->foundObject = false;
            greenLed->switchON();
        }
    }
    else if (ctx->state == WORKING) {
        if(ctx->stopPressed) {
            ctx->state = IDLE;
            ctx->distance = -1;
            ctx->foundObject = false;
            ctx->sector = 0;
            greenLed->switchOFF();
        }
        else if(ctx->distance > 0 && ctx->distance < D1) {
            ctx-> state = ALARM;
        }
        else if(ctx->distance >= D1 && ctx->distance < D2) {
            ctx->state = PREALARM;
        }
    }
    else if (ctx -> state == PREALARM) {
        if(ctx->distance > 0 && ctx->distance < D1) {
            ctx-> state = ALARM;
        }
        else if(ctx->distance <= 0 || ctx->distance >= D2) {
            ctx->state = WORKING;
        }
    }
    else if(ctx -> state == ALARM) {
        if(ctx->resetPressed) {
            ctx->state = WORKING;
            ctx->distance = -1;
            ctx->foundObject = false;
        }
    }
    ctx->startPressed = false;
    ctx->resetPressed = false;
    ctx->stopPressed = false;
}