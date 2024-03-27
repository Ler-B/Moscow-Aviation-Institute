//
// Created by Валерия Будникова on 16.05.2022.
//

#ifndef H_MET_LAB2_SYSTEMNEWTONMETHOD_H
#define H_MET_LAB2_SYSTEMNEWTONMETHOD_H

#include <iostream>
#include "systemOfequations.h"
#include "SF.h"
#include "LU_Decomposition.h"

class SystemNewtonMethod {
private:
    double eps;
    std::pair<Vector, Vector> interval;
    SystemOfequations f;
public:
    int countIter;

    SystemNewtonMethod(const double &_eps,const std::pair<Vector, Vector> &_interval,const SystemOfequations &syst){
        eps = _eps;
        interval = _interval;
        f = syst;
    }

    Vector Ans() {

        double epsK = Norm(interval.first - interval.second);

        Vector xk_prev = interval.first;

        countIter = 0;
        while(epsK > eps) {

            ++countIter;

            LU_Decomposition lu(f.J_f(xk_prev));

            Vector delt_x = lu.Solve( -1 * f.f(xk_prev));

            Vector xk = xk_prev  - delt_x;

            epsK = Norm(delt_x);

            xk_prev = xk;
        }

        return xk_prev;
    }

};


#endif //H_MET_LAB2_SYSTEMNEWTONMETHOD_H
