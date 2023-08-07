//
// Created by keyz_ on 06/08/2023.
//

#include "SleepyScreen.h"

SleepyScreen::SleepyScreen(TFT_eSPI *tft) : Screen(tft) {

}

void SleepyScreen::tick() {
    if (idx < 0) {
        idx = 0;
    } else {
        idx = (idx + 1) % face.frames;
    }

    tft->pushImage(0, 0, face.width, face.height, face.getFrame(idx));
}
