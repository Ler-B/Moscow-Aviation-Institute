#include <iostream>
#include <vector>
#include <string>
#include "Supportive_Functions.h"

#ifndef LAB1_1_TRIDIAGONAL_MATRIX_ALGORITHM_H
#define LAB1_1_TRIDIAGONAL_MATRIX_ALGORITHM_H

class Tridiagonal_Matrix_Algorithm {
private:
    int n;
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::vector<double> d;
    std::vector<double> p;
    std::vector<double> q;
    std::vector<double> x;
    std::vector<std::vector<double>> matr_a;

public:

    Tridiagonal_Matrix_Algorithm(const std::vector<std::vector<double>> &_a, const std::vector<double> &_d) {

        if (_a.size() != _d.size()) throw "Wrong matrix or vector size";

        n = _d.size();
        a = std::vector<double>(n);
        b = std::vector<double>(n);
        c = std::vector<double>(n);
        d = _d;
        p = std::vector<double>(n);
        q = std::vector<double>(n);
        matr_a = _a;

        a[0] = 0;
        b[0] = matr_a[0][0];
        c[0] = matr_a[0][1];
        for (int i = 1; i < n - 1; ++i) {
            a[i] = matr_a[i][i - 1];
            b[i] = matr_a[i][i];
            c[i] = matr_a[i][i + 1];
        }
        a[n - 1] = matr_a[n - 1][n - 2];
        b[n - 1] = matr_a[n - 1][n - 1];
        c[n - 1] = 0;

        Make_P_andQ();
        x = Make_x();
    }

    void PrintElements() {
        PrintMatrix("A:", matr_a);
        PrintVec("d:", d);
        PrintVec("a:", a);
        PrintVec("b:", b);
        PrintVec("c:", c);
        PrintVec("d:", d);
        PrintVec("p:", p);
        PrintVec("q:", q);
    }

    void PrintAnswer() {
        PrintVec("x:", x);
    }

    std::vector<double> Ans() {
        return x;
    }

private:
    void Make_P_andQ() {
         p[0] = - c[0] / b[0];
         q[0] = d[0] / b[0];

         for (int i = 1; i < n - 1; ++i) {
             p[i] = - c[i] / (b[i] + a[i] * p[i - 1]);
             q[i] = (d[i] - a[i] * q[i - 1]) / (b[i] + a[i] * p[i - 1]);
         }
    }

    std::vector<double> Make_x() {
        std::vector<double> ans(n);

        ans[n - 1] = (d[n - 1] - a[n - 1] * q[n - 2]) / (b[n - 1] + a[n - 1] * p[n - 2]);

        for(int i = n - 2; i > -1; --i) {
            ans[i] = p[i] * ans[i + 1] + q[i];
        }

        return ans;
    }

};

#endif //LAB1_1_TRIDIAGONAL_MATRIX_ALGORITHM_H
