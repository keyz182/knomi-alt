//
// Created by keyz_ on 07/08/2023.
//

#ifndef KNOMI_ALT_HOTENDTEMPSCREEN_H
#define KNOMI_ALT_HOTENDTEMPSCREEN_H

#include "Display/Screen.h"
#include "API.h"
#include <TFT_eWidget.h>

class HotendTempScreen : public Screen {
public:
    explicit HotendTempScreen(TFT_eSPI *, API *);

    void tick();
private:
    API *api;
    TFT_eSprite *sprite;
    GraphWidget *gr;
    TraceWidget *t1;
    TraceWidget *t2;
};


#endif //KNOMI_ALT_HOTENDTEMPSCREEN_H
