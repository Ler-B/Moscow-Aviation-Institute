//Будникова Валерия M8O-207Б-19
//Описание класса Long
#pragma once
#include <iostream>

namespace Long 
{
    class Long {
    private:
        unsigned int field1;
        unsigned int field2;
    public:
        Long();
        Long(const unsigned long long a);
        Long(const unsigned int a, const unsigned int b);
        ~Long();
        const Long operator=(const unsigned long long a);
        void Print();
        const Long operator+(const Long &b);
        bool operator>(const Long &b) const;
        bool operator<(const Long &b) const;
        bool operator==(const Long &b) const;
        const Long operator-(const Long &b);
        const Long Multiplication_without_longlong(const Long &b); //Умножение, без использования класса insigned long long
        const Long operator*(const Long &b);
        const Long Division_without_longlong(const Long &b); //Целочисленное деление, без использования класса insigned long long
        const Long operator/(const Long &b);
        const Long RemainderOfDivision_without_longlong(const Long &b); //Нахождение остатка от деления, без использования класса insigned long long
        const Long operator%(const Long &b);
        friend std::ostream& operator<<(std::ostream &os, const Long& b);
    };
    
}