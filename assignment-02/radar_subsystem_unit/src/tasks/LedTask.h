#pragma once

#include "../kernel/Task.h"
#include "../devices/Led.h"
#include "../model/Context.h"

class LedTask : public Task {
    public: 
    LedTask(Context* ctx, Led* led); //* indica un puntatore all'oggetto
    void tick() override;

    private: 
        enum State{OFF, BLINKING_ON, BLINKING_OFF, ON} state;
        Context* ctx;
        Led* led;
};