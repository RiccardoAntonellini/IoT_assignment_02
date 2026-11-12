#include "LedTask.h"
#include "../config.h"

LedTask::LedTask(Context* ctx, Led* led): Task(BLINK_TIME) {
    this->ctx = ctx; //stato del sistema
    this->led = led;
    this->state = OFF; //stato del led
}

    void LedTask::tick() {
        if (this->state == OFF) { //se il led è spento, controlliamo il sistema
            if(ctx->state == PREALARM) {
                led->switchON();
                this->state = ON;
            }
            else if (ctx -> state == ALARM) {
                led->switchON();
                this->state = BLINKING_ON;
            }
        }
        else if (this->state == BLINKING_ON) { //sta lampeggiando e in questo momento il led è acceso
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
        else if (this->state == BLINKING_OFF) { //il led sta lampeggiando ma in questo momento è nella fase spenta
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
        else if(this->state == ON) { //il led è acceso fisso
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