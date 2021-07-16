#ifndef PIXEL_CLIENT_READER
#define PIXEL_CLIENT_READER

#include "PixelClientProcessor.h"

class PixelClientReader {
public:
    bool hasNext();
    void next(PixelClientProcessor*);
    void nextRequest(PixelClientProcessor*);
    unsigned char getRequestType();
private:
    unsigned char requestType;

    void opHome(PixelClientProcessor*);
    void opSetLimits(PixelClientProcessor*);
    void opSetLimitsAndHome(PixelClientProcessor*);
    void opSetSteps(PixelClientProcessor*);
    void opAddSteps(PixelClientProcessor*);
    void opSetAngle(PixelClientProcessor*);
    void opAddAngle(PixelClientProcessor*);
    void opSetRequestType(PixelClientProcessor*);

    void rqPing(PixelClientProcessor*);
    void rqError(PixelClientProcessor*);

    PixelClientLimit nextLimit();
};

#endif
