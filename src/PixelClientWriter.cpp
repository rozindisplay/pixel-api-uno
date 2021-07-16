#include "Wire.h"
#include "PixelClientWriter.h"
#include "PixelClientConsts.h"
#include <utils/StreamUtils.h>

void PixelClientWriter::home(unsigned char address) {
    Wire.beginTransmission(address);
    writeByte(OP_HOME, Wire); 
    Wire.endTransmission();
}
void PixelClientWriter::setLimitsAndHome(unsigned char address, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) {
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

void PixelClientWriter::setLimit(unsigned char address, unsigned char pixle, const PixelClientLimit& limit) {
    Wire.beginTransmission(address);
    
    writeByte(OP_SET_LIMITS, Wire);
    
    writeByte(pixle, Wire);

    writeInt(limit.lower, Wire);
    writeInt(limit.upper, Wire);

    Wire.endTransmission();
}

void PixelClientWriter::setSteps(unsigned char address, unsigned char pixle, int steps) {
    Wire.beginTransmission(address);
    
    writeByte(OP_SET_STEPS, Wire);
    writeByte(pixle, Wire);
    writeInt(steps, Wire);

    Wire.endTransmission();
}

void PixelClientWriter::addSteps(unsigned char address, unsigned char pixle, int steps) {
    Wire.beginTransmission(address);

    writeByte(OP_ADD_STEPS, Wire);
    writeByte(pixle, Wire);
    writeInt(steps, Wire);

    Wire.endTransmission();
}

void PixelClientWriter::setAngle(unsigned char address, unsigned char pixle, double angle) {
    Wire.beginTransmission(address);
    
    writeByte(OP_SET_ANGLE, Wire);
    writeByte(pixle, Wire);
    writeDouble(angle, Wire);

    Wire.endTransmission();
}

void PixelClientWriter::addAngle(unsigned char address, unsigned char pixle, double angle) {
    Wire.beginTransmission(address);
    
    writeByte(OP_ADD_ANGLE, Wire);
    writeByte(pixle, Wire);
    writeDouble(angle, Wire);

    Wire.endTransmission();
}

bool PixelClientWriter::requestPing(unsigned char address) {
    Wire.beginTransmission(address);
    writeByte(OP_REQUEST_TYPE, Wire);
    writeByte(REQUEST_PING, Wire);
    Wire.endTransmission();

    uint8_t bytes = Wire.requestFrom(address, (uint8_t)1);
    unsigned char type;
    for(uint8_t i=0; i<bytes; i++) {
        type = readByte(Wire);
    }
    
    if(1 != bytes) {
        // error: wrong number of bytes
        return false;
    }
    if(type!=REQUEST_PING) {
        // error: wrong request type returned
        return false;
    }

    return true;
}

int PixelClientWriter::requestError(unsigned char address) {
    Wire.beginTransmission(address);
    writeByte(OP_REQUEST_TYPE, Wire);
    writeByte(REQUEST_ERROR, Wire);
    Wire.endTransmission();

    // 1 byte = request type
    // 2 bytes = error code (int)
    uint8_t requestBytes = 3;
    uint8_t bytes = Wire.requestFrom(address, requestBytes);
    if(requestBytes != bytes) {
        // error: wrong number of bytes
        return -1;
    }

    unsigned char type = readByte(Wire);
    int code = readInt(Wire);
    
    if(type!=REQUEST_ERROR) {
        // error: wrong request type returned
        return -1;
    }

    return code;
}
