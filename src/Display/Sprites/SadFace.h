#include <Display/Sprites/tImage.h>


class SadFace : tImage {
public:
    SadFace() : tImage() {}

    uint16_t *getFrame(uint8_t) override;

    uint8_t width = 240;
    uint8_t height = 240;
    uint8_t frames = 1;
};