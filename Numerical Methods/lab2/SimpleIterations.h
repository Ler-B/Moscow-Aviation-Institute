#include <iostream>
#include "Functions.h"


#ifndef H_MET_LAB2_SIMPLEITERATIONS_H
#define H_MET_LAB2_SIMPLEITERATIONS_H

class SimpleIterations{
private:
    double eps;
    std::pair<double, double> interval;
    Function func;
public:
    int countIter;

    SimpleIterations(const double &_eps,const std::pair<double, double> &_interval,const Function &function){
        eps = _eps;
        interval = _interval;
        func = function;
    }

    double Ans() {
        countIter = 0;

        double x0 = (interval.first + interval.second) / 2;

        double q = Make_q(interval.first, interval.second, x0);
        double epsK = q * std::abs(x0 - interval.first);
        if (q < 1) epsK /= (1 - q);

        FixInt(x0, interval);
        double xk_prev = x0;

        while (epsK > eps) {
            ++countIter;
            double xk = xk_prev - func.f(xk_prev) / func.der(x0);

            q = Make_q(interval.first, interval.second, x0);
            epsK = q * std::abs(xk - xk_prev);
            if (q < 1) epsK /= (1 - q);

            FixInt(xk, interval);
            xk_prev = xk;
        }
        return  xk_prev;
    }

    void FixInt(double &x, std::pair<double, double> &intr) {
        if (func.f(x) * func.der(intr.first) > 0) {
            intr.first = x;
        } else {
            intr.second = x;
        }
    }

    double Make_q(const double &a, const double &b, const double &x0) {
        double q1 = std::abs(1 - func.der(a) / func.der(x0));
        double q2 = std::abs(1 - func.der(b) / func.der(x0));

        return std::max(q1, q2);
    }

};

#endif //H_MET_LAB2_SIMPLEITERATIONS_H
