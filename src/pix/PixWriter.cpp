#include "Arduino.h"
#include "Wire.h"
#include <pix/PixWriter.h>
#include <pix/PixConsts.h>
#include <pix/utils/StreamUtils.h>

int PixWriter::init(unsigned char address, const PixLimit& limitP0, const PixLimit& limitP1, const PixLimit& limitP2, const PixLimit& limitP3) {
    int err;
    Wire.beginTransmission(address);
    
    err = writeByte(OP_INIT, Wire);
    if(err!=0) {
        return err;
    }
    
    // limit 0
    err = writeInt(limitP0.lower, Wire);
    if(err!=0) {
        return err;
    }
    err = writeInt(limitP0.upper, Wire);
    if(err!=0) {
        return err;
    }

    // limit 1
    err = writeInt(limitP1.lower, Wire);
    if(err!=0) {
        return err;
    }
    err = writeInt(limitP1.upper, Wire);
    if(err!=0) {
        return err;
    }

    // limit 2
    err = writeInt(limitP2.lower, Wire);
    if(err!=0) {
        return err;
    }
    err = writeInt(limitP2.upper, Wire);
    if(err!=0) {
        return err;
    }

    // limit 3
    err = writeInt(limitP3.lower, Wire);
    if(err!=0) {
        return err;
    }
    err = writeInt(limitP3.upper, Wire);
    if(err!=0) {
        return err;
    }

    return toPixCode(Wire.endTransmission());
}

int PixWriter::home(unsigned char address) {
    Wire.beginTransmission(address);
    
    int err = writeByte(OP_HOME, Wire);
    if(err!=0) {
        return err;
    }
    
    return toPixCode(Wire.endTransmission());
}

int PixWriter::clearErrorCode(unsigned char address) {
    Wire.beginTransmission(address);
    
    int err = writeByte(OP_CLEAR_ERROR_CODE, Wire);
    if(err!=0) {
        return err;
    }
    
    return toPixCode(Wire.endTransmission());
}

int PixWriter::setLimit(unsigned char address, unsigned char pixle, const PixLimit& limit) {
    int err;

    Wire.beginTransmission(address);
    
    err = writeByte(OP_SET_LIMIT, Wire);
    if(err!=0) {return err;}
    
    err = writeByte(pixle, Wire);
    if(err!=0) {return err;}

    err = writeInt(limit.lower, Wire);
    if(err!=0) {return err;}

    err = writeInt(limit.upper, Wire);
    if(err!=0) {return err;}

    return toPixCode(Wire.endTransmission());
}

int PixWriter::setSteps(unsigned char address, unsigned char pixle, int steps) {
    int err;
    
    Wire.beginTransmission(address);
    
    err = writeByte(OP_SET_STEPS, Wire);
    if(err!=0) {return err;}
    
    err = writeByte(pixle, Wire);
    if(err!=0) {return err;}
    
    err = writeInt(steps, Wire);
    if(err!=0) {return err;}

    return toPixCode(Wire.endTransmission());
}

int PixWriter::addSteps(unsigned char address, unsigned char pixle, int steps) {
    int err;
    Wire.beginTransmission(address);

    err = writeByte(OP_ADD_STEPS, Wire);
    if(err!=0) {return err;}

    err = writeByte(pixle, Wire);
    if(err!=0) {return err;}

    err = writeInt(steps, Wire);
    if(err!=0) {return err;}

    return toPixCode(Wire.endTransmission());
}

int PixWriter::setAngle(unsigned char address, unsigned char pixle, double angle) {
    int err;
    Wire.beginTransmission(address);
    
    err = writeByte(OP_SET_ANGLE, Wire);
    if(err!=0) {return err;}

    err = writeByte(pixle, Wire);
    if(err!=0) {return err;}
    
    err = writeDouble(angle, Wire);
    if(err!=0) {return err;}

    return toPixCode(Wire.endTransmission());
}

int PixWriter::addAngle(unsigned char address, unsigned char pixle, double angle) {
    int err;
    Wire.beginTransmission(address);
    
    err = writeByte(OP_ADD_ANGLE, Wire);
    if(err!=0) {return err;}
    
    err = writeByte(pixle, Wire);
    if(err!=0) {return err;}

    err = writeDouble(angle, Wire);
    if(err!=0) {return err;}

    Wire.endTransmission();

    return 0;
}

int PixWriter::requestPing(unsigned char address) {
    return initRequest(address, REQUEST_MOVING_COUNT, -1, 0);
}

int PixWriter::requestErrorCode(unsigned char address, int& errorCode) {
    // 2 bytes (int)
    int err = initRequest(address, REQUEST_MOVING_COUNT, -1, 2);
    if(err!=0) {
        return err;
    }

    int code;
    err = readInt(Wire,code);
    if(err!=0) {
        return err;
    }

    errorCode = code;
    return 0;
}

int PixWriter::requestMovingCount(unsigned char address, unsigned char& movingCount) {
    // 1 byte = moving count
    int err = initRequest(address, REQUEST_MOVING_COUNT, -1, 1);
    if(err!=0) {
        return err;
    }

    unsigned char count;
    err = readByte(Wire, count);
    if(err!=0) {
        return err;
    }

    movingCount = count;
    return 0;
}

int PixWriter::requestStatus(unsigned char address, unsigned char pixel, PixStatus& status) {
    // 1 byte = moving indicator for each pixel
    // 2 bytes = target position for each pixel
    // 2 bytes = current position for each pixel
    // 4 bytes = current angle for each pixel
    // 4 bytes = limit settings for each pixel
    // total = 13
    int err = initRequest(address, REQUEST_MOVING_COUNT, pixel, 13);

    // 1 byte
    char movingCh;
    err = readByte(Wire, movingCh);
    if(err!=0) {
        return err;
    }
    bool moving = movingCh > 0;

    // 2 bytes
    int target;
    err = readInt(Wire, target);
    if(err!=0) {
        return err;
    }

    // 2 bytes
    int steps;
    err = readInt(Wire, steps);
    if(err!=0) {
        return err;
    }
    
    // 4 bytes
    double angle;
    err = readDouble(Wire, angle);
    if(err!=0) {
        return err;
    }

    // 4 bytes
    PixLimit limit;
    err = readLimit(limit);
    if(err!=0) {
        return err;
    }

    status = PixStatus(moving, target, steps, angle, limit);
    return 0;
}

int PixWriter::readLimit(PixLimit& limit) {
    int err;

    int lower;
    err = readInt(Wire, lower);
    if(err!=0) {
        return err;
    }

    int upper;
    err = readInt(Wire, err);
    if(err!=0) {
        return err;
    }
    
    limit = PixLimit(lower, upper);
    return 0;
}

int PixWriter::initRequest(unsigned char address, unsigned char type, unsigned char pixel, unsigned char bytes) {
    // 1 byte request type
    // 1 byte pixel argument
    // total = 2 + requested bytes
    uint8_t totalBytes = bytes + 2;
    
    int err;    

    sendRequestType(address, type, pixel);
    
    uint8_t responseBytes = Wire.requestFrom(address, totalBytes);

    if(responseBytes != totalBytes) {
        // error: wrong number of bytes
        return ERROR_REQUEST_WRONG_NUMBER_OF_BYTES;
    }

    unsigned char responseType;
    err = readByte(Wire, responseType);
    if(err!=0) {
        return err;
    }

    if(responseType!=type) {
        // error: wrong request type returned
        return ERROR_REQUEST_WRONG_TYPE;
    }

    unsigned char responsePixel;
    err = readByte(Wire, responsePixel);
    if(err!=0) {
        return err;
    }

    if(responsePixel!=pixel) {
        // error: wrong arg
        return ERROR_REQUEST_WRONG_PIXEL;
    }

    return 0;
}

int PixWriter::sendRequestType(unsigned char address, unsigned char type, unsigned char pixel) {
    int err;
    
    Wire.beginTransmission(address);
    
    err = writeByte(OP_REQUEST_TYPE, Wire);
    if(err!=0) {
        return err;
    }
    
    err = writeByte(type, Wire);
    if(err!=0) {
        return err;
    }

    err = writeByte(pixel, Wire);
    if(err!=0) {
        return err;
    }

    return toPixCode(Wire.endTransmission());
}

int PixWriter::toPixCode(int transmissionCode) {
    // Transmission Error Codes
    // 0 .. success
    // 1 .. length to long for buffer
    // 2 .. address send, NACK received
    // 3 .. data send, NACK received
    // 4 .. other twi error (lost bus arbitration, bus error, ..)
    // 5 .. timeout

    return transmissionCode==0 ? 0 : ERROR_WIRE_LENGTH_TO_LONG_FOR_BUFFER + transmissionCode -1;
}
