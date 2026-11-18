#pragma once

#include "../kernel/Task.h"
#include "../devices/Led.h"
#include "../model/Context.h"

class LedTask : public Task {
    public:
    LedTask(Context* ctx, Led* led);
    void tick() override;

    private:
        enum State{OFF, BLINKING_ON, BLINKING_OFF, ON} state;// on, off, lampeggiava quindi va spento, non lampeggiava quindi va acceso
        Context* ctx;
        Led* led;
};