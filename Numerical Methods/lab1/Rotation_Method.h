#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Supportive_Functions.h"

#ifndef LAB1_1_ROTATIONMETHOD_H
#define LAB1_1_ROTATIONMETHOD_H

class Rotation_Method {
private:
    int n;
    double eps;
    std::vector<double> eigenvalues;
    std::vector<std::vector<double>> a;
    std::vector<std::vector<double>> eigenvectors;
public:
    Rotation_Method(const std::vector<std::vector<double>> &_a, double _eps) {

        n = _a.size();
        eps = _eps;
        a = _a;

        Go();
    }

    void PrintElements() {
        PrintMatrix("A:", a);
        std::cout << "eps:" << eps << '\n';
        PrintMatrix("Eigenvectors: ", eigenvectors);
        PrintMatrix("Fundamental Eigenvectors: ", FundamentalEigenvectors());
        PrintVec("Eigenvalues: ", eigenvalues);
    }

    void PrintAnswer() {
        PrintMatrix("Собственные вектора: ", eigenvectors);
//        PrintMatrix("Система СВ: ", FundamentalEigenvectors());
        PrintVec("Собственные значения: ", eigenvalues);

    }
private:

    void Go() {
        std::vector<std::vector<double>> uk(n, std::vector<double>(n));
        std::vector<std::vector<double>> ak = a;
        eigenvalues = std::vector<double>(n);

        std::pair<int, int> max = FindMaxElem(ak);
        uk = Make_U(max, ak);
        ak = Transpose(uk) * ak * uk;
        double eps_k = Make_eps(ak);
        eigenvectors = uk;

        while(eps_k > eps) {
            max = FindMaxElem(ak);
            uk = Make_U(max, ak);
            ak = Transpose(uk) * ak * uk;
            eps_k = Make_eps(ak);
            eigenvectors = eigenvectors * uk;
        }
        for(int i = 0; i < n; ++i) {
            eigenvalues[i] = ak[i][i];
        }
    }

    std::vector<std::vector<double>> Make_U(const std::pair<int, int> &max, const std::vector<std::vector<double>> &ak) {
        std::vector<std::vector<double>> u(n, std::vector<double>(n));

        double phi = std::atan(2 * ak[max.first][max.second] / (ak[max.first][max.first] - ak[max.second][max.second])) / 2;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) u[i][j] = 1;
                if (i != j) u[i][j] = 0;
                if (i == max.first and j == max.first) u[i][j] = std::cos(phi);
                if (i == max.second and j == max.second) u[i][j] = std::cos(phi);
                if (i == max.first and j == max.second) u[i][j] = - std::sin(phi);
                if (i == max.second and j == max.first) u[i][j] = std::sin(phi);
            }
        }

        return u;
    }

    std::pair<int, int> FindMaxElem(const std::vector<std::vector<double>> &ak) {
        std::pair<int, int> max(1, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (std::abs(ak[i][j]) > std::abs(ak[max.first][max.second])) {
                    max.first = i;
                    max.second = j;
                }
            }
        }
        return max;
    }

    double Make_eps(const std::vector<std::vector<double>> &ak) {
        double eps = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                eps += ak[i][j] * ak[i][j];
            }
        }
        return std::sqrt(eps);
    }

    std::vector<std::vector<double>> FundamentalEigenvectors() {
        std::vector<std::vector<double>> rez = eigenvectors;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                rez[i][j] /= eigenvectors[n - 1][j];
            }
        }
        return rez;
    }

};

#endif //LAB1_1_ROTATIONMETHOD_H
