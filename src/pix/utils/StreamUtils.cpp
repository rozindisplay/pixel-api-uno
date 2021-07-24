#ifndef PIXEL_CLIENT_UTILS_STREAMS
#define PIXEL_CLIENT_UTILS_STREAMS

#include "StreamUtils.h"
#include "BytesUtils.h"

#include <pix/PixConsts.h>

int readByte(Stream& stream, char& value) {
    value = stream.read();
    if(value == -1) {
        return ERROR_WIRE_FAILED_TO_READ;
    }

    return 0;
}

int readByte(Stream& stream, unsigned char& value) {
    value = stream.read();
    if(value == -1) {
        return ERROR_WIRE_FAILED_TO_READ;
    }

    return 0;
}

int writeByte(char value, Stream& stream) {
    size_t count = stream.write(value);
    if(count != 1) {
        return ERROR_WIRE_FAILED_TO_WRITE;
    }

    return 0;
}

int readInt(Stream& stream, int& value) {
    size_t numBytes = 2;
    char bytes[numBytes];
    
    if(!stream.readBytes(bytes, numBytes)) {
        return ERROR_WIRE_FAILED_TO_READ;
    }

   value = asInt(bytes);
   return 0;
}

int writeInt(int value, Stream& stream) {
    char bytes[2];
    asBytes(value, bytes);

    size_t count = stream.write(bytes,2);
    if(count != 2) {
        return ERROR_WIRE_FAILED_TO_WRITE;
    }

    return 0;
}

int readDouble(Stream& stream, double& value) {
    char bytes[4];
    size_t count = stream.readBytes(bytes, 4);
    if(count!=4) {
        return ERROR_WIRE_FAILED_TO_READ;
    }

    value = asDouble(bytes);
    return 0;
}

int writeDouble(double value, Stream& stream) {
    char bytes[4];
    asBytes(value, bytes);

    size_t count = stream.write(bytes, 4);
    if(count!=4) {
        return ERROR_WIRE_FAILED_TO_WRITE;
    }
    return 0;
}

#endif
