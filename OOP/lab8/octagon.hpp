//Будникова Валерия Павловна М8О-207Б
//Вариант 31(Фигуры: треугольник, 6-угольник, 7-угольник)
#pragma once
#include <cmath>
#include "figure.hpp"

class Octagon: public Figure {
    private:
        int side;
    public:
        Octagon() : Figure(), side(0) {}
        Octagon(double x1, double y1, int c): side(c) {
            points.push_back(Pair(x1, y1));
            points.push_back(Pair(x1 + (double)c * cos(M_PI / 8), y1 -  (double)c * sin(M_PI / 8)));
            points.push_back(Pair(x1 - (double)c * cos(M_PI / 8), y1 -  (double)c * sin(M_PI / 8)));
            points.push_back(Pair(x1 + (double)c * sqrt(1 / sqrt(2) + 1), y1 - (double)c * sqrt(1 / sqrt(2) + 1)));
            points.push_back(Pair(x1 - (double)c * sqrt(1 / sqrt(2) + 1), y1 - (double)c * sqrt(1 / sqrt(2) + 1)));
            points.push_back(Pair(x1 + (double)c * cos(M_PI / 8), y1 - 2 * (double)c * cos(M_PI / 8)));
            points.push_back(Pair(x1 - (double)c * cos(M_PI / 8), y1 - 2 * (double)c * cos(M_PI / 8)));
            points.push_back(Pair(x1, y1 - 2 * (double)c * sqrt(1 / sqrt(2) + 1)));
        }
        std::string Name() override {
            return "Octagon";
        }

        int Get() override {
            return side;
        }

        std::vector<Pair> Coord() override {
            return points;
        }
};