#include "ShapeCalculator.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static inline bool neg(double v) { return v < 0.0; }

double ShapeCalculator::areaCircle(double r) const {
    if (neg(r)) return -1.0;
    return M_PI * r * r;
}

double ShapeCalculator::perimeterCircle(double r) const {
    if (neg(r)) return -1.0;
    return 2.0 * M_PI * r;
}

double ShapeCalculator::areaRectangle(double L, double W) const {
    if (neg(L) || neg(W)) return -1.0;
    return L * W;
}

double ShapeCalculator::areaTriangle(double b, double h) const {
    if (neg(b) || neg(h)) return -1.0;
    return 0.5 * b * h;
}

double ShapeCalculator::distance(double x1, double y1,
                                 double x2, double y2) const {
    // No validation needed; distance is defined for all real inputs
    const double dx = x2 - x1;
    const double dy = y2 - y1;
    return std::sqrt(dx*dx + dy*dy);
}
