#include "triangle.hpp"
#include <cmath>

Triangle::Triangle(double x1, double y1, int c) {
    side = c;
    points.emplace_back(Pair(x1, y1));
    points.emplace_back(Pair(x1 - (double)side / 2, y1 - (double)side * sqrt(3) / 2));
    points.emplace_back(Pair(x1 + (double)side / 2, y1 - (double)side * sqrt(3) / 2));
}

std::string Triangle::Name() {
    return "Triangle";
}

double Triangle::S() {
    double s = side * side * sqrt(3) / 4;
    return s;
}

double Triangle::Radius_vector() {
    double r = side / sqrt(3);
    return r;
}

std::vector<Pair> Triangle::Coord() {
    return points;
}