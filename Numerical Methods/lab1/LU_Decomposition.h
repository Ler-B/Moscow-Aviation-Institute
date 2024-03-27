#include <iostream>
#include <vector>
#include <string>
//#include "Supportive_Functions.h"


#ifndef LAB1_1_LU_DECOMPOSITION_H
#define LAB1_1_LU_DECOMPOSITION_H

class LU_Decomposition {
private:
    int n;
    std::vector<std::vector<double>> a;
    std::vector<std::vector<double>> l;
    std::vector<std::vector<double>> u;

    std::vector<std::vector<double>> p;


public:
    LU_Decomposition(const std::vector<std::vector<double>> &_a) {

        if (_a.size() != _a[0].size()) throw "Wrong matrix size";

        n = _a.size();

        a = _a;
        l = std::vector<std::vector<double>> (n, std::vector<double>(n, 0));
        u = std::vector<std::vector<double>> (n, std::vector<double>(n, 0));

        p = E(n);

        Make_L_and_U();

    }

    void PrintElements() {
        PrintMatrix("A:", a);
        PrintMatrix("L:", l);
        PrintMatrix("U:", u);


        PrintMatrix("L * U", l * u);

        if (p != E(n)) PrintMatrix("P:", p);
    }

    std::vector<double> Solve(const std::vector<double> &b) {
        if (b.size() != n) throw "Wrong vector size";

        std::vector<double> z = Make_z(b);

        return Make_x(z);
    }

private:
    void Make_L_and_U() {
        std::vector<std::vector<double>> ak;
        ak = a;
        int ind = FindMaxInd(ak, 0);
        ChangeStr(ak, 0, ind);
        ChangeStr(l, 0, ind);
        ChangeStr(p, 0, ind);

        l[0][0] = 1;
        for(int k = 1; k < n; ++k) {

            ind = FindMaxInd(a, k);
            ChangeStr(ak, k, ind);
            ChangeStr(l, k, ind);
            ChangeStr(p, k, ind);

            std::vector<std::vector<double>> new_a = ak;

            for (int i = k; i < n; ++i) {

                double mu = 0;
                bool fl = false;

                for (int j = k - 1; j < n; ++j) {
                    if (!fl) {
                        mu =  ak[i][j] / ak[k - 1][k - 1];
                        if (i > j) l[i][j] = mu;
                    }
                    fl = true;
                    if (i == j) l[i][j] = 1;

                    new_a[i][j] = ak[i][j] - mu * ak[k - 1][j];
                }
            }
            ak = new_a;
        }
        u = ak;
    }

    int FindMaxInd(const std::vector<std::vector<double>> &m, const int &stl) {
        double max = std::abs(m[stl][stl]);
        int ind = stl;
        for (int i = 0; i < n ; ++i) {
            if (std::abs(m[i][stl]) > max) {
                max = std::abs(m[i][stl]);
                ind = i;
            }
        }
        return ind;
    }

    std::vector<double> Make_z(const std::vector<double> &b) {
        std::vector<double> z(n);

        z[0] = b[0];
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < i; ++j) {
                sum += l[i][j] * z[j];
            }

            z[i] = b[i] - sum;
        }
        return z;
    }


    std::vector<double> Make_x(const std::vector<double> &z) {
        std::vector<double> x(n);

        for (int i = n - 1; i > -1; --i) {
            double sum = 0;
            for (int j = n - 1; j > i; --j) {
                sum += u[i][j] * x[j];
            }
            x[i] = (z[i] - sum) / u[i][i];
        }

        return x;
    }

};







#endif //LAB1_1_LU_DECOMPOSITION_H
