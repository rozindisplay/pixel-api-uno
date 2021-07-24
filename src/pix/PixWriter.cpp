#include "Wire.h"
#include <pix/PixWriter.h>
#include <pix/PixConsts.h>
#include <pix/utils/StreamUtils.h>

int PixWriter::init(unsigned char address, const Limit& limitP0, const Limit& limitP1, const Limit& limitP2, const Limit& limitP3) {
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

int PixWriter::setLimit(unsigned char address, unsigned char pixle, const Limit& limit) {
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
    int err = sendRequestType(address, REQUEST_PING);
    if(err!=0) {
        return err;
    }

    uint8_t bytes = Wire.requestFrom(address, (uint8_t)1);
    
    if(1 != bytes) {
        // error: wrong number of bytes
        return ERROR_REQUEST_WRONG_NUMBER_OF_BYTES;
    }

    unsigned char type;
    err = readByte(Wire, type);
    if(err!=0) {
        return err;
    }

    if(type!=REQUEST_PING) {
        // error: wrong request type returned
        return ERROR_REQUEST_WRONG_TYPE;
    }

    return 0;
}

int PixWriter::requestErrorCode(unsigned char address, int& errorCode) {
    int err = sendRequestType(address, REQUEST_ERROR_CODE);
    if(err!=0) {
        return err;
    }

    // 1 byte = request type
    // 2 bytes = error code (int)
    uint8_t requestBytes = 3;
    uint8_t bytes = Wire.requestFrom(address, requestBytes);
    if(requestBytes != bytes) {
        // error: wrong number of bytes
        return ERROR_REQUEST_WRONG_NUMBER_OF_BYTES;
    }

    unsigned char type;
    err = readByte(Wire, type);
    if(err!=0) {
        return err;
    }
    
    if(type!=REQUEST_ERROR_CODE) {
        // error: wrong request type returned
        return ERROR_REQUEST_WRONG_TYPE;
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
    int err = sendRequestType(address, REQUEST_MOVING_COUNT);
    if(err!=0) {
        return err;
    }

    // 1 byte = request type
    // 1 byte = moving count
    uint8_t requestBytes = 2;
    uint8_t bytes = Wire.requestFrom(address, requestBytes);
    if(requestBytes != bytes) {
        // error: wrong number of bytes
        return ERROR_REQUEST_WRONG_NUMBER_OF_BYTES;
    }

    unsigned char type;
    err = readByte(Wire, type);
    if(err!=0) {
        return err;
    }

    if(type!=REQUEST_MOVING_COUNT) {
        // error: wrong request type returned
        return ERROR_REQUEST_WRONG_TYPE;
    }

    unsigned char count;
    err = readByte(Wire, count);
    if(err!=0) {
        return err;
    }

    movingCount = count;
    return 0;
}

int PixWriter::requestStatus(unsigned char address, NodeStatus& status) {
    int err = sendRequestType(address, REQUEST_STATUS);
    if(err!=0) {
        return err;
    }

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
        return ERROR_REQUEST_WRONG_NUMBER_OF_BYTES;
    }

    unsigned char type;
    err = readByte(Wire, type);
    if(err!=0) {
        return err;
    }

    if(type!=REQUEST_STATUS) {
        // error: wrong request type returned
        return ERROR_REQUEST_WRONG_TYPE;
    }

    int errcode;
    err = readInt(Wire, errcode);

    status.error = errcode;
    err = readStatus(status[0]);
    if(err!=0) {
        return err;
    }
    err = readStatus(status[1]);
    if(err!=0) {
        return err;
    }
    err = readStatus(status[2]);
    if(err!=0) {
        return err;
    }
    err = readStatus(status[3]);
    if(err!=0) {
        return err;
    }

    return 0;
}

int PixWriter::readLimit(Limit& limit) {
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
    
    limit = Limit(lower, upper);
    return 0;
}

int PixWriter::readStatus(PixelStatus& status) {
    int err;
    
    char movingCh;
    err = readByte(Wire, movingCh);
    if(err!=0) {
        return err;
    }
    bool moving = movingCh >0;

    int target;
    err = readInt(Wire, target);
    if(err!=0) {
        return err;
    }

    int steps;
    err = readInt(Wire, steps);
    if(err!=0) {
        return err;
    }
    
    double angle;
    err = readDouble(Wire, angle);
    if(err!=0) {
        return err;
    }

    Limit limit;
    err = readLimit(limit);
    if(err!=0) {
        return err;
    }

    status = PixelStatus(moving, target, steps, angle, limit);
}

int PixWriter::sendRequestType(unsigned char address, unsigned char type) {
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
