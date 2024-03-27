//Будникова Валерия Павловна М8О-207Б
//Вариант 31(Фигуры: треугольник, 6-угольник, 7-угольник)
#pragma once
#include <cmath>
#include "figure.hpp"

class Hexagon: public Figure {
    private:
        int side;
    public:
        Hexagon() : Figure(), side(0) {}

        Hexagon(double x1, double y1, int c): side(c) {
            points.push_back(Pair(x1, y1));
            points.push_back(Pair(x1 - (double)c * sqrt(3) / 2, y1 - (double) c / 2));
            points.push_back(Pair(x1 + (double)c * sqrt(3) / 2, y1 - (double) c / 2));
            points.push_back(Pair(x1 - (double)c * sqrt(3) / 2, y1 - (double) c / 2 - c));
            points.push_back(Pair(x1 + (double)c * sqrt(3) / 2, y1 - (double) c / 2 - c));
            points.push_back(Pair(x1, y1 - 2 * c));
        }
    
        std::string Name() override {
            return "Hexagon";
        }
        int Get() override {
            return side;
        }

        std::vector<Pair> Coord() override {
            return points;
        }
};
