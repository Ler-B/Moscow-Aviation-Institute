#pragma once
#include <iostream>
#include <vector>
#include <string>

struct Pair {
    double x;
    double y;
    Pair() {
        x = 0;
        y = 0;
    }
    Pair(double a, double b) {
        x = a;
        y = b;
    }
};

 class Figure {
    protected:
        std::vector<Pair> points;
    public:
        Figure();
        Figure(double x1, double y1, int c);
        virtual std::string Name();
        virtual double S();
        virtual double Radius_vector();
        virtual std::vector<Pair> Coord();
 };


