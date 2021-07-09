#ifndef PIXEL_CLIENT_UTILS_STREAMS
#define PIXEL_CLIENT_UTILS_STREAMS

#include "StreamUtils.h"
#include "BytesUtils.h"

char readByte(Stream& stream) {
    return stream.read();
}

void writeByte(char value, Stream& stream) {
    stream.write(value);
}

int readInt(Stream& stream) {
    char bytes[2];
    stream.readBytes(bytes, 2);

    return asInt(bytes);
}

void writeInt(int value, Stream& stream) {
    char bytes[2];
    asBytes(value, bytes);

    stream.write(bytes,2);
}

double readDouble(Stream& stream) {
    char bytes[4];
    stream.readBytes(bytes, 4);

    return asDouble(bytes);
}

void writeDouble(double value, Stream& stream) {
    char bytes[4];
    asBytes(value, bytes);

    stream.write(bytes, 4);
}

#endif