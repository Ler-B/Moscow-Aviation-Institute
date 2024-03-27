#include <iostream>
#include <vector>
#include <string>
#include "Supportive_Functions.h"

#ifndef LAB1_1_SIMPLE_ITERATION_METHOD_H
#define LAB1_1_SIMPLE_ITERATION_METHOD_H

class Simple_Iteration_Method {
private:
    int n;
    double eps;
    double count;
    std::vector<double> b;
    std::vector<double> bet;
    std::vector<double> x;
    std::vector<std::vector<double>> a;
    std::vector<std::vector<double>> al;

public:
    Simple_Iteration_Method(const std::vector<std::vector<double>> &_a, const std::vector<double> &_b, double _eps) {

        if (_a.size() != _b.size()) throw "Wrong matrix or vector size";
        n = _a.size();
        eps = _eps;
        b = _b;
        a = _a;

        Make_Alpha_Betta();

        x = Make_x();
    }

    void PrintElements() {
        PrintMatrix("A:", a);
        PrintVec("b:", b);
        PrintMatrix("Alpha:", al);
        PrintVec("Betta:", bet);
    }

    void PrintAnswer() {
        PrintVec("x:", x);
    }

    void PrintAnalysis() {
        std::cout << count << " итерации(ий) потребовалось для получения ответа.\n\n";
    }

private:

    void Make_Alpha_Betta() {
        al = a;
        bet = b;
        for (int i = 0; i < n; ++i) {
            double diag_el = a[i][i];
            bet[i] /= diag_el;
            for (int j = 0; j < n; ++j) {
                al[i][j] /= -diag_el;
                if (i == j) al[i][j] = 0;
            }
        }
    }

    std::vector<double> Make_x() {
        double eps_k = eps + 1;
        x = bet;
        std::vector<double> x_prev = x;
        count = 0;
        double norm_al = Norm1(al);
        while(eps_k > eps) {

            x_prev = x;
            x = al*x_prev + bet;

            if (norm_al < 1) {
                eps_k = norm_al * Norm1(x - x_prev) / (1 - norm_al);
            } else {
                eps_k = Norm1(x - x_prev);
            }

            ++count;
        }

        return x;
    }

};

#endif //LAB1_1_SIMPLE_ITERATION_METHOD_H
