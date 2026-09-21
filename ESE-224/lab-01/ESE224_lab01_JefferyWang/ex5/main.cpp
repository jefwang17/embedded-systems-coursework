#include "ShapeCalculator.h"
#include <iostream>
#include <iomanip>
using namespace std;
// g++ main.cpp ShapeCalculator.cpp -o main
int main() {
    ShapeCalculator sc;

    cout << fixed << setprecision(2);

    cout << "Area circle r=3: "      << sc.areaCircle(3.0) << "\n";
    cout << "Perimeter circle r=3: " << sc.perimeterCircle(3.0) << "\n";
    cout << "Area rectangle 4x5: "   << sc.areaRectangle(4.0, 5.0) << "\n";
    cout << "Area triangle b=6,h=2: "<< sc.areaTriangle(6.0, 2.0) << "\n";
    cout << "Distance (0,0) to (3,4): " << sc.distance(0.0, 0.0, 3.0, 4.0) << "\n";

    // Invalid input examples:
    cout << "Area circle r=-2: " << sc.areaCircle(-2.0) << " (invalid -> -1)\n";

    return 0;
}
