#include <iostream>
#include <vector>
#include <string>
#include "Supportive_Functions.h"
#include "LU_Decomposition.h"
#include "Tridiagonal_Matrix_Algorithm.h"
#include "Simple_Iteration_Method.h"
#include "Zeidel_Method.h"
#include "Rotation_Method.h"
#include "QR_Algorithm.h"

std::vector<double> b;
std::vector<std::vector<double>> a;

void Task1_1() {
    std::cout << "\n\nЗАДАНИЕ 1.1\n";
    Readout(a, b);

    PrintMatrix("A", a);
    PrintVec("b:", b);


    LU_Decomposition dec(a);
    std::cout << "LU-разложение:" << "\n";
    dec.PrintElements();
    PrintVec("x : ", dec.Solve(b));
}

void Task1_2() {
    std::cout << "\n\nЗАДАНИЕ 1.2\n";

    Readout(a, b);

    PrintMatrix("A", a);
    PrintVec("d:", b);


    Tridiagonal_Matrix_Algorithm pr(a, b);
    LU_Decomposition dec2(a);

    std::cout << "Метод прогонки:" << "\n";
    //    pr.PrintElements();
    pr.PrintAnswer();

    std::cout << "LU-разложение:" << "\n";
    PrintVec("x:", dec2.Solve(b));
}

void Task1_3() {
    std::cout << "\n\nЗАДАНИЕ 1.3\n";
    double eps;

    Readout(a, b);

//  std::cout << "Введите точность:";
    std::cin >> eps;

    PrintMatrix("\nA", a);
    PrintVec("d:", b);
    std::cout << "точность:" << eps << "\n\n";

    Simple_Iteration_Method iter_met(a, b, eps);
    Zeidel_Method zen(a, b, eps);
    LU_Decomposition dec3(a);

    std::cout << "Метод простой итерации:" << "\n";
    iter_met.PrintAnswer();
    iter_met.PrintAnalysis();

    std::cout << "Метод Зейделя:" << "\n";
//    zen.PrintElements();
    zen.PrintAnswer();
    zen.PrintAnalysis();

    std::cout << "LU-разложение:" << "\n";
    PrintVec("x:", dec3.Solve(b));
}

void Task1_4() {
    std::cout << "\n\nЗАДАНИЕ 1.4\n";

    double eps;
    Readout(a);
//    std::cout << "Введите точность:";
    std::cin >> eps;

    PrintMatrix("\nA", a);
    std::cout << "точность:" << eps << "\n\n";

    Rotation_Method rot(a, eps);
    rot.PrintAnswer();
}

void Task1_5() {
    std::cout << "\n\nЗАДАНИЕ 1.5\n";

    double eps;
    Readout(a);
//    std::cout << "Введите точность:";
    std::cin >> eps;

    PrintMatrix("\nA", a);
    std::cout << "точность:" << eps << "\n\n";

    QR_Algorithm qr(a, eps);
    qr.PrintElements();
}


int main() {

    Task1_1();

    Task1_2();

    Task1_3();

    Task1_4();

    Task1_5();


    return 0;
}
