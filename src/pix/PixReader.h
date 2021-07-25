#ifndef PIXEL_CLIENT_READER
#define PIXEL_CLIENT_READER

#include <pix/PixProcessor.h>
#include <pix/PixConsts.h>

class PixReader {
public:
    bool hasNext();
    int next(PixProcessor*);
    int nextRequest(PixProcessor*);
    unsigned char getRequestType();
private:
    unsigned char requestType = REQUEST_PING;
    unsigned char requestPixel = 0;

    int opHome(PixProcessor*);
    int opHomeAll(PixProcessor*);
    int opSetLimit(PixProcessor*);
    int opSetSteps(PixProcessor*);
    int opAddSteps(PixProcessor*);
    int opSetAngle(PixProcessor*);
    int opAddAngle(PixProcessor*);
    int opClearErrorCode(PixProcessor*);
    int opSetRequestType(PixProcessor*);

    int rqPing(PixProcessor*);
    int rqPixels(PixProcessor*);
    int rqIsMoving(PixProcessor*);
    int rqMovingCount(PixProcessor*);
    int rqTargetSteps(PixProcessor*);
    int rqSteps(PixProcessor*);
    int rqTargetAngle(PixProcessor*);
    int rqAngle(PixProcessor*);
    int rqLimit(PixProcessor*);
    int rqStatus(PixProcessor*);
    int rqErrorCode(PixProcessor*);

    int nextLimit(PixLimit&);
    int writeLimit(const PixLimit&);
    int writeHeader(unsigned char rqCode);
};

#endif
