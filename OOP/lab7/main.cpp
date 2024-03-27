//Будникова Валерия Павловна 
//Варианты фигур - Треульльник, Шестиугольник, Восьмиугольник
//Задание - Спроектировать простейший «графический» векторный редактор. 

#include <iostream>
#include <algorithm>
#include <stack>
#include <execution>
#include "figure.hpp"
#include "triangle.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"

template<class A, class B, class C>
class Factory {
    public:
    Factory() {}
    ~Factory() {}
    std::shared_ptr<Figure> Triangle(double x1, double y1, int side) {
        return std::make_shared<A>(x1, y1, side);
    }
    std::shared_ptr<Figure> Hexagon(double x1, double y1, int side) {
        return std::make_shared<B>(x1, y1, side);
    }
    std::shared_ptr<Figure> Octagon(double x1, double y1, int side) {
        return std::make_shared<C>(x1, y1, side);
    }
};


void Menu(){
    std::cout << "Введите:\n 1  - создание нового документа\n 2  - импорт документа из файла\n 3  - экспорт документа в файл\n";
    std::cout << " 4  - добавить треугольник\n 5  - добавить шестиугольник\n 6  - добавить восьмиугольник\n";
    std::cout << " 7  - удалить фигуру по индексу\n 8  - печать на экран фигур \n 9  - отменить последнее действие\n 10 - завершить программу\n";
}

void Print(){
    std::cout << "Введите координаты верхней точки и длину стороны через пробел: ";
}

struct Memento {
    std::vector<std::shared_ptr<Figure>> state;
    Memento() {}
    Memento(const std::vector<std::shared_ptr<Figure>> &other) : state({other}) {}
    ~Memento() {}
};

struct Action {
    std::stack<Memento> temp;
    void Save(std::vector<std::shared_ptr<Figure>>  fignext) {
        temp.emplace(fignext);
    }
    std::vector<std::shared_ptr<Figure>> Undo() {
        if (!temp.empty()) {
            std::vector<std::shared_ptr<Figure>> res = temp.top().state;
            temp.pop();
            return res;
        } else {
            throw std::logic_error("err");
        }
    }
};

int main() {
    Action doo;
    double x1, y1;
    int side, m;
    std::vector<std::shared_ptr<Figure>> fig;
    Factory<Triangle, Hexagon, Octagon> addfigure;
    Menu();
    FILE * f;
    std::cout << "Введите команду:";
    while (std::cin >> m && m < 10 && m > 0) {
        switch (m) {
            case 1: {
                doo.Save(fig);
                fig.clear();
                //создание нового документа(очистка)
                break;
            }
            case 2: {
                //импорт документа из файла 
                doo.Save(fig);
                fig.clear();
                int a;
                std::string name;
                std::cout << "Введите файла:";
                std::cin >> name;
                f = fopen(name.c_str(), "r");
                if (f == NULL) {
                    std::cout << "Ошибка открытия файла";
                    break;
                }
                bool fl = true;
                while (!feof(f)) {
                    fread(&a, sizeof(int), 1, f);
                    fread(&x1, sizeof(double), 1, f);
                    fread(&y1, sizeof(double), 1, f);
                    fread(&side, sizeof(int), 1, f);
                    switch (a) {
                    case 1: {
                        fig.push_back(addfigure.Triangle(x1, y1, side));
                        break;
                    }
                    case 2: {
                        fig.push_back(addfigure.Hexagon(x1, y1, side));
                        break;
                    }
                    case 3: {
                        fig.push_back(addfigure.Octagon(x1, y1, side));
                        break;
                    }
                    default:
                        break;
                    }
                    a = -1;
                }
                fclose(f);
                break;
            }
            case 3: {
                //экспорт документа в файл
                std::string name;
                std::cout << "Введите файла:";
                std::cin >> name;
                f = fopen(name.c_str(), "w");
                if (f == NULL) {
                    std::cout << "Ошибка открытия файла"<< std::endl;
                    break;
                }
                for (int i = 0; i < fig.size(); ++i) {
                    int a;
                    if (fig[i]->Name() == "Triangle" ) a = 1;
                    if (fig[i]->Name() == "Hexagon" ) a = 2;
                    if (fig[i]->Name() == "Octagon" ) a = 3;
                    fwrite(&a, sizeof(int), 1, f);
                    std::vector<Pair> temp = fig[i]->Coord();
                    fwrite(&temp[0].x, sizeof(double), 1, f);
                    fwrite(&temp[0].y, sizeof(double), 1, f);
                    int b = fig[i]->Get();
                    fwrite(&b, sizeof(int), 1, f);
                }
                fclose(f);
                break;
            }
            case 4: {
                Print();
                std::cin >> x1 >> y1 >> side;
                if (side < 0) {
                    std::cout << "Введенные значения не верные! Длина не может быть отрицательной."<< std::endl;
                    break;
                }
                doo.Save(fig);
                fig.push_back(addfigure.Triangle(x1, y1, side));
                break;
            }
            case 5: {
                Print();
                std::cin >> x1 >> y1 >> side;
                if (side < 0) {
                    std::cout << "Введенные значения не верные! Длина не может быть отрицательной."<< std::endl;
                    break;
                }
                doo.Save(fig);
                fig.push_back(addfigure.Hexagon(x1, y1, side));
                break;
            }
            case 6: {
                Print();
                std::cin >> x1 >> y1 >> side;
                if (side < 0) {
                    std::cout << "Введенные значения не верные! Длина не может быть отрицательной." << std::endl;
                    break;
                }
                
                doo.Save(fig);
                fig.push_back(addfigure.Octagon(x1, y1, side));
                break;
            }
            case 7: {
                int ind;
                std::cout << "Введите индекс:";
                std::cin >> ind;
                doo.Save(fig);
                if (ind <= 0 || ind >= fig.size() + 1) {
                    std::cout << "Введенные значения не верные" << std::endl;
                    break;
                }
                ind--;
                fig.erase(fig.begin() + ind);
                break;
            }
            case 8: {
                std::cout << fig;
                break;
            }
            case 9: {
                fig = doo.Undo();
                std::cout << std::endl;
                break;
            }
            default:
                break;
        }
        std::cout << "Введите команду:";
    }
}