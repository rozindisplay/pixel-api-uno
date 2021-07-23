#ifndef PIXEL_CLIENT_STEPS
#define PIXEL_CLIENT_STEPS

class PixSteps {
public:
    PixSteps(const int, const int, const int, const int);
    int size();
    int getSteps(int);
    int operator[](int);
private:
    const int steps[4];
};

#endif
