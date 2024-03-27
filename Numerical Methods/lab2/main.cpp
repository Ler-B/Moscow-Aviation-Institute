#include <iostream>
#include "SimpleIterations.h"
#include "Functions.h"
#include "NewtonMethod.h"
#include "SystemSimpleIterations.h"
#include "systemOfequations.h"
#include "SF.h"
#include "SystemNewtonMethod.h"

int main() {

//    Lab 2.1
    std::cout << "ЗАДАНИЕ 2.1: " << "\n";
    Function func;

    std::pair<double, double> interval(-0.999, -0.799);

    SimpleIterations s(0.0001, interval, func);
    NewtonMethod n(0.0001, interval, func);

    std::cout << "Простые итерации: " << s.Ans() << "\n";
    std::cout << "Количество итераций: " << s.countIter << "\n\n";

    std::cout << "Метод Ньютона: " << n.Ans() << "\n";
    std::cout << "Количество итераций: " << n.countIter << "\n\n";

//    Lab 2.2


    std::cout << "\n\nЗАДАНИЕ 2.2: " << "\n";
    std::pair<Vector, Vector> intr({5, 1}, {6,2});

    SystemOfequations sys(4);

    SystemSimpleIterations s1(0.0001, intr, sys);

    std::cout << "Простые итерации: " << "\n";
    PrintVec("", s1.Ans());
    std::cout << "Количество итераций: " << s1.countIter << "\n\n";



    SystemNewtonMethod n1(0.0001, intr, sys);

    std::cout << "Метод Ньютона: " << "\n";
    PrintVec("", n1.Ans());
    std::cout << "Количество итераций: " << n1.countIter << "\n\n";


}
