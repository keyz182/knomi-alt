//
// Created by keyz_ on 06/08/2023.
//

#ifndef KNOMI_ALT_DISPLAY_HPP
#define KNOMI_ALT_DISPLAY_HPP

#include "TFT_eSPI.h"
#include "Display/Screen.h"

class Display {
public:
    void display_Init();

    void setScreen(Screen *);

    void tick();

    TFT_eSPI *tft;

    void setInterval(unsigned long);

private:
    Screen *screen;
    unsigned long previousMillis = 0;
    unsigned long displayInterval = 1000;
};


#endif //KNOMI_ALT_DISPLAY_HPP
