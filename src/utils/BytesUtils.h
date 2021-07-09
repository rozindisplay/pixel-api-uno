#include "Stream.h"

/**
 * Converts an array of bytes to an int
 * @param buf an array of 2 bytes
 * @returns integer representation (2 bytes)
 */
int asInt(char* buf);

/**
 * Converts an int to an array of bytes
 * @param value integer representation (2 bytes)
 * @param buf an array of 2 bytes where the int will be stored
 */
void asBytes(int value, char* buf);

/**
 * Converts an array of bytes to a double
 */
double asDouble(char* bytes);

/**
 * Converts a double to an array of bytes
 */
void asBytes(double value, char* buf);