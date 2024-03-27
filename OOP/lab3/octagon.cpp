#include "octagon.hpp"
#include <cmath>


Octagon::Octagon(double x1, double y1, int c) {
    points.push_back(Pair(x1, y1));
    points.push_back(Pair(x1 + (double)c * cos(M_PI / 8), y1 -  (double)c * sin(M_PI / 8)));
    points.push_back(Pair(x1 - (double)c * cos(M_PI / 8), y1 -  (double)c * sin(M_PI / 8)));
    points.push_back(Pair(x1 + (double)c * sqrt(1 / sqrt(2) + 1), y1 - (double)c * sqrt(1 / sqrt(2) + 1)));
    points.push_back(Pair(x1 - (double)c * sqrt(1 / sqrt(2) + 1), y1 - (double)c * sqrt(1 / sqrt(2) + 1)));
    points.push_back(Pair(x1 + (double)c * cos(M_PI / 8), y1 - 2 * (double)c * cos(M_PI / 8)));
    points.push_back(Pair(x1 - (double)c * cos(M_PI / 8), y1 - 2 * (double)c * cos(M_PI / 8)));
    points.push_back(Pair(x1, y1 - 2 * (double)c * sqrt(1 / sqrt(2) + 1)));
    side = c;
}

std::string Octagon::Name() {
    return "Octagon";
}

double Octagon::S() {
    double s = 2 * side * side * (1 + sqrt(2));
    return s;
}

double Octagon::Radius_vector() {
    double r = side * sqrt(1 / sqrt(2) + 1);
    return r;
}

std::vector<Pair> Octagon::Coord() {
    return points;
}