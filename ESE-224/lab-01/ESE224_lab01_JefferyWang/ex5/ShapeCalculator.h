#ifndef SHAPE_CALCULATOR_H
#define SHAPE_CALCULATOR_H

class ShapeCalculator {
private:
    // Example private attributes (not required for the stateless API,
    // but included per exercise suggestion)
    double radius{};
    double length{}, width{};
    double base{}, height{};
    double x1{}, y1{}, x2{}, y2{};

public:
    // All methods are const and validate inputs (negatives -> return -1.0)
    double areaCircle(double r)                const;
    double perimeterCircle(double r)           const;
    double areaRectangle(double L, double W)   const;
    double areaTriangle(double b, double h)    const;
    double distance(double x1, double y1,
                    double x2, double y2)      const;
};

#endif
