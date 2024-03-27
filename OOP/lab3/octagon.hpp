#pragma once
#include "figure.hpp"

class Octagon: public Figure {
    private:
        int side;
    public:
        Octagon() : Figure() { side = 0; }
        Octagon(double x1, double y1, int c);
        std::string Name() override;
        double S() override;
        double Radius_vector() override;
        std::vector<Pair> Coord() override;
};