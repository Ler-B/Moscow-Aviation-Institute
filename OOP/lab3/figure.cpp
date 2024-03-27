#include "figure.hpp"

Figure::Figure() {
}

Figure::Figure(double x1, double y1, int c) {
    points.emplace_back(Pair(x1,y1));
}

std::string Figure::Name() {
    return "Figure";
}

double Figure::S() {
    return 0;
}

double Figure::Radius_vector() {
    return 0;
}

std::vector<Pair> Figure::Coord() {
    return points;
}
