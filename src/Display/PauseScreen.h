//
// Created by keyz_ on 07/08/2023.
//

#ifndef KNOMI_ALT_PAUSESCREEN_H
#define KNOMI_ALT_PAUSESCREEN_H

#include "Display/Screen.h"
#include "Display/Sprites/PauseFace.h"

class PauseScreen : public Screen {
public:
    explicit PauseScreen(TFT_eSPI *);

    void tick();

private:
    PauseFace face = PauseFace();
};


#endif //KNOMI_ALT_PAUSESCREEN_H
