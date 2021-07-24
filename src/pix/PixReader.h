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

    int opInit(PixProcessor*);
    int opHome(PixProcessor*);
    int opClearErrorCode(PixProcessor*);
    int opSetLimit(PixProcessor*);
    int opSetSteps(PixProcessor*);
    int opAddSteps(PixProcessor*);
    int opSetAngle(PixProcessor*);
    int opAddAngle(PixProcessor*);
    int opSetRequestType(PixProcessor*);

    int rqPing(PixProcessor*);
    int rqErrorCode(PixProcessor*);
    int rqMovingCount(PixProcessor*);
    int rqStatus(PixProcessor*);

    int nextLimit(PixLimit&);
    int writeLimit(const PixLimit&);
};

#endif
