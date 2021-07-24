#include <pix/PixModel.h>

PixStatus::PixStatus() {
}

PixStatus::PixStatus(bool moving, int target, int steps, double angle, PixLimit limit): moving(moving), target(target), steps(steps), angle(angle), limit(limit) {
}

PixLimit::PixLimit() {
}

PixLimit::PixLimit(int lower, int upper): lower(lower), upper(upper) {
}