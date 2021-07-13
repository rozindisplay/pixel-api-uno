#ifndef PIXEL_CLIENT_WRITER
#define PIXEL_CLIENT_WRITER

#include "PixelClientLimit.h"

class PixelClientWriter {
public:
    void home(int address);
    void setLimitsAndHome(int address, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4);
    void setLimit(int address, char pixle, const PixelClientLimit& limit);
    void setSteps(int address, char pixle, int steps);
    void addSteps(int address, char pixle, int steps);
    void setAngle(int address, char pixle, double angle);
    void addAngle(int address, char pixle, double angle);
};

#endif