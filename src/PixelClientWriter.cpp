#include "Wire.h"
#include "PixelClientWriter.h"
#include "PixelClientConsts.h"
#include <utils/StreamUtils.h>

void PixelClientWriter::home(int address) {
    Wire.beginTransmission(address);
    writeByte(OP_HOME, Wire); 
    Wire.endTransmission();
}
void PixelClientWriter::setLimitsAndHome(int address, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) {
    Wire.beginTransmission(address);
    
    writeByte(OP_SET_LIMITS_AND_HOME, Wire);
    
    writeInt(limitP1.lower, Wire);
    writeInt(limitP1.upper, Wire);

    writeInt(limitP2.lower, Wire);
    writeInt(limitP2.upper, Wire);

    writeInt(limitP3.lower, Wire);
    writeInt(limitP3.upper, Wire);

    writeInt(limitP4.lower, Wire);
    writeInt(limitP4.upper, Wire);

    Wire.endTransmission();
}

void PixelClientWriter::setLimit(int address, char pixle, const PixelClientLimit& limit) {
    Wire.beginTransmission(address);
    
    writeByte(OP_SET_LIMITS, Wire);
    
    writeByte(pixle, Wire);

    writeInt(limit.lower, Wire);
    writeInt(limit.upper, Wire);

    Wire.endTransmission();
}

void PixelClientWriter::setSteps(int address, char pixle, int steps) {
    Wire.beginTransmission(address);
    
    writeByte(OP_SET_STEPS, Wire);
    writeByte(pixle, Wire);
    writeInt(steps, Wire);

    Wire.endTransmission();
}

void PixelClientWriter::addSteps(int address, char pixle, int steps) {
    Wire.beginTransmission(address);

    writeByte(OP_ADD_STEPS, Wire);
    writeByte(pixle, Wire);
    writeInt(steps, Wire);

    Wire.endTransmission();
}

void PixelClientWriter::setAngle(int address, char pixle, double angle) {
    Wire.beginTransmission(address);
    
    writeByte(OP_SET_ANGLE, Wire);
    writeByte(pixle, Wire);
    writeDouble(angle, Wire);

    Wire.endTransmission();
}

void PixelClientWriter::addAngle(int address, char pixle, double angle) {
    Wire.beginTransmission(address);
    
    writeByte(OP_ADD_ANGLE, Wire);
    writeByte(pixle, Wire);
    writeDouble(angle, Wire);

    Wire.endTransmission();
}
