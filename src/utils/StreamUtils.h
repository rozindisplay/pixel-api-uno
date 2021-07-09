#include "Stream.h"

char readByte(Stream& stream);
void writeByte(char value, Stream& stream);

int readInt(Stream& stream);
void writeInt(int value, Stream& stream);

double readDouble(Stream& stream);
void writeDouble(double value, Stream& stream);