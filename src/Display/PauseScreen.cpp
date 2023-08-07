//
// Created by keyz_ on 07/08/2023.
//

#include "PauseScreen.h"

PauseScreen::PauseScreen(TFT_eSPI *tft) : Screen(tft) {

}

void PauseScreen::tick() {
    tft->pushImage(0, 0, face.width, face.height, face.getFrame(0));
}