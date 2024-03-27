//
// Created by Валерия Будникова on 16.05.2022.
//

#ifndef H_MET_LAB2_SF_H
#define H_MET_LAB2_SF_H

#include <string>
#include <vector>
#include <iostream>

#include <cmath>

using Vector = std::vector<double>;
using Matrix = std::vector<Vector>;
using Complex = std::pair<double, double>;

void PrintMatrix(const std::string str, const Matrix &a) {
    std::cout << str << "\n";
    for(int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[0].size(); ++j) {
            std::cout.precision(3);
            std::cout << a[i][j] << "\t\t\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void PrintVec(const std::string str, const Vector &a) {
    std::cout << str << "  ";
    for(double i : a) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

double Norm(const Matrix m) {
    double sum = 0;
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[0].size(); ++j) {
            sum += pow(m[i][j], 2);
        }
    }
    return sqrt(sum);
}

double Norm(const Vector &v) {
    double sum = 0;
    for (double i : v) {
        sum += pow(std::abs(i), 2);
    }
    return sqrt(sum);
}

Vector operator*(const Matrix &m,  const Vector &v ) {

    Vector ans(v.size(), 0);
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[0].size(); ++j) {
            ans[i] += m[i][j] * v[j];
        }
    }

    return ans;
}

Vector operator*(const double &a,  const Vector &v ) {

    Vector ans = v;

    for (auto el: ans) {
        el *= a;
    }

    return ans;
}

Matrix operator*(const Matrix &m1,  const Matrix &m2 ) {

    if (m1.size() != m2[0].size()) throw "operator* : Wrong matrix sizes";

    Matrix res(m1.size(), Vector(m2[0].size(), 0));

    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[0].size(); ++j) {
            for (int k = 0; k < m1[0].size(); ++k) {
                res[i][j] += m1[i][k]*m2[k][j];
            }
        }
    }

    return res;
}

Matrix operator+(const Matrix &m1,  const Matrix &m2 ) {

    if (m1.size() != m2.size()) throw "operator* : Wrong matrix sizes";

    Matrix res(m1.size(), Vector(m2.size(), 0));

    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[0].size(); ++j) {
            res[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return res;
}

Matrix operator-(const Matrix &m1,  const Matrix &m2 ) {

    if (m1.size() != m2.size()) throw "operator* : Wrong matrix sizes";

    Matrix res(m1.size(), Vector(m2.size(), 0));

    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[0].size(); ++j) {
            res[i][j] = m1[i][j] - m2[i][j];
        }
    }

    return res;
}

Vector operator+(const Vector &v1,  const Vector &v2 ) {

//    if (v1.size() != v2.size()) throw "operator+ : Wrong vector size";

    Vector ans(v1.size(), 0);
    for (int i = 0; i < v1.size(); ++i) {
        ans[i] = v1[i] + v2[i];
    }

    return ans;
}

Vector operator-(const Vector &v1,  const Vector &v2 ) {

//    if (v1.size() != v2.size()) throw "operator+ : Wrong vector size";

    Vector ans(v1.size(), 0);
    for (int i = 0; i < v1.size(); ++i) {
        ans[i] = v1[i] - v2[i];
    }

    return ans;
}

double Scalar(const Vector &v1,  const Vector &v2) {
    double res = 0;
    for (int i = 0; i < v1.size(); ++i) {
        res += v1[i] * v2[i];
    }
    return res;
}

Matrix operator*(const Vector &v1,  const Vector &v2 ) {
    Matrix res = Matrix(v1.size(), Vector(v2.size(), 0));
    for(int i = 0; i < v1.size(); ++i) {
        for (int j = 0; j < v2.size(); ++j) {
            res[i][j] = v1[i] * v2[j];
        }
    }
    return res;
}


Matrix operator*(const Matrix m, const double a ) {
    Matrix res(m.size(), Vector(m[0].size()));
    for (int i = 0; i < m.size(); ++i) {
        for(int j = 0; j < m[0].size(); ++j) {
            res[i][j] = m[i][j] * a;
        }
    }
    return res;
}

Matrix operator*(const double a, const Matrix m) {
    Matrix res(m.size(), Vector(m[0].size()));
    for (int i = 0; i < m.size(); ++i) {
        for(int j = 0; j < m[0].size(); ++j) {
            res[i][j] = m[i][j] * a;
        }
    }
    return res;
}

Matrix E(const int &n) {
    Matrix e = Matrix(n, Vector(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) e[i][j] = 1;
        }
    }
    return e;
}

void ChangeStr(Matrix &a, const int &st1, const int &st2) {
    if (st1 != st2) for (int i = 0; i < a.size(); ++i) {
            std::swap(a[st1][i], a[st2][i]);
        }
}

Matrix NewStrChange(Matrix a, const int &st1, const int &st2) {
    if (st1 != st2) for (int i = 0; i < a.size(); ++i) {
            std::swap(a[st1][i], a[st2][i]);
        }
    return a;
}

std::ostream& operator << (std::ostream &os, const Complex &c) {
    return os << c.first << " + i*(" << c.second << ")";
}

#endif //H_MET_LAB2_SF_H
