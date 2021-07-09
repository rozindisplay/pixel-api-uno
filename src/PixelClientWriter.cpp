#include "Wire.h"
#include "PixelClientWriter.h"
#include "PixelClientConsts.h"
#include <utils/StreamUtils.h>

void PixelClientWriter::home() {
    writeByte(OP_HOME, Wire); 
}
void PixelClientWriter::setLimitsAndHome(const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) {
    writeByte(OP_SET_LIMITS_AND_HOME, Wire);
    
    writeInt(limitP1.lower, Wire);
    writeInt(limitP1.upper, Wire);

    writeInt(limitP2.lower, Wire);
    writeInt(limitP2.upper, Wire);

    writeInt(limitP3.lower, Wire);
    writeInt(limitP3.upper, Wire);

    writeInt(limitP4.lower, Wire);
    writeInt(limitP4.upper, Wire);
}

void PixelClientWriter::setLimit(char pixle, const PixelClientLimit& limit) {
    writeByte(OP_SET_LIMITS, Wire);
    
    writeByte(pixle, Wire);

    writeInt(limit.lower, Wire);
    writeInt(limit.upper, Wire);
}

void PixelClientWriter::setSteps(char pixle, int steps) {
    writeByte(OP_SET_STEPS, Wire);
    writeByte(pixle, Wire);
    writeInt(steps, Wire);
}

void PixelClientWriter::addSteps(char pixle, int steps) {
    writeByte(OP_ADD_STEPS, Wire);
    writeByte(pixle, Wire);
    writeInt(steps, Wire);
}

void PixelClientWriter::setAngle(char pixle, double angle) {
    writeByte(OP_SET_ANGLE, Wire);
    writeByte(pixle, Wire);
    writeDouble(angle, Wire);
}

void PixelClientWriter::addAngle(char pixle, double angle) {
    writeByte(OP_ADD_ANGLE, Wire);
    writeByte(pixle, Wire);
    writeDouble(angle, Wire);
}
