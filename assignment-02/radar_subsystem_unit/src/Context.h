#pragma once

#include "config.h"

enum SystemState {
    IDLE,
    WORKING,
    PREALARM,
    ALARM
};

struct Context {
    SystemState state = IDLE;

    //scansione

    int sector = 0;
    bool foundObject = false;
    float distance = 0;

    //temp
    float temperature = 20.0; // In celcius
    float soundSpeed = 343.0;

    bool startPressed = false;
    bool stopPressed = false;
    bool resetPressed = false;

    int manualAngle = 0;

    bool remoteControl = false;
};
