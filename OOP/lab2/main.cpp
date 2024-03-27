//Будникова Валерия M8O-207Б-19
//Вариант 20 
//Создать класс Bottle для работы с емкостями. Класс должен состоять из двух вещественных чисел: a- объем емкости в литрах и b – процент наполнения емкости (0 – пустая, 1 – полная). Реализовать операции сложения и вычитания, а также сравнения объектов класса бутылка в виде перегрузки операторов. При сложении должен складываться фактический объем заполнения бутылок. 
//Необходимо реализовать пользовательский литерал для работы с константами типа Bottle
#include "bottle.hpp"
#include <iostream>

int main() {
    Bot::Bottle b = "25,0.65"_bt;
    std::cout << "Объект, созданный с помощью литерала:\t" << b << std::endl;
    double v1;
    double fill1;
    double v2;
    double fill2;
    Bot::Bottle bot1, bot2;
    while(std::cin >> v1 >> fill1 >> v2 >> fill2) {
        std::cout << std::endl << "Bottle1: ";
        bot1 = Bot::Bottle(v1, fill1);
        std::cout << bot1 << std::endl;

        std::cout << "Bottle2: ";
        bot2 = Bot::Bottle(v2, fill2);
        std::cout << bot2 << std::endl;

        std::cout << std::endl << "СУММА:\t";
        std::cout << bot1 + bot2 << std::endl;

        std::cout << std::endl << "РАЗНОСТЬ:\t";
        std::cout << bot1 - bot2 << std::endl;

        std::cout << std::endl << "ОТНОШЕНИЕ:\t";
        if (bot1 > bot2) {
            std::cout << "Bottle1 > Bottle2" << std::endl;
        }
        if (bot1 < bot2) {
            std::cout << "Bottle1 < Bottle2" << std::endl;
        }
        if (bot1 == bot2) {
            std::cout << "Bottle1 = Bottle2" << std::endl;
        }
    }
}