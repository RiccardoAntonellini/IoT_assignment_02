#pragma once

#include "../kernel/Task.h"
#include "../devices/Button.h"
#include "../model/Context.h"

class ButtonTask : public Task {
    public:
    ButtonTask(Context* ctx, Button* startButton, Button* stopButton, Button* resetButton);
    void tick() override;

    private:
        Context* ctx;
        Button* startButton;
        Button* stopButton;
        Button* resetButton;
};