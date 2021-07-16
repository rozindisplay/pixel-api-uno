#ifndef PIXEL_CLIENT_REQUEST_HANDLER
#define PIXEL_CLIENT_REQUEST_HANDLER

#include "PixelClientProcessor.h"

class PixelClientRequestHandler {
public:
    void next(PixelClientProcessor*);
private:
    void rqPing(PixelClientProcessor*);
    unsigned char requestType;
};

#endif
