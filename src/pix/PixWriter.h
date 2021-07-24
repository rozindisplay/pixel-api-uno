#ifndef PIXEL_CLIENT_WRITER
#define PIXEL_CLIENT_WRITER

#include <pix/PixModel.h>

class PixWriter {
public:
    int init(unsigned char address, const Limit& limitP1, const Limit& limitP2, const Limit& limitP3, const Limit& limitP4);
    int home(unsigned char address);
    int clearErrorCode(unsigned char address);
    int setLimit(unsigned char address, unsigned char pixle, const Limit& limit);
    int setSteps(unsigned char address, unsigned char pixle, int steps);
    int addSteps(unsigned char address, unsigned char pixle, int steps);
    int setAngle(unsigned char address, unsigned char pixle, double angle);
    int addAngle(unsigned char address, unsigned char pixle, double angle);
    int requestPing(unsigned char address);
    int requestErrorCode(unsigned char address, int& errorCode);
    int requestMovingCount(unsigned char address, unsigned char& movingCount);
    int requestStatus(unsigned char address, NodeStatus& status);
private:
    int readLimit(Limit&);
    int readStatus(PixelStatus&);
    int sendRequestType(unsigned char address, unsigned char type);
    int toPixCode(int transmissionCode);
};

#endif
