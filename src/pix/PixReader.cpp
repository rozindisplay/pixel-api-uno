#include "Wire.h"
#include <pix/PixReader.h>
#include <pix/PixConsts.h>
#include <pix/utils/StreamUtils.h>

bool PixReader::hasNext() {
    return Wire.available()!=0;
}

int PixReader::next(PixProcessor* processor) {
    if(!hasNext()) {
        return ERROR_READER_DATA_NOT_AVAILABLE;
    }

    unsigned char opcode = Wire.read();

    switch(opcode) {
    case OP_HOME:
        return opHome(processor);
    case OP_HOME_ALL:
        return opHomeAll(processor);
    case OP_CLEAR_ERROR_CODE:
        return opClearErrorCode(processor);
    case OP_SET_LIMIT:
        return opSetLimit(processor);
    case OP_SET_STEPS:
        return opSetSteps(processor);
    case OP_ADD_STEPS:
        return opAddSteps(processor);
    case OP_SET_ANGLE:
        return opSetAngle(processor);
    case OP_ADD_ANGLE:
        return opAddAngle(processor);
    case OP_REQUEST_TYPE:
        return opSetRequestType(processor);
    default:
        return ERROR_READER_UNKNOWN_COMMAND;
    }
}

int PixReader::nextRequest(PixProcessor* processor) {
    switch (requestType) {
    case REQUEST_PING:
        return rqPing(processor);
    case REQUEST_PIXELS:
        return rqPixels(processor);
    case REQUEST_MOVING_COUNT:
        return rqMovingCount(processor);
    case REQUEST_IS_MOVING:
        return rqIsMoving(processor);
    case REQUEST_TARGET_STEPS:
        return rqTargetSteps(processor);
    case REQUEST_STEPS:
        return rqSteps(processor);
    case REQUEST_TARGET_ANGLE:
        return rqTargetAngle(processor);
    case REQUEST_ANGLE:
        return rqAngle(processor);
    case REQUEST_LIMIT:
        return rqLimit(processor);
    case REQUEST_STATUS:
        return rqStatus(processor);
    case REQUEST_ERROR_CODE:
        return rqErrorCode(processor);
    default:
        return ERROR_READER_UNKNOWN_REQUEST;
    }
}

unsigned char PixReader::getRequestType() {
    return requestType;
}

int PixReader::opHome(PixProcessor* processor) {
    int err;
    
    char pixle;
    err = readByte(Wire, pixle);
    if(0!=err) {return err;}

    processor->onHome(pixle);
    return 0;
}

int PixReader::opHomeAll(PixProcessor* processor) {
    processor->onHome();
    return 0;
}

int PixReader::opClearErrorCode(PixProcessor* processor) {
    processor->onClearErrorCode();
    return 0;
}

int PixReader::opSetLimit(PixProcessor* processor) {
    int err;
    
    char pixle;
    err = readByte(Wire, pixle);
    if(0!=err) {return err;}

    PixLimit limit;
    err = nextLimit(limit);
    if(0!=err) {return err;}

    processor->onSetLimit(pixle, limit);
    return 0;
}

int PixReader::opSetSteps(PixProcessor* processor) {
    int err;
    
    char pixle;
    err = readByte(Wire, pixle);
    if(0!=err) {return err;}
    
    int steps;
    err = readInt(Wire, steps);
    if(0!=err) {return err;}

    processor->onSetSteps(pixle, steps);
    return 0;
}

int PixReader::opAddSteps(PixProcessor* processor) {
    int err;
    
    unsigned char pixle;
    err = readByte(Wire, pixle);
    if(0!=err) {return err;}

    int steps;
    err = readInt(Wire, steps);
    if(0!=err) {return err;}

    processor->onAddSteps(pixle, steps);
    return 0;
}

int PixReader::opSetAngle(PixProcessor* processor) {
    int err;

    unsigned char pixle;
    err = readByte(Wire, pixle);
    if(0!=err) {return err;}

    double angle;
    err = readDouble(Wire, angle);
    if(0!=err) {return err;}

    processor->onSetAngle(pixle, angle);
    return 0;
}

int PixReader::opAddAngle(PixProcessor* processor) {
    int err;

    unsigned char pixle;
    err = readByte(Wire, pixle);
    if(0!=err) {return err;}

    double angle;
    err = readDouble(Wire, angle);
    if(0!=err) {return err;}

    processor->onAddAngle(pixle, angle);
    return 0;
}

int PixReader::opSetRequestType(PixProcessor* processor) {
    int err;

    unsigned char type;
    err = readByte(Wire, type);
    if(0!=err) {return err;}

    unsigned char pixel;
    err = readByte(Wire, pixel);
    if(0!=err) {return err;}

    this->requestType = type;
    this->requestPixel = pixel;

    return 0;
}

int PixReader::rqPing(PixProcessor* processor) {
    processor->requestPing();
    
    int err;

    // --== Header ==-- //
    err = writeHeader(REQUEST_PING);
    if(0!=err) {return err;}

    // total = 0 bytes + header

    return 0;
}

int PixReader::rqPixels(PixProcessor* processor) {
    unsigned char count = processor->requestPixels();

    int err;

    // --== Header ==-- //
    err = writeHeader(REQUEST_PIXELS);
    if(0!=err) {return err;}
    
    // --== Body ==-- //
    // 1 byte
    err = writeByte(count, Wire);
    if(0!=err) {return err;}

    // total = 1 byte + header

    return 0;
}

int PixReader::rqIsMoving(PixProcessor* processor) {
    int err;

    bool isMoving = processor->requestIsMoving(requestPixel);
    
    // --== Header ==-- //
    err = writeHeader(REQUEST_IS_MOVING);
    if(0!=err) {return err;}
    
    // --== Body ==-- //
    // 1 byte
    err = writeByte(isMoving ? 1 : 0, Wire);
    if(0!=err) {return err;}

    // total = 1 byte + header

    return 0;
}

int PixReader::rqMovingCount(PixProcessor* processor) {
    int err;

    unsigned char count = processor->requestMoving();
    
    // --== Header ==-- //
    err = writeHeader(REQUEST_MOVING_COUNT);
    if(0!=err) {return err;}
    
    // --== Body ==-- //
    // 1 byte
    err = writeByte(count, Wire);
    if(0!=err) {return err;}

    // total = 1 byte + header

    return 0;
}

int PixReader::rqTargetSteps(PixProcessor* processor) {
    int err;

    int steps = processor->requestTargetSteps(requestPixel);
    
    // --== Header ==-- //
    err = writeHeader(REQUEST_TARGET_STEPS);
    if(0!=err) {return err;}
    
    // --== Body ==-- //
    // 2 bytes
    err = writeInt(steps, Wire);
    if(0!=err) {return err;}

    // total = 2 bytes + header

    return 0;
}

int PixReader::rqSteps(PixProcessor* processor) {
    int err;

    int steps = processor->requestSteps(requestPixel);
    
    // --== Header ==-- //
    err = writeHeader(REQUEST_STEPS);
    if(0!=err) {return err;}
    
    // --== Body ==-- //
    // 2 bytes
    err = writeInt(steps, Wire);
    if(0!=err) {return err;}

    // total = 2 bytes + header

    return 0;
}

int PixReader::rqTargetAngle(PixProcessor* processor) {
    int err;

    double angle = processor->requestTargetAngle(requestPixel);
    
    // --== Header ==-- //
    err = writeHeader(REQUEST_TARGET_ANGLE);
    if(0!=err) {return err;}
    
    // --== Body ==-- //
    // 4 bytes
    err = writeDouble(angle, Wire);
    if(0!=err) {return err;}

    // total = 4 bytes + header

    return 0;
}

int PixReader::rqAngle(PixProcessor* processor) {
    int err;

    double angle = processor->requestAngle(requestPixel);
    
    // --== Header ==-- //
    err = writeHeader(REQUEST_ANGLE);
    if(0!=err) {return err;}
    
    // --== Body ==-- //
    // 4 bytes
    err = writeDouble(angle, Wire);
    if(0!=err) {return err;}

    // total = 4 bytes + header

    return 0;
}

int PixReader::rqLimit(PixProcessor* processor) {
    int err;

    PixLimit limit = processor->requestLimit(requestPixel);
    
    // --== Header ==-- //
    err = writeHeader(REQUEST_LIMIT);
    if(0!=err) {return err;}
    
    // --== Body ==-- //
    // 4 bytes
    err = writeLimit(limit);
    if(0!=err) {return err;}

    // total = 4 bytes + header

    return 0;
}

int PixReader::rqStatus(PixProcessor* processor) {
    int err;

    PixStatus status = processor->requestStatus(requestPixel);
    
    // --== Header ==-- //
    err = writeHeader(REQUEST_STATUS);
    if(0!=err) {return err;}
    
    // --== Body ==-- //
    // 1 byte
    err = writeByte(status.moving ? 1 : 0, Wire);
    if(0!=err) {return err;}

    // 2 bytes
    err = writeInt(status.target, Wire);
    if(0!=err) {return err;}

    // 2 bytes
    err = writeInt(status.steps, Wire);
    if(0!=err) {return err;}

    // 4 bytes
    err = writeDouble(status.angle, Wire);
    if(0!=err) {return err;}

    // 4 bytes
    err = writeLimit(status.limit);
    if(0!=err) {return err;}

    // total = 13 bytes + header

    return 0;
}

int PixReader::rqErrorCode(PixProcessor* processor) {
    // process error
    int err;
    
    // request error
    int errorCode = processor->requestErrorCode();
    
    // --== Header ==-- //
    err = writeHeader(REQUEST_ERROR_CODE);
    if(0!=err) {return err;}
    
    // --== Body ==-- //
    // write 2 bytes
    err = writeInt(errorCode, Wire);
    if(0!=err) {return err;}

    // total = 2 bytes + header
    
    return 0;
}

int PixReader::nextLimit(PixLimit& limit) {
    
    // 2 bytes
    int lower;
    int err = readInt(Wire, lower);
    if(err!=0) { return err; }

    // 2 bytes
    int upper;
    err = readInt(Wire, upper);
    if(err!=0) { return err; }
    
    // total = 4 bytes

    limit = PixLimit(lower, upper);
    return 0;
}

int PixReader::writeLimit(const PixLimit& limit) {
    
    // 2 bytes
    int err = writeInt(limit.lower, Wire);
    if(err!=0) { return err; }

    // 2 bytes
    err = writeInt(limit.upper, Wire);
    if(err!=0) { return err; }

    // total = 4 bytes

    return 0;
}

int PixReader::writeHeader(unsigned char rqCode) {
    int err;
    
    // --== Headers ==-- //
    // 1 byte : Type
    err = writeByte(rqCode, Wire);
    if(0!=err) {return err;}

    // 1 byte : Pixel Arg
    err = writeByte(requestPixel, Wire);
    if(0!=err) {return err;}

    // total = 2 bytes

    return 0;
}