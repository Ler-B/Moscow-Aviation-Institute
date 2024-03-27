//Будниква Валерия 207
//Фигура - шестиугольник
//Динамический массив 

#include <cmath>
#include <algorithm>
#include <iostream>
#include "iterator.hpp"
#include "vector.hpp"

void Menu(){
    std::cout << "Введите:\n 1 - Чтобы добавить фигуру\n 2 - Чтобы распечатать все фигуры\n 3 - Вставить по номеру\n";
    std::cout << " 4 - Удалить по номеру\n 5 - Количество фигур, у которых площадь меньше заданной\n 6 - Завершить\n";
}

void Print(){
    std::cout << "Введите координаты верхней точки и длину стороны через пробел: ";
}

int main() {
    Vect<int> Vector;
    auto print = [](const Hexagon<int>& ob){
        std::cout << ob << std::endl << std::endl;
    };
    Menu();
    int x1 = 0, y1 = 0, side = 0;
    int m;
    std::cout << "Введите команду:";
    while (std::cin >> m && m < 6) {
        switch (m) {
            case 1: {
                Print();
                std::cin >> x1 >> y1 >> side;
                if (side < 0) {
                    std::cout << "Введенные значения не верные" << std::endl;
                    break;
                }
                Vector.push_back(Hexagon(x1, y1, side));
                break;
            }
            case 2: {
                std::for_each(Vector.begin(), Vector.end(), print);
                break;
            }
            case 3: {
                int pos;
                std::cout << "Введите номер позиции:";
                std::cin >> pos;
                try {
                    if (pos < 0) {
                        throw std::out_of_range("Iterator cannot be incremented past the end of range.");
                    } else {
                        Print();
                        std::cin >> x1 >> y1 >> side;
                        Vector.insert(Vector.begin() + pos, Hexagon(x1, y1, side));
                    }
                } catch (std::out_of_range &err) {
                    std::cout << err.what();
                }
                break;
            }
            case 4: {
                int pos;
                std::cout << "Введите номер позиции:";
                std::cin >> pos;
                try { 
                    Vector.erase(Vector.begin() + pos);
                } catch (std::out_of_range &error) {
                    std::cout << error.what();
                }
                break;
            }
            case 5: {
                int S;
                std::cout << "Введите площадь:";
                std::cin >> S;
                auto square = [S](const Hexagon<int>& ob){
                    return (3 * sqrt(3) * ob.side * ob.side / 2) < S;
                };
                std::cout << "Кол-во фигур: " << std::count_if(Vector.begin(), Vector.end(), square);
                break;
            }
            default:
                break;
        }
        std::cout << "\nВведите команду:";
    }        
    return 0;
}
