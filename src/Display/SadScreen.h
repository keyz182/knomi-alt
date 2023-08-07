//
// Created by keyz_ on 06/08/2023.
//

#ifndef KNOMI_ALT_SADSCREEN_H
#define KNOMI_ALT_SADSCREEN_H

#include "Display/Screen.h"
#include "Display/Sprites/SadFace.h"

class SadScreen : public Screen {
public:
    explicit SadScreen(TFT_eSPI *);

    void tick();

private:
    SadFace face = SadFace();
};


#endif //KNOMI_ALT_SADSCREEN_H
