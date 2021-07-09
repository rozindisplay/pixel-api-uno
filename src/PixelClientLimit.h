#ifndef PIXEL_CLIENT_LIMIT
#define PIXEL_CLIENT_LIMIT

struct PixelClientLimit {
    const int lower;
    const int upper;
    PixelClientLimit(int lower, int upper): lower(lower), upper(upper){}
};

#endif
