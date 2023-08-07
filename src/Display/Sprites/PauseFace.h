//
// Created by keyz_ on 07/08/2023.
//

#ifndef KNOMI_ALT_PAUSEFACE_H
#define KNOMI_ALT_PAUSEFACE_H


#include <Display/Sprites/tImage.h>


class PauseFace : tImage {
public:
    PauseFace() : tImage() {}

    uint16_t *getFrame(uint8_t) override;

    uint8_t width = 240;
    uint8_t height = 240;
    uint8_t frames = 1;
};

#endif //KNOMI_ALT_PAUSEFACE_H
