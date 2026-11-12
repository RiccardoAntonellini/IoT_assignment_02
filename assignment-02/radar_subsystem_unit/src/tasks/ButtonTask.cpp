#include "ButtonTask.h"
#include "../config.h"

ButtonTask::ButtonTask(Context* ctx, Button* startButton, Button* stopButton, Button* resetButton): Task(BUTTON_DEBOUNCE_MS) {
    this->ctx = ctx;
    this->startButton = startButton;
    this->stopButton = stopButton;
    this->resetButton = resetButton;
}

void ButtonTask::tick() {
    startButton->update();
    stopButton->update();
    resetButton->update();

    if (startButton->justPressed()) ctx->startPressed = true; //Aggiorniamo lo stato nel context se è appena stato premuto
    if (stopButton->justPressed())  ctx->stopPressed  = true;
    if (resetButton->justPressed()) ctx->resetPressed = true;
}