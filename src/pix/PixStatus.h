#ifndef PIXEL_CLIENT_STATUS
#define PIXEL_CLIENT_STATUS

class PixStatus {
public:
    const bool moving;
    const int target;
    const int steps;
    const double angle;
    const PixLimit limit;
    PixStatus(const bool moving, const int target, const int steps, const double angle, const PixLimit limit)
        :moving(moving), target(target), steps(steps), angle(angle), limit(limit) {}
};

#endif
