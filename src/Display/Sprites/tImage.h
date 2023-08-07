#include <stdint.h>
#include <pgmspace.h>

#ifndef KNOMI_ALT_TIMAGE_H
#define KNOMI_ALT_TIMAGE_H

class tImage {
protected:
    tImage() {};

    ~tImage() = default;

public:
    virtual uint16_t *getFrame(uint8_t) = 0;

    uint8_t frames;
    uint16_t width;
    uint16_t height;
};

#endif