#include <iostream>
#include <vector>
#include <string>
#include "Supportive_Functions.h"

#ifndef LAB1_1_ZEIDEL_METHOD_H
#define LAB1_1_ZEIDEL_METHOD_H

class Zeidel_Method {
private:
    int n;
    double eps;
    double count;
    std::vector<double> b;
    std::vector<double> bet;
    std::vector<double> x;
    std::vector<std::vector<double>> a;
    std::vector<std::vector<double>> al;
    std::vector<std::vector<double>> al2;
public:
    Zeidel_Method(const std::vector<std::vector<double>> &_a, const std::vector<double> &_b, double _eps) {

        if (_a.size() != _b.size()) throw "Wrong matrix or vector size";
        n = _a.size();
        eps = _eps;
        b = _b;
        a = _a;

        Make_Alpha_Betta();
        al2 = Al2(al);

        x = Make_x();
    }

    void PrintElements() {
        PrintMatrix("A:", a);
        PrintVec("b:", b);
        PrintMatrix("Alpha:", al);
        PrintMatrix("Alpha2:", al2);
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
        count = 0;
        x = bet;
        std::vector<double> x_prev = x;


        double norm_al = Norm1(al);
        double norm_al2 = Norm1(al2);

        while(eps_k > eps) {
            x_prev = x;
            x = Zend_Multi(al, x_prev) + bet;
//            PrintVec("Zendel x", x);
            if (norm_al < 1) {
                eps_k = norm_al2 * Norm1(x - x_prev) / (1 - norm_al);
            } else {
                eps_k = Norm1(x - x_prev);
            }
            ++count;
        }

        return x;
    }

    std::vector<double> Zend_Multi(const std::vector<std::vector<double>> &m, const std::vector<double> &v) {
        std::vector<double> ans(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                ans[i] += m[i][j] * (ans[j] + bet[j]);
            }
            for (int j = i; j < n; ++j) {
                ans[i] += m[i][j] * v[j];
            }
        }
        return ans;
    }

    std::vector<std::vector<double>> Al2(const std::vector<std::vector<double>> &al) {
        std::vector<std::vector<double>> al2(n, std::vector<double>(n, 0));
        for(int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                al2[i][j] = al[i][j];
            }
        }
        return al2;
    }
};

#endif //LAB1_1_ZEIDEL_METHOD_H
