#ifndef PIXEL_CLIENT_UTILS_BYTES
#define PIXEL_CLIENT_UTILS_BYTES

#include "Arduino.h"
#include "BytesUtils.h"

int asInt(char* buf) {
    int value = 0;
    memcpy(&value, buf, 2);
    
    return value;
}

void asBytes(int value, char* buf) {
    memcpy(buf, &value, 2);
}

double asDouble(char* buf) {
    double value = 0;
    memcpy(&value, buf, 4);
    
    return value;
}

void asBytes(double value, char* buf) {
    memcpy(buf, &value, 4);
}

#endif