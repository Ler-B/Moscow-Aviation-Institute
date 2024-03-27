//
// Created by Валерия Будникова on 15.05.2022.
//

#ifndef H_MET_LAB2_SYSTEMSIMPLEITERATIONS_H
#define H_MET_LAB2_SYSTEMSIMPLEITERATIONS_H


#include <iostream>
#include "systemOfequations.h"
#include "SF.h"

class SystemSimpleIterations{
private:
    double eps;
    std::pair<Vector, Vector> interval;
    SystemOfequations f;
public:
    int countIter;

    SystemSimpleIterations(const double &_eps,const std::pair<Vector, Vector> &_interval,const SystemOfequations &_syst){
        eps = _eps;
        interval = _interval;
        f = _syst;
    }

    Vector Ans() {
        Vector x0 = Vector(2);
        Vector x_k = Vector(2);
        x0[0] = (interval.first[0] + interval.second[0]) / 2;
        x0[1] = (interval.first[1] + interval.second[1]) / 2;

        x_k = x0;

        double q = Make_q();

        double eps_k = Norm(x0 - x_k) * q / (1 - q);

        std::cout << "q = " << q << '\n';

        countIter = 0;

        do {
            Vector x_prev = x_k;
            x_k = f.Phi(x_prev);

            eps_k = Norm(x_prev - x_k) * q / (1 - q);

            ++countIter;
        } while (eps_k > eps);

        return x_k;
    }

    double Make_q() {
        return std::max(Norm(f.J_Phi(interval.first)), Norm(f.J_Phi(interval.second)));
    }

};


#endif //H_MET_LAB2_SYSTEMSIMPLEITERATIONS_H
