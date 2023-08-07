//
// Created by keyz_ on 07/08/2023.
//

#include "HotendTempScreen.h"

HotendTempScreen::HotendTempScreen(TFT_eSPI *tft, API *_api): Screen(tft) {
    api = _api;
    sprite = new TFT_eSprite(tft);
}

void HotendTempScreen::tick() {
//    sprite->createSprite(240,240);
//    sprite->fillSprite(TFT_BLACK);
    tft->fillScreen(TFT_BLACK);
    tft->setTextColor(TFT_RED);
    tft->setTextSize(1);
    tft->setTextDatum(MC_DATUM);
    tft->fillRect(20, 110, 200, 20, TFT_RED);

    Serial.println("HotendTempScreen::tick");
    Serial.println((float)api->tooltemp);
    Serial.println((float)api->target_tooltemp);

    String temp = String(api->tooltemp) + "°C";
    String target_temp = String(api->target_tooltemp) + "°C";

    tft->drawString(temp, 120, 80,4);
    tft->drawString(target_temp, 120, 160,4);

//    sprite->pushSprite(0,0);
//    sprite->deleteSprite();
    delay(500);
}