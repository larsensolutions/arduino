
#include <FastLED.h>
class Blend {
    public:
        CRGBPalette16 palette;
        TBlendType blend;
        Blend(CRGBPalette16 palette, TBlendType blend){
            this->palette = palette;
            this->blend = blend;
        }
};