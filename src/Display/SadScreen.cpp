//
// Created by keyz_ on 06/08/2023.
//

#include "SadScreen.h"

SadScreen::SadScreen(TFT_eSPI *tft) : Screen(tft) {

}

void SadScreen::tick() {
    tft->pushImage(0, 0, face.width, face.height, face.getFrame(0));
}