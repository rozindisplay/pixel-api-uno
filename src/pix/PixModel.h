#ifndef PIXEL_CLIENT_STATUS
#define PIXEL_CLIENT_STATUS

struct Limit {
    int lower;
    int upper;
    Limit();
    Limit(int lower, int upper);
};

struct PixelStatus {
    bool moving;
    int target;
    int steps;
    double angle;
    Limit limit;
    PixelStatus();
    PixelStatus(bool moving, int target, int steps, double angle, Limit limit);
};

struct NodeStatus {
public:
    int error;
    
    const int size();
    PixelStatus& operator[](int);
    NodeStatus();
    NodeStatus(int error, PixelStatus ps0, PixelStatus ps1, PixelStatus ps2, PixelStatus ps3);
private:
    PixelStatus pixels[4];
};

#endif
