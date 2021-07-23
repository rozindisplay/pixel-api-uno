#include "Wire.h"
#include <pix/PixWriter.h>
#include <pix/PixConsts.h>
#include <pix/utils/StreamUtils.h>

void PixWriter::init(unsigned char address, const PixLimit& limitP1, const PixLimit& limitP2, const PixLimit& limitP3, const PixLimit& limitP4) {
    Wire.beginTransmission(address);
    
    writeByte(OP_INIT, Wire);
    
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

void PixWriter::home(unsigned char address) {
    Wire.beginTransmission(address);
    writeByte(OP_HOME, Wire); 
    Wire.endTransmission();
}

void PixWriter::clearErrorCode(unsigned char address) {
    Wire.beginTransmission(address);
    writeByte(OP_CLEAR_ERROR_CODE, Wire); 
    Wire.endTransmission();
}

void PixWriter::setLimit(unsigned char address, unsigned char pixle, const PixLimit& limit) {
    Wire.beginTransmission(address);
    
    writeByte(OP_SET_LIMIT, Wire);
    
    writeByte(pixle, Wire);

    writeInt(limit.lower, Wire);
    writeInt(limit.upper, Wire);

    Wire.endTransmission();
}

void PixWriter::setSteps(unsigned char address, unsigned char pixle, int steps) {
    Wire.beginTransmission(address);
    
    writeByte(OP_SET_STEPS, Wire);
    writeByte(pixle, Wire);
    writeInt(steps, Wire);

    Wire.endTransmission();
}

void PixWriter::addSteps(unsigned char address, unsigned char pixle, int steps) {
    Wire.beginTransmission(address);

    writeByte(OP_ADD_STEPS, Wire);
    writeByte(pixle, Wire);
    writeInt(steps, Wire);

    Wire.endTransmission();
}

void PixWriter::setAngle(unsigned char address, unsigned char pixle, double angle) {
    Wire.beginTransmission(address);
    
    writeByte(OP_SET_ANGLE, Wire);
    writeByte(pixle, Wire);
    writeDouble(angle, Wire);

    Wire.endTransmission();
}

void PixWriter::addAngle(unsigned char address, unsigned char pixle, double angle) {
    Wire.beginTransmission(address);
    
    writeByte(OP_ADD_ANGLE, Wire);
    writeByte(pixle, Wire);
    writeDouble(angle, Wire);

    Wire.endTransmission();
}

bool PixWriter::requestPing(unsigned char address) {
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

int PixWriter::requestErrorCode(unsigned char address) {
    Wire.beginTransmission(address);
    writeByte(OP_REQUEST_TYPE, Wire);
    writeByte(REQUEST_ERROR_CODE, Wire);
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
    
    if(type!=REQUEST_ERROR_CODE) {
        // error: wrong request type returned
        return -1;
    }

    return code;
}

unsigned char PixWriter::requestMovingCount(unsigned char address) {
    Wire.beginTransmission(address);
    writeByte(OP_REQUEST_TYPE, Wire);
    writeByte(REQUEST_MOVING_COUNT, Wire);
    Wire.endTransmission();

    // 1 byte = request type
    // 1 byte = moving count
    uint8_t requestBytes = 2;
    uint8_t bytes = Wire.requestFrom(address, requestBytes);
    if(requestBytes != bytes) {
        // error: wrong number of bytes
        return -1;
    }

    unsigned char type = readByte(Wire);
    unsigned char count = readByte(Wire);

    if(type!=REQUEST_MOVING_COUNT) {
        // error: wrong request type returned
        return -1;
    }

    return count;
}

const PixStatusSet PixWriter::requestStatus(unsigned char address) {
    Wire.beginTransmission(address);
    writeByte(OP_REQUEST_TYPE, Wire);
    writeByte(REQUEST_STATUS, Wire);
    Wire.endTransmission();

    // 1 byte = request type
    // 2 byte = error code
    // 4 * 1 byte = moving indicator for each pixel (4bytes)
    // 4 * 2 bytes = target position for each pixel (8bytes)
    // 4 * 2 bytes = current position for each pixel (8bytes)
    // 4 * 4 bytes = current angle for each pixel (16bytes)
    // 4 * 4 bytes = limit settings for each pixel (16bytes)
    // total = 55

    uint8_t requestBytes = 55;
    uint8_t bytes = Wire.requestFrom(address, requestBytes);
    if(requestBytes != bytes) {
        // error: wrong number of bytes
        throw -1;
    }

    unsigned char type = readByte(Wire);
    int errcode = readInt(Wire);

    PixStatus s0 = readStatus();
    PixStatus s1 = readStatus();
    PixStatus s2 = readStatus();
    PixStatus s3 = readStatus();

    PixStatusSet s = PixStatusSet(errcode, s0, s1, s2, s3);

    if(type!=REQUEST_STATUS) {
        // error: wrong request type returned
        throw -1;
    }

    return s;
}

PixLimit PixWriter::readLimit() {
    int lower = readInt(Wire);
    int upper = readInt(Wire);
    return PixLimit(lower, upper);
}

PixStatus PixWriter::readStatus() {
    bool moving = readByte(Wire) > 0;
    int target = readInt(Wire);
    int steps = readInt(Wire);
    double angle = readDouble(Wire);
    PixLimit limit = readLimit();

    return PixStatus(moving, target, steps, angle, limit);
}
