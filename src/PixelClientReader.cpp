
#include "Wire.h"
#include "PixelClientReader.h"
#include "PixelClientConsts.h"
#include <utils/StreamUtils.h>

bool PixelClientReader::hasNext() {
    return Wire.available()!=0;
}

void PixelClientReader::next(PixelClientProcessor* processor) {
    if(!hasNext()) {
        return;
    }

    unsigned char opcode = Wire.read();

    switch(opcode) {
    case OP_HOME:
        opHome(processor);
        break;
    case OP_SET_LIMITS:
        opSetLimits(processor);
        break;
    case OP_SET_LIMITS_AND_HOME:
        opSetLimitsAndHome(processor);
        break;
    case OP_SET_STEPS:
        opSetSteps(processor);
        break;
    case OP_ADD_STEPS:
        opAddSteps(processor);
        break;
    case OP_SET_ANGLE:
        opSetAngle(processor);
        break;
    case OP_ADD_ANGLE:
        opAddAngle(processor);
        break;
    case OP_REQUEST_TYPE:
        opSetRequestType(processor);
        break;
    }
}

void PixelClientReader::nextRequest(PixelClientProcessor* processor) {
    switch (requestType) {
    case REQUEST_PING:
        rqPing(processor);
        break;
    default:
        // error: unknown request type
        break;
    }
}

unsigned char PixelClientReader::getRequestType() {
    return requestType;
}

void PixelClientReader::opHome(PixelClientProcessor* processor) {
    processor->onHome(OP_HOME);
}

void PixelClientReader::opSetLimits(PixelClientProcessor* processor) {
    const unsigned char pixle = readByte(Wire);
    const PixelClientLimit limit = nextLimit();

    processor->onSetLimit(OP_SET_LIMITS, pixle, limit);
}

void PixelClientReader::opSetLimitsAndHome(PixelClientProcessor* processor) {
    const PixelClientLimit limitP1 = nextLimit();
    const PixelClientLimit limitP2 = nextLimit();
    const PixelClientLimit limitP3 = nextLimit();
    const PixelClientLimit limitP4 = nextLimit();

    processor->onSetLimitsAndHome(OP_SET_LIMITS_AND_HOME, limitP1, limitP2, limitP3, limitP4);
}

void PixelClientReader::opSetSteps(PixelClientProcessor* processor) {
    const unsigned char pixle = readByte(Wire);
    const int steps = readInt(Wire);

    processor->onSetSteps(OP_SET_STEPS, pixle, steps);
}

void PixelClientReader::opAddSteps(PixelClientProcessor* processor) {
    const unsigned char pixle = readByte(Wire);
    const int steps = readInt(Wire);

    processor->onAddSteps(OP_ADD_STEPS, pixle, steps);
}

void PixelClientReader::opSetAngle(PixelClientProcessor* processor) {
    const unsigned char pixle = readByte(Wire);
    const double angle = readDouble(Wire);

    processor->onSetAngle(OP_SET_ANGLE, pixle, angle);
}

void PixelClientReader::opAddAngle(PixelClientProcessor* processor) {
    const unsigned char pixle = readByte(Wire);
    const double angle = readDouble(Wire);

    processor->onAddAngle(OP_ADD_ANGLE, pixle, angle);
}

void PixelClientReader::opSetRequestType(PixelClientProcessor* processor) {
    const unsigned char type = readByte(Wire);
    this->requestType = type;

    processor->onSetRequestType(OP_REQUEST_TYPE, type);
}

void PixelClientReader::rqPing(PixelClientProcessor* processor) {
    processor->requestPing();
    writeByte(REQUEST_PING, Wire);
}

void PixelClientReader::rqError(PixelClientProcessor* processor) {
    int errorCode = processor->requestError();
    writeByte(REQUEST_ERROR, Wire);
    writeInt(errorCode, Wire);
}

PixelClientLimit PixelClientReader::nextLimit() {
    const int lower = readInt(Wire);
    const int upper = readInt(Wire);
    return PixelClientLimit(lower, upper);    
}
