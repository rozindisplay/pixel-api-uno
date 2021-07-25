#ifndef PIXEL_CLIENT_WRITER
#define PIXEL_CLIENT_WRITER

#include <pix/PixModel.h>

class PixWriter {
public:
    int home(unsigned char address);
    int home(unsigned char address, unsigned char pixel);
    int setLimit(unsigned char address, unsigned char pixel, const PixLimit& limit);
    int setSteps(unsigned char address, unsigned char pixel, int steps);
    int addSteps(unsigned char address, unsigned char pixel, int steps);
    int setAngle(unsigned char address, unsigned char pixel, double angle);
    int addAngle(unsigned char address, unsigned char pixel, double angle);
    int clearErrorCode(unsigned char address);
    int requestPing(unsigned char address);
    int requestPixel(unsigned char address, unsigned char &count);
    int requestMoving(unsigned char address, unsigned char &count);
    int requestIsMoving(unsigned char address, unsigned char pixel, bool &isMoving);
    int requestTargetSteps(unsigned char address, unsigned char pixel, int &steps);
    int requestSteps(unsigned char address, unsigned char pixel, int &steps);
    int requestTargetAngle(unsigned char address, unsigned char pixel, double &angle);
    int requestAngle(unsigned char address, unsigned char pixel, double &angle);
    int requestLimit(unsigned char address, unsigned char pixel, PixLimit &limit);
    int requestStatus(unsigned char address, unsigned char pixel, PixStatus& status);
    int requestErrorCode(unsigned char address, int& errorCode);
private:
    int readLimit(PixLimit&);
    int sendRequestType(unsigned char address, unsigned char type, unsigned char pixel);
    int initRequest(unsigned char address, unsigned char type, unsigned char pixel, unsigned char bytes);
    int toPixCode(int transmissionCode);
};

#endif
