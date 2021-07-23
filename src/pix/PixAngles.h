#ifndef PIXEL_CLIENT_ANGLES
#define PIXEL_CLIENT_ANGLES

class PixAngles {
public:
    PixAngles(const double, const double, const double, const double);
    int size();
    int getAngle(int);
    int operator[](int);
private:
    const double angles[4];
};

#endif
