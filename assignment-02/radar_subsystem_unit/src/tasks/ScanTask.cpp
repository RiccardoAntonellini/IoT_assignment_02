#include "ScanTask.h"
#include "../config.h"

ScanTask::ScanTask(Sonar* sonar, Context* ctx, Potentiometer* pot, RadarServo* servo):Task(SCAN_PERIOD_S1) {
    this->sonar = sonar;
    this->ctx = ctx;
    this->pot = pot;
    this->servo = servo;
    this->currentSector = 0;
    this->state = STOPPED;
}

void ScanTask::scanStep() {
    if(ctx->state == PREALARM) {
        setPeriod(SCAN_PERIOD_S2);
    }
    else 
        setPeriod(SCAN_PERIOD_S1);

    servo->setSector(currentSector);
    ctx->sector = currentSector;
    float distance = sonar->measure(ctx->soundSpeed); //Cerchiamo la distanza dell'oggetto
    ctx->distance = distance;
    ctx->foundObject = (distance > 0 && distance < SONAR_MAX_DISTANCE); //restituisce true solo se l'oggetto c'è ed è ad una distanza non troppo ampia.
}

void ScanTask::tick() {
    if(state == STOPPED) {
        if(ctx->state == WORKING || ctx->state == PREALARM) {
            currentSector = 0;
            state = SCAN_FORWARD;
        }
    }
    else if (state == SCAN_FORWARD) {
        if (ctx->state == WORKING || ctx->state == PREALARM) {
            scanStep();
            currentSector++;
            if(currentSector >= N_SECTORS) {
                this->state = SCAN_BACKWARD;
                currentSector = N_SECTORS - 1;
            }
        }
        else if (ctx-> state == IDLE) {
            this->state = STOPPED;
        }
        else if (ctx -> state == ALARM) {
            this -> state = MANUAL;
        }
    }

    else if( state == SCAN_BACKWARD) {
        if (ctx->state == WORKING || ctx->state == PREALARM) {
            scanStep();
            currentSector--;
            if(currentSector < 0) {
                this->state = SCAN_FORWARD;
                currentSector = 1;
            }
        }
        else if (ctx-> state == IDLE) {
            this->state = STOPPED;
        }
        else if (ctx -> state == ALARM) {
            this -> state = MANUAL;
        }
    }

    else if(state == MANUAL) {
        if(ctx -> state == ALARM) {
            setPeriod(BASE_PERIOD);
            int angle = pot->getAngle();
            ctx -> manualAngle = angle;
            servo->setAngle(angle);
        }
        else {
            state = STOPPED;
            setPeriod(SCAN_PERIOD_S1);
        }
    }
}