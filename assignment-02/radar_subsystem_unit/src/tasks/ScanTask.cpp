#include "ScanTask.h"
#include "../config.h"

ScanTask::ScanTask(Sonar* sonar, Context* ctx, Potentiometer* pot, RadarServo* servo):Task(SCAN_PERIOD_S1) {
    this->sonar = sonar;
    this->ctx = ctx;
    this->pot = pot;
    this->servo = servo;
    this->currentSector = 0;
    this->state = STOPPED;
    this->isFirstAlarm = true;
    this->potMoved = false;
    this->initialPotAngle = 0;
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

int ScanTask::angleToSector(int angle, int numSectors) {
    // Limita l'angolo per sicurezza tra 0 e 180
    angle = constrain(angle, 0, 180);
    
    // Calcola l'ampiezza di ogni settore (es. 180 / 10 = 18 gradi a settore)
    // Usando la divisione intera, 180 / 18 darebbe 10 (fuori range 0..9), quindi usiamo min()
    int sector = (angle * numSectors) / 180;
    return min(sector, numSectors - 1);
}

int ScanTask::sectorToAngle(int sector, int numSectors) {
    // Limita il settore per sicurezza tra 0 e numSectors - 1
    sector = constrain(sector, 0, numSectors - 1);
    
    // Calcola il centro dello spicchio corrispondente al settore
    // Esempio con 10 settori (ampiezza 18° ciascuno):
    // settore 0 -> 9°, settore 1 -> 27°, ..., settore 9 -> 171°
    int angle = ((sector * 2 + 1) * 180) / (numSectors * 2);
    return constrain(angle, 0, 180);
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
        if(ctx->state == ALARM) {
            setPeriod(BASE_PERIOD);
            int currentPotAngle = pot->getAngle();

            if(isFirstAlarm) {
                initialPotAngle = currentPotAngle;
                isFirstAlarm = false;
                potMoved = false;
            }
            if(!potMoved && abs(currentPotAngle - initialPotAngle) > 5) {
                potMoved = true;
            }

            int angle = potMoved ? currentPotAngle : sectorToAngle(ctx->sector, N_SECTORS);

            ctx->manualAngle = angle;
            servo->setAngle(angle);
            ctx->sector = angleToSector(angle, N_SECTORS);
            
            float distance = sonar->measure(ctx->soundSpeed);
            ctx->distance = distance;
            ctx->foundObject = (distance > 0 && distance < SONAR_MAX_DISTANCE);
        }
        else {
            state = STOPPED;
            setPeriod(SCAN_PERIOD_S1);
            isFirstAlarm = true;
            potMoved = false;
        }
    }
}