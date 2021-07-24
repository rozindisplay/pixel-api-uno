#include "Stream.h"

int readByte(Stream& stream, char& value);
int readByte(Stream& stream, unsigned char& value);
int writeByte(char value, Stream& stream);

int readInt(Stream& stream, int& value);
int writeInt(int value, Stream& stream);

int readDouble(Stream& stream, double& value);
int writeDouble(double value, Stream& stream);
