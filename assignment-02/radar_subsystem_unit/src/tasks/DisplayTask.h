#pragma once

#include "../kernel/Task.h"
#include "../devices/Display.h"
#include "../model/Context.h"

class DisplayTask : public Task {
public:
    DisplayTask(Context* ctx, Display* display);
    void tick() override;

private:
    enum State { DISPLAY_OFF, DISPLAY_ON } state;
    Context* ctx;
    Display* display;

    SystemState lastState;
    int lastSector;
    bool lastFound;
    float lastDistance;

    const char* stateToString(SystemState s);
};