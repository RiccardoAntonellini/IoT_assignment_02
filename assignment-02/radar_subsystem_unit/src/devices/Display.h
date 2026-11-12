#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"

class Display {
    public:
        Display();
        void init();
        void clear();
        void printLine(uint8_t row, const char *text);
        void backLightOn();
        void backLightOff();

    private:
        LiquidCrystal_I2C lcd;
        char lines[LCD_ROWS][LCD_COLS + 1]; // copia per evitare di scrivere due volte la stessa cosa
}