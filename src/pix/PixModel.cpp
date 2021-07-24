#include <pix/PixModel.h>

NodeStatus::NodeStatus() {
}

NodeStatus::NodeStatus(int error, PixelStatus ps0, PixelStatus ps1, PixelStatus ps2, PixelStatus ps3): error(error), pixels({ps0, ps1, ps2, ps3}) {
}

const int NodeStatus::size() {
    return 4;
}

PixelStatus& NodeStatus::operator[](int i) {
    return pixels[i];
}

PixelStatus::PixelStatus() {
}

PixelStatus::PixelStatus(bool moving, int target, int steps, double angle, Limit limit): moving(moving), target(target), steps(steps), angle(angle), limit(limit) {
}

Limit::Limit() {
}

Limit::Limit(int lower, int upper): lower(lower), upper(upper) {
}