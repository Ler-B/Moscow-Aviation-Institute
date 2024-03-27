//Будникова Валерия M8O-207Б-19
//Реализация класса Bottle
#include "bottle.hpp"

namespace Bot
{
    Bottle::Bottle() {
        v = 0;
        fill = 0;
    }

    Bottle::Bottle(const double& a, const double& b) {
        if (a >= 0 && b >= 0 && b <= 1) {
            v = a;
            fill = b;
        } else {
            v = 0;
            fill = 0;
            std::cout << "Неправильные значения для Bottle. ";
        }
    }

    const Bottle Bottle::operator+(const Bottle& b) {
        if (v == 0 && fill == 0) {
            return b;
        }
        Bottle rez;
        rez.v = v + b.v;
        rez.fill = (v * fill + b.v * b.fill) / (v + b.v);
        return rez;
    }

    const Bottle Bottle::operator-(const Bottle& b) {
        if (v * fill < b.v * b.fill) {
            std::cout << "Нельзя вычесть больший объем из меньшего. ";
            return Bottle(0,0);
        }
        if (v == 0 && fill == 0) {
            return Bottle(0,0);
        }
        Bottle rez;
        rez.v = v;
        rez.fill = (v * fill - b.v * b.fill) / v;
        return rez;
    }

    bool Bottle::operator<(const Bottle& b) {
        return(v < b.v);
    }

    bool Bottle::operator>(const Bottle& b) {
        return(v > b.v);
    }

    bool Bottle::operator==(const Bottle& b) {
        if (v == b.v && fill == b.fill) {
            return true;
        } else {
            return false;
        }
    }
    std::ostream& operator<<(std::ostream& os, const Bottle& b){
        os << "Volume: " << b.v << "\t" << "Filled: " << b.fill;
        return os;
    }
}

Bot::Bottle operator"" _bt(const char* str, size_t n){
    double a = 0;
    double temp = 1;
    double v[2];
    short c = 0;
    int f = 0;
    for(int i = 0; i < n; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (f == 0){
                a += (str[i] - '0') * temp;
                temp *= 10;
            } else {
                temp /= 10;
                a += (str[i] - '0') * temp; 
            }
        } else {
            if (str[i] == '.') {
                temp = 1;
                f = 1;
            } else if (str[i] == ','){
                v[c] = a;
                a = 0;
                temp = 1;
                ++c;
            }
        }
        if ((str[i] < '0' || str[i] > '9') && str[i] != ',' && str[i] != '.') {
            temp = -1;
            v[0] = -1;
            v[1] = -1;
        }
    }
    v[c] = a;
    return Bot::Bottle(v[0], v[1]);
}




