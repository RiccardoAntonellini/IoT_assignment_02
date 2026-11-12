#include "Display.h"
#include <string.h>

Display::Display() : lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS) {}

void Display::init() {
    lcd.init();
    lcd.backlight();
    clear();
}

void Display::clear() {
    lcd.clear();

    for (uint8_t r = 0; r < LCD_ROWS; r++) { // allineamento della copia locale, spazi in ogni riga
        memset(lines[r], ' ', LCD_COLS);
        lines[r][LCD_COLS] = '\0';
    }
}

void Display::printLine(uint8_t row, const char *text) {

    if (row >= LCD_ROWS || text == nullptr) {
        return; // parametri non validi
    }

    // costruisco la riga di LCD_COLS caratteri, tronco se di più e metto spazi se di meno
    char buffer[LCD_COLS + 1];
    uint8_t i = 0;
    while (i < LCD_COLS && text[i] != '\0') {
        buffer[i] = text[i];
        i++;
    }

    while (i < LCD_COLS) {
        buffer[i++] = ' ';
    }

    buffer[LCD_COLS] = '\0';

    // se la riga non è cambiata allora non scrivo nulla
    if (memcmp(buffer, lines[row], LCD_COLS + 1) == 0) {
        return;
    }

    // aggiornamento della copia e scrittura
    memcpy(lines[row], buffer, LCD_COLS + 1);
    lcd.setCursor(0, row);
    lcd.print(buffer);
}

void Display::backLightOn() { lcd.backlight(); }
void Display::backLightOff() { lcd.noBacklight(); }
