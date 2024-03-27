//Будникова Валерия Павловна М8О-207Б
//Вариант 31(Фигуры: треугольник, 6-угольник, 7-угольник)
#pragma once
#include <iostream>
#include <vector>
#include <string>

struct Pair {
    double x;
    double y;
    Pair(): x(0), y(0) {}
    Pair(double a, double b): x(a), y(b) {}
};

class Figure {
    protected:
        std::vector<Pair> points;
    public:
        Figure() {}
        Figure(double x1, double y1, int c) {
            points.emplace_back(Pair(x1,y1));
        }
        virtual std::string Name() {
            return "Point";
        }
        virtual int Get() {
            return 0;
        }

        virtual std::vector<Pair> Coord() {
            return points;
        }
};

std::ostream& operator<<(std::ostream &os, Pair p) {
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}

std::ostream& operator<<(std::ostream &os, std::vector<Pair> pair) {
    for (auto p: pair) os << " " << p;
    return os;
}

std::ostream& operator<<(std::ostream &os, std::vector<std::shared_ptr<Figure>> fig) {
    for (auto f: fig) os << f->Name() << std::endl << f->Coord() << std::endl;
    return os;
}


