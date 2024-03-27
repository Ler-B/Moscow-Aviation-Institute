//Будниква Валерия 207
//Фигура - шестиугольник
//Динамический массив для коллекции фигур
//Стек для указателей на блоки памяти

#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include "iterator.hpp"
#include "vector.hpp"
#include "allocator.hpp"

const std::size_t BLOCK_SIZE  = 10000;

void Menu(){
    std::cout << "Введите:\n 1 - Добавить фигуру\n 2 - Распечатать все фигуры\n 3 - Вставить по номеру\n";
    std::cout << " 4 - Удалить по номеру\n 5 - Завершить\n";
}

void Print(){
    std::cout << "Введите координаты верхней точки и длину стороны через пробел: ";
}


int main() {
    std::vector<int, Allocator<int, BLOCK_SIZE>> vect;

    for (int i = 0; i < 100; ++i) {
       vect.push_back(i+2);
    }
    auto print = [](const int & a)  {
        std::cout << a << a << a << std::endl;
    };

    std::for_each(vect.begin(), vect.end(), print);
    
    // using Hex = Hexagon<int, Allocator<int, BLOCK_SIZE>>;
    // Fig<Hex, Allocator<Hex,BLOCK_SIZE>> Vector;
    // Menu();
    // int x1 = 0, y1 = 0, side = 0;
    // int m;
    // auto print = [](const Hex & ob){
    //     std::cout << ob << std::endl << std::endl;
    // };
    // std::cout << "Введите команду:";
    // while (std::cin >> m && m < 5) {
    //     switch (m) {
    //         case 1: {
    //             Print();
    //             std::cin >> x1 >> y1 >> side;
    //             if (side < 0) {
    //                 std::cout << "Введенные значения не верные" << std::endl;
    //                 break;
    //             }
    //             try {
    //                 Vector.push_back(Hex(x1, y1, side));
    //             } catch (const std::bad_alloc &er) {
    //                 std::cout << er.what() << std::endl;
    //             }
    //             break;
    //         }
    //         case 2: {
    //             std::for_each(Vector.begin(), Vector.end(), print);
    //             break;
    //         }
    //         case 3: {
    //             int pos;
    //             std::cout << "Введите номер позиции:";
    //             std::cin >> pos;
    //             try {
    //                 if (pos < 0) {
    //                     throw std::out_of_range("Iterator cannot be incremented past the end of range.");
    //                 } else {
    //                     Print();
    //                     std::cin >> x1 >> y1 >> side;
    //                     Vector.insert(Vector.begin() + pos, Hex(x1, y1, side));
    //                 }
    //             } catch (std::out_of_range &err) {
    //                 std::cout << err.what();
    //             }
    //             break;
    //         }
    //         case 4: {
    //             int pos;
    //             std::cout << "Введите номер позиции:";
    //             std::cin >> pos;
    //             try { 
    //                 Vector.erase(Vector.begin() + pos);
    //             } catch (std::out_of_range &error) {
    //                 std::cout << error.what();
    //             }
    //             break;
    //         }
    //         default:
    //             break;
    //     }
    //     std::cout << "\nВведите команду:";
    // }        
    // return 0;
}
