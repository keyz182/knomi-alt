//
// Created by keyz_ on 07/08/2023.
//

#include "NoWiFiScreen.h"

NoWiFiScreen::NoWiFiScreen(TFT_eSPI *tft) : Screen(tft) {

}

void NoWiFiScreen::tick() {
    tft->pushImage(0, 0, face.width, face.height, face.getFrame(0));
}