#pragma once
#include "figure.hpp"

class Hexagon: public Figure {
    private:
        int side;
    public:
        Hexagon() : Figure() { side = 0; }
        Hexagon(double x1, double y1, int c);
        std::string Name() override;
        double S() override;
        double Radius_vector() override;
        std::vector<Pair> Coord() override;
};
