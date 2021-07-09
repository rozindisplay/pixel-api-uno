#ifndef PIXEL_CLIENT_WRITER
#define PIXEL_CLIENT_WRITER

#include "PixelClientLimit.h"

class PixelClientWriter {
public:
    void home();
    void setLimitsAndHome(const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4);
    void setLimit(char pixle, const PixelClientLimit& limit);
    void setSteps(char pixle, int steps);
    void addSteps(char pixle, int steps);
    void setAngle(char pixle, double angle);
    void addAngle(char pixle, double angle);
};

#endif