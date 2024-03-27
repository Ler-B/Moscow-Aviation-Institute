//
// Created by Валерия Будникова on 11.04.2022.
//
#include <cmath>

#ifndef H_MET_LAB2_SUPPORTIVE_FUNCTIONS_H
#define H_MET_LAB2_SUPPORTIVE_FUNCTIONS_H

class Function{
public:
    Function(){}

    double f(double x) {
        return std::sqrt(1 - x*x) - std::exp(x) + 0.1;
    }

    double der(double x){
        return -x / std::sqrt(1 - x*x) - std::exp(x);
    }

    double der2(double x) {
        return -1 / std::pow(1 - x * x, 3/2) - std::exp(x);
    }
};




#endif //H_MET_LAB2_SUPPORTIVE_FUNCTIONS_H
