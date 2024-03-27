#include "hexagon.hpp"
#include <cmath>

Hexagon::Hexagon(double x1, double y1, int c) {
    points.push_back(Pair(x1, y1));
    points.push_back(Pair(x1 - (double)c * sqrt(3) / 2, y1 - (double) c / 2));
    points.push_back(Pair(x1 + (double)c * sqrt(3) / 2, y1 - (double) c / 2));
    points.push_back(Pair(x1 - (double)c * sqrt(3) / 2, y1 - (double) c / 2 - c));
    points.push_back(Pair(x1 + (double)c * sqrt(3) / 2, y1 - (double) c / 2 - c));
    points.push_back(Pair(x1, y1 - 2 * c));
    side = c;
}

std::string Hexagon::Name() {
    return "Hexagon";
}

double Hexagon::S() {
    double s = 3 * sqrt(3) * side * side / 2;
    return s;
}

double Hexagon::Radius_vector() {
    return side;
}

std::vector<Pair> Hexagon::Coord() {
    return points;
}
