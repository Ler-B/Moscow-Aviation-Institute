//Будникова Валерия M8O-207Б-19
//Реализация класса Long
#include "classlong.hpp"

namespace Long
{
    Long::Long() {
        field1 = 0;
        field2 = 0;
    }
    
    Long::Long(const unsigned long long a) {
        field1 = a >> 32;
        field2 = a & 0xffffffff;
    }

    Long::Long(const unsigned int a, const unsigned int b) {
        field1 = a;
        field2 = b;
    }

    Long::~Long() {}

    const Long Long::operator=(const unsigned long long a) {
        Long num(a);
        return num;
    }
    
    void Long::Print(){
        unsigned long long rez = field1;
        rez = (rez << 32) + field2;
        std::cout << rez << std::endl;
    }
    
    const Long Long::operator+(const Long &b) {
        Long rez;
        rez.field2 = field2 + b.field2;
        if (((((field2 >> 1) + (b.field2 >> 1)) + ((field2 & 1)&(b.field2 & 1))) >> 31) == 1) {
            rez.field1 = field1 + b.field1 + 1;
        } else {
            rez.field1 = field1 + b.field1;
        }
        return rez;
    }
    
    bool Long::operator>(const Long &b) const {
        if (field1 > b.field1) {
            return true;
        }
        if (field1 == b.field1 && field2 > b.field2) {
            return true;
        }
        return false;
    }

    bool Long::operator<(const Long &b) const {
        if (field1 < b.field1) {
            return true;
        }
        if (field1 == b.field1 && field2 < b.field2) {
            return true;
        }
        return false;
    }
    
    bool Long::operator==(const Long &b) const {
        if (field1 == b.field1 && field2 == b.field2) {
            return true;
        }
        return false;
    }

    const Long Long::operator-(const Long &b) {
        Long rez;
        if (field1 < b.field1) {
            std::cout << "Ошибка! Получается отрицательное число.";
            return rez;
        }
        if (field1 == b.field1 && field2 < b.field2) {
            std::cout << "Ошибка! Получается отрицательное число.";
            return rez;
        }
        
        if (field2 > b.field2) {
            rez.field2 = field2 - b.field2;
            rez.field1 = field1 - b.field1;
        }
        if (field2 < b.field2) {
            rez.field1 = field1 - b.field1 - 1;
            unsigned int s = b.field2 - field2;
            int count = 0;
            while ((s & 1) != 1) {
                s = s >> 1;
                count++;
            }
            rez.field2 = (((((0xffffffff) >> count << count) - (b.field2 - field2)) >> count) + 1) << count;
        }
        return rez;
    }

    const Long Long::Multiplication_without_longlong(const Long &b) {
        Long rez;
        if (field1 != 0 && b.field1 != 0) {
            std::cout << "Ошибка! Переполнение.";
            return rez;
        }
        for (unsigned int i = 0; i < field2; ++i) {
            rez = rez + b;
            if ((rez.field1 & 0xffffffff) == 0xffffffff) {
                std::cout << "Ошибка! Переполнение.";
                return rez;
            }
        }
        return rez;

    }

    const Long Long::operator*(const Long &b) {
        Long rez;
        unsigned long long a1 = field1;
        unsigned long long a2 = b.field1;
        a1 = (a1 << 32) + field2;
        a2 = (a2 << 32) + b.field2;
        a1 *= a2;
        rez.field1 = a1 >> 32;
        rez.field2 = a1 & 0xffffffff;
        return rez;
    }

    const Long Long::Division_without_longlong(const Long &b) {
        Long rez;
        Long temp;
        const Long temp2(1);
        temp.field1 = field1;
        temp.field2 = field2;
        if (b > temp) {
            return rez;
        }
        if (rez == b) {
            std::cout << "Ошибка! Делить на ноль нельзя.";
            return rez;
        }
        while ((b < temp) || (b == temp)) {
            temp = temp - b;
            rez = rez + temp2;
        }
        return rez;
    }

    const Long Long::operator/(const Long &b) {
        Long rez;
        unsigned long long a1 = field1;
        unsigned long long a2 = b.field1;
        a1 = (a1 << 32) + field2;
        a2 = (a2 << 32) + b.field2;
        if (a1 < a2) {
            return rez;
        }
        if (rez == b) {
            std::cout << "Ошибка! Делить на ноль нельзя.";
            return rez;
        }
        a1 /= a2;
        rez.field1 = a1 >> 32;
        rez.field2 = a1 & 0xffffffff;
        return rez;
    }

    const Long Long::RemainderOfDivision_without_longlong(const Long &b) {
        Long rez;
        rez.field1 = field1;
        rez.field2 = field2;
        if (rez < b) {
            rez.field1 = field1;
            rez.field2 = field2;
        }
        if (b.field1 == 0 && b.field2 == 0) {
            std::cout << "Ошибка! Делить на ноль нельзя.";
            return rez;
        }
        while ((b < rez) || (b == rez)) {
            rez = rez - b;
        }
        return rez;
    }

    const Long Long::operator%(const Long &b) {
        Long rez;
        unsigned long long a1 = field1;
        unsigned long long a2 = b.field1;
        a1 = (a1 << 32) + field2;
        a2 = (a2 << 32) + b.field2;
        if (a1 < a2) {
            rez.field1 = field1;
            rez.field2 = field2;
        }
        if (rez == b) {
            std::cout << "Ошибка! Делить на ноль нельзя.";
            return rez;
        }
        a1 %= a2;
        rez.field1 = a1 >> 32;
        rez.field2 = a1 & 0xffffffff;
        return rez;
    }

    std::ostream& operator<<(std::ostream &os, const Long& b) {
        unsigned long long a = b.field1;
        a = (a << 32) + b.field2;
        os << a;
        return os;
    }

}