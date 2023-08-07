//
// Created by keyz_ on 06/08/2023.
//

#ifndef KNOMI_ALT_SCREEN_H
#define KNOMI_ALT_SCREEN_H

#include "TFT_eSPI.h"

class Screen {
protected:
    explicit Screen(TFT_eSPI *);

    virtual ~Screen() = 0;

    TFT_eSPI *tft;
public:
    virtual void tick() = 0;
};


#endif //KNOMI_ALT_SCREEN_H
