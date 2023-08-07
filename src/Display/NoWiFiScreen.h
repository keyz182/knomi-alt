//
// Created by keyz_ on 07/08/2023.
//

#ifndef KNOMI_ALT_NOWIFISCREEN_H
#define KNOMI_ALT_NOWIFISCREEN_H

#include "Display/Screen.h"
#include "Display/Sprites/NoWiFiFace.h"

class NoWiFiScreen : public Screen {
public:
    explicit NoWiFiScreen(TFT_eSPI *);

    void tick();

private:
    NoWiFiFace face = NoWiFiFace();
};


#endif //KNOMI_ALT_NOWIFISCREEN_H
