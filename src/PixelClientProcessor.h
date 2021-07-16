#ifndef PIXEL_CLIENT_PROCESSOR
#define PIXEL_CLIENT_PROCESSOR

#include "PixelClientLimit.h"

class PixelClientProcessor {
public:
    virtual void onHome(unsigned char opcode) = 0;
    virtual void onSetLimitsAndHome(unsigned char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) = 0;
    virtual void onSetLimit(unsigned char opcode, unsigned char pixle, const PixelClientLimit& limit) = 0;
    virtual void onSetSteps(unsigned char opcode, unsigned char pixle, int steps) = 0;
    virtual void onAddSteps(unsigned char opcode, unsigned char pixle, int steps) = 0;
    virtual void onSetAngle(unsigned char opcode, unsigned char pixle, double angle) = 0;
    virtual void onAddAngle(unsigned char opcode, unsigned char pixle, double angle) = 0;
    virtual void onSetRequestType(unsigned char opcode, unsigned char requestType) = 0;
    virtual void ping() = 0;
};

#endif
