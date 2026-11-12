#include "Button.h"
#include "config.h"

//sola inizializzazione
Button::Button(uint8_t pin) : pin(pin), rawState(false), stableState(false), pressedEvent(false), lastChangeTime(0) {}

void Button::init() {
    pinMode(pin, INPUT_PULLUP); // a riposo il pin è HIGH
    rawState = stableState = (digitalRead(pin) == LOW);
    lastChangeTime = millis();
}

void Button::update() {
    pressedEvent = false;

    bool reading = (digitalRead(pin) == LOW); // lettura grezza

    if (reading != rawState) {
        rawState = reading;
        lastChangeTime = millis();
    }

    // accetto il nuovo stato solo se è stabile da almeno BUTTON_DEBOUNCE_MS
    if (rawState != stableState && (millis() - lastChangeTime) >= BUTTON_DEBOUNCE_MS) {
        stableState = rawState;
        if (stableState) {
            pressedEvent = true; // rilasciato --> premuto
        }
    }
}

bool Button::isPressed() const { return stableState; }
bool Button::justPressed() const { return pressedEvent; }
