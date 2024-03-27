//Будникова Валерия Павловна 
//Варианты фигур - Треульльник, Шестиугольник, Восьмиугольник
//Задание - Спроектировать простейший «графический» векторный редактор. 
#pragma once
#include <cmath>
#include "figure.hpp"

class Hexagon: public Figure {
    private:
        int side;
    public:
        Hexagon() : Figure() {side = 0;}

        Hexagon(double x1, double y1, int c) {
            points.push_back(Pair(x1, y1));
            points.push_back(Pair(x1 - (double)c * sqrt(3) / 2, y1 - (double) c / 2));
            points.push_back(Pair(x1 + (double)c * sqrt(3) / 2, y1 - (double) c / 2));
            points.push_back(Pair(x1 - (double)c * sqrt(3) / 2, y1 - (double) c / 2 - c));
            points.push_back(Pair(x1 + (double)c * sqrt(3) / 2, y1 - (double) c / 2 - c));
            points.push_back(Pair(x1, y1 - 2 * c));
            side = c;
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
