#include "LedTask.h"
#include "../config.h"

LedTask::LedTask(Context* ctx, Led* led): Task(BLINK_TIME) {
    this->ctx = ctx;
    this->led = led;
    this->state = OFF;
}

    void LedTask::tick() {
        if (this->state == OFF) {
            if(ctx->state == PREALARM) {
                led->switchON();
                this->state = ON;
            }
            else if (ctx -> state == ALARM) {
                led->switchON();
                this->state = BLINKING_ON;
            }
        }
        else if (this->state == BLINKING_ON) {
            if (ctx->state == ALARM) {
                led->switchOFF();
                this->state = BLINKING_OFF;
            }
            else if(ctx->state == PREALARM) {
                this->state = ON;
            }
            else if(ctx->state == IDLE) {
                led->switchOFF();
                this->state = OFF;
            }
            else if(ctx->state == WORKING) {
                led->switchOFF();
                this->state = OFF;
            }
        }
        else if (this->state == BLINKING_OFF) {
            if(ctx->state == ALARM) {
                led->switchON();
                this->state = BLINKING_ON;
            }
            else if (ctx->state == PREALARM) {
                led->switchON();
                this->state = ON;
            }
            else if (ctx->state == WORKING) {
                this->state = OFF;
            }
            else if (ctx->state == IDLE) {
                this->state = OFF;
            }
        }
        else if(this->state == ON) {
            if(ctx->state == ALARM) {
                led->switchOFF();
                this->state = BLINKING_OFF;
            }
            else if (ctx->state == WORKING) {
                led->switchOFF();
                this->state = OFF;
            }
            else if (ctx->state == IDLE) {
                led->switchOFF();
                this->state = OFF;
            }
        }
    }   