#include <pix/PixStatusSet.h>

PixStatusSet::PixStatusSet(const int error, const PixStatus status0, const PixStatus status1, const PixStatus status2, const PixStatus status3): error(error), statuses({status0, status1, status2, status3}) {
}

const int PixStatusSet::size() {
    return 4;
}

const PixStatus* PixStatusSet::getStatus(int i) {
    return &statuses[i];
}

const PixStatus* PixStatusSet::operator[](int i) {
    return getStatus(i);
}