#include "Wire.h"
#include <utils/StreamUtils.h>
#include "PixelClientConsts.h"
#include "PixelClientRequestHandler.h"

void PixelClientRequestHandler::next(PixelClientProcessor* processor) {
    switch (requestType) {
    case REQUEST_PING:
        rqPing(processor);
        break;
    default:
        // error: unknown request type
        break;
    }
}

void PixelClientRequestHandler::rqPing(PixelClientProcessor* processor) {
    processor->ping();
    writeByte(REQUEST_PING, Wire);
}
