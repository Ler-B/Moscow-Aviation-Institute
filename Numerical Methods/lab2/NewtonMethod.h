#include <iostream>
#include "Functions.h"

#ifndef H_MET_LAB2_NEWTONMETHOD_H
#define H_MET_LAB2_NEWTONMETHOD_H

class NewtonMethod {
private:
    double eps;
    std::pair<double, double> interval;
    Function func;
public:
    int countIter;

    NewtonMethod(const double &_eps,const std::pair<double, double> &_interval,const Function &function){
        eps = _eps;
        interval = _interval;
        func = function;
    }

    double Ans() {
        countIter = 0;
        double epsK = std::abs(interval.first - interval.second);

        double xk_prev = interval.first;
        if (func.f(interval.second) * func.der2(interval.second) > 0) {
            xk_prev = interval.second;
        }

        while(epsK > eps) {

            ++countIter;

            double xk = xk_prev  - func.f(xk_prev) / func.der(xk_prev);

            epsK = std::abs(xk - xk_prev);

            xk_prev = xk;
        }

        return xk_prev;
    }

};

#endif //H_MET_LAB2_NEWTONMETHOD_H
