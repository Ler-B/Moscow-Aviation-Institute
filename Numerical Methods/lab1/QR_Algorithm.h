#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Supportive_Functions.h"

#ifndef LAB1_1_QR_DECOMPOSITION_H
#define LAB1_1_QR_DECOMPOSITION_H

class QR_Algorithm {
private:
    int n;
    double eps;
    Matrix a;
    Matrix q;
    Matrix r;
    std::vector<Complex> eigenvalues;

public:
    QR_Algorithm(const Matrix &_a, const double &_eps) {

        if (_a.size() != _a[0].size()) throw "Wrong matrix size";

        n = _a.size();
        eps = _eps;
        a = _a;
        q = Matrix (n, Vector(n, 0));
        r = Matrix (n, Vector(n, 0));

        Algorithm();
    }

    void PrintElements() {
        PrintMatrix("A:", a);
        PrintMatrix("Q:", q);
        PrintMatrix("R:", r);


        for (int i = 0; i < n; ++i) {
            std::cout.precision(3);
            std::cout << "lambda" << i + 1 << " = " << eigenvalues[i] << "\n";
        }
    }

private:
    std::pair<Matrix, Matrix> QR_Decomposition(const Matrix &a) {
        Matrix q, r;
        Matrix ak, hk;
        Vector vk(n);
        ak = a;

        vk[0] = ak[0][0] + Sign(ak[0][0])* EuclidianNorm(ak, 0);
        for (int i = 1; i < n; ++i) {
            vk[i] = a[i][0];
        }

        hk = E(n) - (2 / Scalar(vk, vk)) * (vk * vk);

        q = hk;
        ak = hk * ak;
        for (int k = 1; k < n - 1; ++k) {

            for (int i = 0; i < k; ++i) {
                vk[i] = 0;
            }
            vk[k] = ak[k][k] + Sign(ak[k][k])* EuclidianNorm(ak, k);
            for (int i = k + 1; i < n; ++i) {
                vk[i] = a[i][k];
            }
            hk = E(n) - (2 / Scalar(vk, vk)) * (vk * vk);

            q = q * hk;
            ak = hk * ak;
        }

        r = ak;

        return std::pair<Matrix, Matrix>{q, r};
    }

    void Algorithm() {
        double eps2_k = eps + 1;
        Matrix ak;
        ak = a;
        std::pair<Matrix, Matrix> qr = QR_Decomposition(ak);

        q = qr.first;
        r = qr.second;

        int counter = 0;
        while (eps2_k > eps) {

            ak = Transpose(qr.first) * ak * qr.first;

            qr = QR_Decomposition(ak);

            eps2_k = Eps(ak);

            ++counter;
        }

        FindEigenvalues(ak);

    }

    double Eps(Matrix ak) {
        double eps = 0;
        for (int i = 0; i < n - 2; ++i) {
            eps += ak[i + 2][i] * ak[i + 2][i];
        }
        return std::sqrt(eps);
    }

    void FindEigenvalues(const Matrix &m) {
        for (int i = 0; i < n - 1; ++i) {
            if (std::abs(m[i + 1][i]) > eps) {
                Solve(m[i][i], m[i][i + 1], m[i + 1][i], m[i + 1][i + 1]);
            } else {
                Complex l(m[i][i], 0);
                eigenvalues.push_back(l);
            }
        }
    }

    void Solve(const double &a1, const double &a2, const double &a3, const double &a4) {
        double a = 1;
        double b = -(a1 + a4);
        double c = a1 * a4 - a2 * a3;

        double d = b * b - 4 * a * c;

        if (d > 0) {

            Complex l1 ((-b + std::sqrt(d)) / (2 * a), 0);
            Complex l2 ((-b - std::sqrt(d)) / (2 * a), 0);
            eigenvalues.push_back(l1);
            eigenvalues.push_back(l2);

        } else if (d == 0) {

            Complex l ((-b) / (2 * a), 0);
            eigenvalues.push_back(l);

        } else {
            Complex l1 ((-b) / (2 * a), std::sqrt(-d) / (2 * a));
            Complex l2 ((-b) / (2 * a), -std::sqrt(-d) / (2 * a));
            eigenvalues.push_back(l1);
            eigenvalues.push_back(l2);
        }
    }

    int Sign(const double &a) {
        return a < 0 ? -1 : a > 0 ? 1 : 0;
    }

};

#endif //LAB1_1_QR_DECOMPOSITION_H
