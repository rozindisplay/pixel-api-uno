#ifndef PIXEL_CLIENT_READER
#define PIXEL_CLIENT_READER

#include "PixelClientProcessor.h"

class PixelClientReader {
public:
    bool hasNext();
    void next(PixelClientProcessor*);
private:
    void opHome(PixelClientProcessor*);
    void opSetLimits(PixelClientProcessor*);
    void opSetLimitsAndHome(PixelClientProcessor*);
    void opSetSteps(PixelClientProcessor*);
    void opAddSteps(PixelClientProcessor*);
    void opSetAngle(PixelClientProcessor*);
    void opAddAngle(PixelClientProcessor*);

    PixelClientLimit nextLimit();
};

#endif