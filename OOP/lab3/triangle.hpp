#pragma once
#include "figure.hpp"

class Triangle: public Figure {
    private:
        int side;
    public:
        Triangle() : Figure() { side = 0; }
        Triangle(double x1, double y1, int c);
        std::string Name() override;
        double S() override;
        double Radius_vector() override;
        std::vector<Pair> Coord() override;
};
