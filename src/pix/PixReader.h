#ifndef PIXEL_CLIENT_READER
#define PIXEL_CLIENT_READER

#include <pix/PixLimit.h>
#include <pix/PixProcessor.h>
#include <pix/PixConsts.h>

class PixReader {
public:
    bool hasNext();
    void next(PixProcessor*);
    void nextRequest(PixProcessor*);
    unsigned char getRequestType();
private:
    unsigned char requestType = REQUEST_PING;

    void opInit(PixProcessor*);
    void opHome(PixProcessor*);
    void opClearErrorCode(PixProcessor*);
    void opSetLimit(PixProcessor*);
    void opSetSteps(PixProcessor*);
    void opAddSteps(PixProcessor*);
    void opSetAngle(PixProcessor*);
    void opAddAngle(PixProcessor*);
    void opSetRequestType(PixProcessor*);

    void rqPing(PixProcessor*);
    void rqErrorCode(PixProcessor*);
    void rqMovingCount(PixProcessor*);
    void rqStatus(PixProcessor*);

    PixLimit nextLimit();
    void writeLimit(const PixLimit&);
};

#endif
