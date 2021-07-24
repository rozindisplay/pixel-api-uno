#ifndef PIXEL_CLIENT_WRITER
#define PIXEL_CLIENT_WRITER

#include <pix/PixModel.h>

class PixWriter {
public:
    int init(unsigned char address, const PixLimit& limitP1, const PixLimit& limitP2, const PixLimit& limitP3, const PixLimit& limitP4);
    int home(unsigned char address);
    int clearErrorCode(unsigned char address);
    int setLimit(unsigned char address, unsigned char pixle, const PixLimit& limit);
    int setSteps(unsigned char address, unsigned char pixle, int steps);
    int addSteps(unsigned char address, unsigned char pixle, int steps);
    int setAngle(unsigned char address, unsigned char pixle, double angle);
    int addAngle(unsigned char address, unsigned char pixle, double angle);
    int requestPing(unsigned char address);
    int requestErrorCode(unsigned char address, int& errorCode);
    int requestMovingCount(unsigned char address, unsigned char& movingCount);
    int requestStatus(unsigned char address, unsigned char pixle, PixStatus& status);
private:
    int readLimit(PixLimit&);
    int sendRequestType(unsigned char address, unsigned char type, unsigned char pixel);
    int initRequest(unsigned char address, unsigned char type, unsigned char pixel, unsigned char bytes);
    int toPixCode(int transmissionCode);
};

#endif
