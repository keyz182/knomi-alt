//
// Created by keyz_ on 06/08/2023.
//

#include "Display.hpp"

void Display::display_Init() {
    // Init display and TFT lib
    tft = new TFT_eSPI(240, 240);
    tft->init();
    tft->setRotation(0);
    tft->fillScreen(TFT_BLACK);
    tft->setSwapBytes(true);

    // Init display LEDs
    pinMode(16, OUTPUT);
    digitalWrite(16, HIGH);

    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
}

void Display::tick() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= displayInterval) {
        previousMillis = currentMillis;
        if (screen != nullptr) {
            screen->tick();
        }
    } else {
        delay(displayInterval / 10);
    }

}

void Display::setScreen(Screen *_scr) {
    if(screen != _scr){
        tft->fillScreen(TFT_BLACK);
        screen = _scr;
    }
}

void Display::setInterval(unsigned long interval) {
    displayInterval = interval;
}