//
// Created by keyz_ on 06/08/2023.
//

#ifndef KNOMI_ALT_SLEEPYSCREEN_H
#define KNOMI_ALT_SLEEPYSCREEN_H

#include "Display/Screen.h"
#include "Display/Sprites/SleepyFace.h"

class SleepyScreen : public Screen {
public:
    explicit SleepyScreen(TFT_eSPI *);

    void tick();

private:
    int8_t idx = -1;
    SleepyFace face = SleepyFace();
};

#endif //KNOMI_ALT_SLEEPYSCREEN_H
