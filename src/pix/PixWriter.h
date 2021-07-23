#ifndef PIXEL_CLIENT_WRITER
#define PIXEL_CLIENT_WRITER

#include <pix/PixLimit.h>
#include <pix/PixStatusSet.h>

class PixWriter {
public:
    void init(unsigned char address, const PixLimit& limitP1, const PixLimit& limitP2, const PixLimit& limitP3, const PixLimit& limitP4);
    void home(unsigned char address);
    void clearErrorCode(unsigned char address);
    void setLimit(unsigned char address, unsigned char pixle, const PixLimit& limit);
    void setSteps(unsigned char address, unsigned char pixle, int steps);
    void addSteps(unsigned char address, unsigned char pixle, int steps);
    void setAngle(unsigned char address, unsigned char pixle, double angle);
    void addAngle(unsigned char address, unsigned char pixle, double angle);
    bool requestPing(unsigned char address);
    int requestErrorCode(unsigned char address);
    unsigned char requestMovingCount(unsigned char address);
    const PixStatusSet requestStatus(unsigned char address);
private:
    PixLimit readLimit();
    PixStatus readStatus();
};

#endif
