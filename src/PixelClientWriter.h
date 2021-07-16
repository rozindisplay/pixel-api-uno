#ifndef PIXEL_CLIENT_WRITER
#define PIXEL_CLIENT_WRITER

#include "PixelClientLimit.h"

class PixelClientWriter {
public:
    void home(unsigned char address);
    void setLimitsAndHome(unsigned char address, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4);
    void setLimit(unsigned char address, unsigned char pixle, const PixelClientLimit& limit);
    void setSteps(unsigned char address, unsigned char pixle, int steps);
    void addSteps(unsigned char address, unsigned char pixle, int steps);
    void setAngle(unsigned char address, unsigned char pixle, double angle);
    void addAngle(unsigned char address, unsigned char pixle, double angle);
    bool requestPing(unsigned char address);
    int requestError(unsigned char address);
};

#endif
