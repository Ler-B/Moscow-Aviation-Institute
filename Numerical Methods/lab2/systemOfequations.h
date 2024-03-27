//
// Created by Валерия Будникова on 15.05.2022.
//
#include <cmath>
#include <vector>
#include <iostream>
using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;

#ifndef H_MET_LAB2_SYSTEMOFEQUATIONS_H
#define H_MET_LAB2_SYSTEMOFEQUATIONS_H

class SystemOfequations{
public:
    double a = 4;

    SystemOfequations(double _a){
        a = _a;
    }

    SystemOfequations() {};

    Vector f(Vector x) {
        if (x.size() != 2) {
            std::cout << "Размер вектора х не соответствует системе\n";
        }
        Vector rez = Vector(2);
        double x1 = x[0];
        double x2 = x[1];
        rez[0] = (pow(x1, 2) + pow(a, 2)) * x2 - pow(a, 3);
        rez[1] = pow(x1 - a/2, 2) + pow(x2 - a/2, 2) - pow(a, 2);
        return rez;
    }

    Vector Phi(Vector x) {
        Vector rez = Vector(2);
        double x1 = x[0];
        double x2 = x[1];
        rez[0] = sqrt(pow(a, 2) - pow(x2 - a/2, 2)) + a / 2;
        rez[1] = pow(a, 3) / (pow(rez[0], 2) + pow(a, 2));
        return rez;

    }

    Matrix J_Phi(const Vector &x){
        if (x.size() != 2) {
            std::cout << "Размер вектора х не соответствует системе\n";
        }
        Matrix rez = Matrix(2, Vector(2));
        double x1 = x[0];
        double x2 = x[1];
        rez[0][0] = 0;
        rez[0][1] = (a - 2 * x2) / sqrt(3 * a * a + 4 * a * x2 - 4* x2 * x2);
        rez[1][0] = - 2 * a * a * a * x1 / pow(a * a + x1 * x1, 2);
        rez[1][1] = 0;
        return rez;
    }

    Matrix J_f(const Vector &x){
        if (x.size() != 2) {
            std::cout << "Размер вектора х не соответствует системе\n";
        }
        Matrix rez = Matrix(2, Vector(2));
        double x1 = x[0];
        double x2 = x[1];
        rez[0][0] = 2 * x1 * x2;
        rez[0][1] = x1 * x1 + a * a;
        rez[1][0] = 2 * x1 - a;
        rez[1][1] = 2 * x2 - a;
        return rez;
    }


    Matrix J_f_1(const Vector &x){
        if (x.size() != 2) {
            std::cout << "Размер вектора х не соответствует системе\n";
        }
        Matrix rez = Matrix(2, Vector(2));
        double x1 = x[0];
        double x2 = x[1];
        Matrix j = this->J_f(x);
        double _a = j[0][0];
        double _b = j[0][1];
        double _c = j[1][0];
        double _d = j[1][1];

        double det = (_a * _d - _b * _c);

        rez[0][0] = _d / det;
        rez[0][1] = -_b / det;
        rez[1][0] = -_c / det;
        rez[1][1] = _a / det;

        return rez;
    }
//    Matrix _J_1(const Vector &x){
//        if (x.size() != 2) {
//            std::cout << "Размер вектора х не соответствует системе\n";
//        }
//        Matrix rez = Matrix(2, Vector(2));
//        double x1 = x[0];
//        double x2 = x[1];
//        Matrix j = this->J_Phi(x);
//        double _a = j[0][0];
//        double _b = j[0][1];
//        double _c = j[1][0];
//        double _d = j[1][1];
//
//        double det = (_a * _d - _b * _c);
//
//        rez[0][0] = _d / det;
//        rez[0][1] = -_b / det;
//        rez[1][0] = -_c / det;
//        rez[1][1] = _a / det;
//
//        return rez;
//    }
};

#endif //H_MET_LAB2_SYSTEMOFEQUATIONS_H
