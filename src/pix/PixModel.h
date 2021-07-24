#ifndef PIXEL_CLIENT_STATUS
#define PIXEL_CLIENT_STATUS

struct PixLimit {
    int lower;
    int upper;
    PixLimit();
    PixLimit(int lower, int upper);
};

struct PixStatus {
    bool moving;
    int target;
    int steps;
    double angle;
    PixLimit limit;
    PixStatus();
    PixStatus(bool moving, int target, int steps, double angle, PixLimit limit);
};

#endif
