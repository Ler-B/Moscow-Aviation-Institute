#include <iostream>
#include "figure.hpp"
#include "triangle.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"

void Menu(){
    std::cout << "Введите:\n 1 - Чтобы добавить треугольник\n 2 - чтобы добавить шестиугольник\n 3 - чтобы добавить восьмиугольник\n";
    std::cout << " 4 - чтобы удалить элемент по индексу\n 5 - распечатать вектор\n 6 - выдвть общую площадь фигур\n 7 - завершить программу\n";
}

void Print(){
    std::cout << "Введите координаты верхней точки и длину стороны через пробел: ";
}

std::ostream& operator<<(std::ostream &os, Pair p) {
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}

std::ostream& operator<<(std::ostream &os, std::vector<Pair> p) {
    for (int i = 0; i < p.size(); ++i) {
        os << " " << p[i];
    }
    return os;
}

int main() {
    std::string name;
    double x1, y1;
    int side, m;
    std::vector<Figure *> fig;
    Menu();
    std::cout << "Введите команду:";
    while (std::cin >> m && m < 7) {
        switch (m) {
            case 1: {
                Print();
                std::cin >> x1 >> y1 >> side;
                if (side < 0) {
                    std::cout << "Введенные значения не верные" << std::endl;
                    break;
                }
                Figure * triangle = new Triangle(x1, y1, side);
                fig.push_back(triangle);
                break;
            }
            case 2: {
                Print();
                std::cin >> x1 >> y1 >> side;
                if (side < 0) {
                    std::cout << "Введенные значения не верные" << std::endl;
                    break;
                }
                Figure * hexagon = new Hexagon(x1, y1, side);
                fig.push_back(hexagon);
                break;
            }
            case 3: {
                Print();
                std::cin >> x1 >> y1 >> side;
                if (side < 0) {
                    std::cout << "Введенные значения не верные" << std::endl;
                    break;
                }
                Figure * octagon = new Octagon(x1, y1, side);
                fig.push_back(octagon);
                break;
            }
            case 4: {
                int ind;
                std::cout << "Введите индекс:";
                std::cin >> ind;
                if (ind <= 0 || ind >= fig.size() + 1) {
                    std::cout << "Введенные значения не верные" << std::endl;
                    break;
                }
                ind--;
                fig.erase(fig.begin() + ind);
                break;
            }
            case 5: {
                 for (int i = 0; i < fig.size(); ++i) {
                     std::cout << std::endl;
                     std::cout << "ФИГУРА - " << fig[i]->Name() << std::endl;
                     std::cout << "КООРДИНАТЫ:" << fig[i]->Coord() << std::endl;
                     std::cout << "РАДИУС ВЕКТОР: " << fig[i]->Radius_vector() << std::endl;
                     std::cout << "ПЛОЩАДЬ: " << fig[i]->S() << std::endl;
                 }
                break;
            }
            case 6: {
                double s = 0;
                for (int i = 0; i < fig.size(); ++i) {
                     s += fig[i]->S();
                }
                std::cout << std::endl << "ОБЩАЯ ПЛОЩАДЬ: " << s << std::endl;
                break;
            }
            default:
                break;
        }
        std::cout << "\nВведите команду:";
    }
}
