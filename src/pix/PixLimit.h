#ifndef PIXEL_CLIENT_LIMIT
#define PIXEL_CLIENT_LIMIT

struct PixLimit {
    const int lower;
    const int upper;
    PixLimit(int lower, int upper): lower(lower), upper(upper){}
};

#endif
