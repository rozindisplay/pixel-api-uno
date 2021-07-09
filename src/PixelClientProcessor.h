#ifndef PIXEL_CLIENT_PROCESSOR
#define PIXEL_CLIENT_PROCESSOR

#include "PixelClientLimit.h"

class PixelClientProcessor {
public:
    virtual void onHome(char opcode) = 0;
    virtual void onSetLimitsAndHome(char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) = 0;
    virtual void onSetLimit(char opcode, char pixle, const PixelClientLimit& limit) = 0;
    virtual void onSetSteps(char opcode, char pixle, int steps) = 0;
    virtual void onAddSteps(char opcode, char pixle, int steps) = 0;
    virtual void onSetAngle(char opcode, char pixle, double angle) = 0;
    virtual void onAddAngle(char opcode, char pixle, double angle) = 0;
};

#endif