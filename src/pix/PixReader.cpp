#include "Wire.h"
#include <pix/PixReader.h>
#include <pix/PixConsts.h>
#include <pix/utils/StreamUtils.h>

bool PixReader::hasNext() {
    return Wire.available()!=0;
}

void PixReader::next(PixProcessor* processor) {
    if(!hasNext()) {
        return;
    }

    unsigned char opcode = Wire.read();

    switch(opcode) {
    case OP_INIT:
        opInit(processor);
        break;
    case OP_HOME:
        opHome(processor);
        break;
    case OP_CLEAR_ERROR_CODE:
        opClearErrorCode(processor);
        break;
    case OP_SET_LIMIT:
        opSetLimit(processor);
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
    default:
        // error: unknown opcode
        break;
    }
}

void PixReader::nextRequest(PixProcessor* processor) {
    switch (requestType) {
    case REQUEST_PING:
        rqPing(processor);
        break;
    case REQUEST_ERROR_CODE:
        rqErrorCode(processor);
        break;
    case REQUEST_MOVING_COUNT:
        rqMovingCount(processor);
        break;
    case REQUEST_STATUS:
        rqStatus(processor);
        break;
    default:
        // error: unknown request type
        break;
    }
}

unsigned char PixReader::getRequestType() {
    return requestType;
}

void PixReader::opInit(PixProcessor* processor) {
    const PixLimit limitP0 = nextLimit();
    const PixLimit limitP1 = nextLimit();
    const PixLimit limitP2 = nextLimit();
    const PixLimit limitP3 = nextLimit();

    processor->onInit(limitP0, limitP1, limitP2, limitP3);
}

void PixReader::opHome(PixProcessor* processor) {
    processor->onHome();
}

void PixReader::opClearErrorCode(PixProcessor* processor) {
    processor->onClearErrorCode();
}

void PixReader::opSetLimit(PixProcessor* processor) {
    const unsigned char pixle = readByte(Wire);
    const PixLimit limit = nextLimit();

    processor->onSetLimit(pixle, limit);
}

void PixReader::opSetSteps(PixProcessor* processor) {
    const unsigned char pixle = readByte(Wire);
    const int steps = readInt(Wire);

    processor->onSetSteps(pixle, steps);
}

void PixReader::opAddSteps(PixProcessor* processor) {
    const unsigned char pixle = readByte(Wire);
    const int steps = readInt(Wire);

    processor->onAddSteps(pixle, steps);
}

void PixReader::opSetAngle(PixProcessor* processor) {
    const unsigned char pixle = readByte(Wire);
    const double angle = readDouble(Wire);

    processor->onSetAngle(pixle, angle);
}

void PixReader::opAddAngle(PixProcessor* processor) {
    const unsigned char pixle = readByte(Wire);
    const double angle = readDouble(Wire);

    processor->onAddAngle(pixle, angle);
}

void PixReader::opSetRequestType(PixProcessor* processor) {
    const unsigned char type = readByte(Wire);
    this->requestType = type;
}

void PixReader::rqPing(PixProcessor* processor) {
    processor->requestPing();
    writeByte(REQUEST_PING, Wire);

    // total = 1 bytes
}

void PixReader::rqErrorCode(PixProcessor* processor) {
    int errorCode = processor->requestErrorCode();
    writeByte(REQUEST_ERROR_CODE, Wire);
    writeInt(errorCode, Wire);

    // total = 3 bytes
}

void PixReader::rqMovingCount(PixProcessor* processor) {
    unsigned char count = processor->requestMovingCount();
    writeByte(REQUEST_MOVING_COUNT, Wire);
    writeByte(count, Wire);

    // total = 2 bytes
}

void PixReader::rqStatus(PixProcessor* processor) {
    PixStatusSet statuses = processor->requestStatus();
    
    // 1 byte
    writeByte(REQUEST_STATUS, Wire);
    
    // 2 bytes
    writeInt(statuses.error, Wire);

    const int size = statuses.size();
    for(int i=0; i<size; i++) {
        const PixStatus *status = statuses[i];

        // 4 * 1 bytes = 4 bytes
        writeByte(status->moving? 1 : 0, Wire);

        // 4 * 2 bytes = 8 bytes
        writeInt(status->target, Wire);
        
        // 4 * 2 bytes = 8 bytes
        writeInt(status->steps, Wire);

        // 4 * 4 bytes = 16 bytes
        writeDouble(status->angle, Wire);

        // 4 * 4 bytes = 16 bytes
        writeLimit(status->limit);
    }

    // total = 55 bytes
}

PixLimit PixReader::nextLimit() {
    const int lower = readInt(Wire);
    const int upper = readInt(Wire);
    return PixLimit(lower, upper);    
}

void PixReader::writeLimit(const PixLimit& limit) {
    writeInt(limit.lower, Wire);
    writeInt(limit.upper, Wire);

    // total = 4 bytes
}
