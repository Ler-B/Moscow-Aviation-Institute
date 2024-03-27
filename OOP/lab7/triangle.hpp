//Будникова Валерия Павловна 
//Варианты фигур - Треульльник, Шестиугольник, Восьмиугольник
//Задание - Спроектировать простейший «графический» векторный редактор. 
#pragma once
#include <cmath>
#include "figure.hpp"

class Triangle: public Figure {
    private:
        int side;
    public:
        Triangle() : Figure() { side = 0; }

        Triangle(double x1, double y1, int c) {
            side = c;
            points.emplace_back(Pair(x1, y1));
            points.emplace_back(Pair(x1 - (double)side / 2, y1 - (double)side * sqrt(3) / 2));
            points.emplace_back(Pair(x1 + (double)side / 2, y1 - (double)side * sqrt(3) / 2));
        }

        std::string Name() override {
            return "Triangle";
        }

        int Get() override {
            return side;
        }

        std::vector<Pair> Coord() override {
            return points;
        }
};
