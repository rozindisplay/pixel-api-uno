#ifndef PIXEL_CLIENT_STATUSES
#define PIXEL_CLIENT_STATUSES

#include <pix/PixStatus.h>

class PixStatusSet {
public:
    const int error;
    PixStatusSet(const int error, const PixStatus status0, const PixStatus status1, const PixStatus status2, const PixStatus status3);

    const int size();
    const PixStatus* getStatus(int);
    const PixStatus* operator[](int);
private:
    const PixStatus statuses[4];
};

#endif
